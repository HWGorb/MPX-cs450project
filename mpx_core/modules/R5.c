#include "R5.h"

u32int heapStart;
struct allocatedblocks* allocblocks;
struct freeblocks* freeblocks;
char itoabuffer2[100]={'\0'};
//memset(itoabuffer2,'\0',100);

int isEmptyR5(){
	int buffersize = 100;
	if(allocblocks->head == NULL){
		buffersize = 19;
		sys_req(WRITE,DEFAULT_DEVICE,"The heap is empty\n", &buffersize);
		return 0;
	}
	else{
		buffersize = 23;
		sys_req(WRITE,DEFAULT_DEVICE,"The heap is not empty\n", &buffersize);
	}
	return 1;
}

void* initHeap(int size)
{
	struct CMCB* head = (struct CMCB*) kmalloc(sizeof(struct CMCB)+size);
	heapStart = (u32int)head+sizeof(struct CMCB);
	//head = {0, heapStart, size, "head",NULL,NULL};
	head->type = 0;
	head->addr = (void*)heapStart;
	head->size = size;
	//head->pcbname = "head";

	
	
	allocblocks = (struct allocatedblocks*) kmalloc(sizeof(struct allocatedblocks));
	allocblocks->head = NULL;
	//alloc->head = NULL;
	freeblocks = (struct freeblocks*) kmalloc(sizeof(struct freeblocks));
	freeblocks->head = head;

	return (void*)heapStart;
}

//will have to set next and prev pointers of both allocated block just created and free block
u32int allocateMem(u32int size)
{
	struct CMCB* temp = freeblocks->head;
	if(temp != NULL)
	{
		while(temp != NULL)
		{
			//remove temp from freelist

			if(size < (u32int)(temp->size))
			{
				if(temp == freeblocks->head)
				{
					freeblocks->head = temp->next;
				}

				if(temp->next != NULL)
				{
					if(temp->prev != NULL)
					{	
						temp->prev->next = temp->next;
					}
					temp->next->prev = temp->prev;
				}
				if(temp->prev != NULL)
				{
					if(temp->next != NULL)
						temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
				}	
				//free block size before allocation
				int tempfreeblocksize = temp->size;

				struct CMCB* newallocblock = temp;
				newallocblock->type 	= 1;
				newallocblock->size 	= size;
				newallocblock->next 	= NULL;
				newallocblock->prev 	= NULL;
				//make sure that allocated block is in order by address
				struct CMCB* temphead = allocblocks->head;
				if(temphead != NULL)
				{
					if (newallocblock->addr - sizeof(struct CMCB) < (void*)temphead)
					{
						newallocblock->next = temphead;
						newallocblock->next->prev = newallocblock; 
						//temphead->prev = newallockblock; 
						allocblocks->head = newallocblock; 
					}
					else
					{
						while(temphead != NULL)
						{
							//already know that size we are allocating is smaller than current free block
							//check if location in memory is 
							
							if (newallocblock->addr - sizeof(struct CMCB) > (void*)temphead && temphead->next == NULL)
							{
								temphead->next = newallocblock;
								temphead->next->prev = temphead;
								break;	
							}
							temphead = temphead->next;
						}
					}
				}
				else
				{
					allocblocks->head = newallocblock;
				}
				struct CMCB* newfreeblock = (struct CMCB*) (temp->addr +temp->size);
				newfreeblock->type = 0;
				newfreeblock->addr = (void*)((u32int)newfreeblock + sizeof(struct CMCB));
				//+2*sizeof(struct CMCB) to account for the beginning CMCB and the end CMCB of the allocated block
				newfreeblock->size = tempfreeblocksize - (size + sizeof(struct CMCB));


				newfreeblock->next = NULL;
				newfreeblock->prev = NULL;

				//need to rempve temp before manipulate new freeblcok
				//need to set freeblock-> head to new head
				temp = newfreeblock;
				if(freeblocks->head == NULL)
					freeblocks->head = newfreeblock; 
				else
				{
					temphead = freeblocks->head;
					while(temphead != NULL)
					{
						if(temp < temphead)
						{
							if(temphead == freeblocks->head)
							{
								freeblocks->head = temp;
							}
							//temphead = temp;
							temp->prev = temphead->prev;
							temp->next = temphead; 
							if(temphead->prev != NULL)
							{
								temphead->prev->next = temp;
							}
							temphead->prev = temp;
							break;
						}
						if(temphead->next == NULL)
						{
							temphead->next = temp;
							temp->prev = temphead;
							break;
						}
						//else
						temphead = temphead->next;
					}
				}

				return (u32int)(newallocblock->addr);
			}
			temp = temp->next;
		}
	}
	
	return NULL;
}

int freeMem(void* x)
{
	int buffersize = 100;
	//int address = itoa(x);
	struct CMCB* temp = findCMCB(x);
	if(temp != NULL && temp->addr != x)
	{
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid pointer\n", &buffersize);	
		return 1;
	}
	else if(temp->type == 0 && temp->size != 0)
	{
		sys_req(WRITE,DEFAULT_DEVICE,"already free memory\n", &buffersize);	
		return 1;
	}
	
	//unlinking from alllocated list
	if(temp == allocblocks->head)
	{
		allocblocks->head = temp->next;
	}

	if(temp->next != NULL)
	{
		if(temp->prev != NULL)
		{
			temp->prev->next = temp->next;
		}
		temp->next->prev = temp->prev;
	}
	if(temp->prev != NULL)
	{	
		if(temp->next != NULL)
			temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
	}

	//sets the new free block in the freeblocks list
	struct CMCB* temphead= freeblocks->head;
	//compares loc in mem, temp=allocated block, temphead=loc in free list
	temp->type = 0;
	while(temphead != NULL)
	{
		if(temp < temphead)
		{
			if(temphead == freeblocks->head)
			{
				freeblocks->head = temp;
			}
			//temphead = temp;
			temp->prev = temphead->prev;
			temp->next = temphead; 
			if(temphead->prev != NULL)
			{
				temphead->prev->next = temp;
			}
			temphead->prev = temp;
			break;
		}
		if(temphead->next == NULL)
		{
			temphead->next = temp;
			temp->prev = temphead;
			break;
		}
		temphead=temphead->next;
	}
	
	//temp is now in free list
	//temp = temphead;
	struct CMCB* tempbeginning = NULL;
	struct CMCB* tempend = NULL;
	//tempbeginning = tempend;
	
	//check if temp has next and set tempend to either temp next if it has one or temp itself if not
	if(temp->next != NULL)
		{
		if(temp->next->addr == temp->addr  + temp->size +sizeof(struct CMCB))
		{
			tempend = temp->next;
			temp->size += sizeof(struct CMCB) + temp->next->size;
			temp->next = tempend->next;
			if(tempend->next != NULL)
				tempend->next->prev = temp;
			//tempend->prev->prev->next=tempend->next;
		}
	}	
		//
	//if freeblock prev is also adjacent, tempbeginning = prev pointer
	if(temp->prev != NULL)
	{
		if(temp->prev->addr + temp->prev->size + sizeof(struct CMCB) == temp->addr)
		{
			tempbeginning = temp->prev;
			//tempbeginning(temp->prev) size now has to include the size of temp and overwrite its end CMCB and temp's beginning CMCB
			tempbeginning->size = tempbeginning->size + sizeof(struct CMCB) + temp->size;
			tempbeginning->next = temp->next;
			if(temp->next != NULL)
				temp->next->prev = tempbeginning; 
		}
	}
	return 0;
}

void showfree()
{
	int buffersize;
	buffersize = 99;
	uint32_t address; 
	struct CMCB* temp = freeblocks->head;
	if (temp == NULL)
	{
		buffersize = 7;
	sys_req(WRITE,DEFAULT_DEVICE,"Empty\n", &buffersize);
	}
	else
	{
		buffersize = 14;
		sys_req(WRITE,DEFAULT_DEVICE,"Free memory \n", &buffersize);
		while(temp != NULL)
		{
			address =(int)temp->addr;
			buffersize = 14;
			sys_req(WRITE,DEFAULT_DEVICE,"Block size : ", &buffersize);
			memset(itoabuffer2,'\0',100);
			itoa(temp->size, itoabuffer2);
			buffersize = strlen(itoabuffer2);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer2, &buffersize);
			buffersize = 2;
			sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);
			buffersize = 16;
			sys_req(WRITE,DEFAULT_DEVICE,"Block address:\t", &buffersize);
			memset(itoabuffer2,'\0',100);
			itoa(address, itoabuffer2);
			buffersize = strlen(itoabuffer2);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer2, &buffersize);
			buffersize = 3;
			sys_req(WRITE,DEFAULT_DEVICE,"\n\n", &buffersize);
			temp = temp->next;
		}
	}
}

void showallocated()
{
	uint32_t address; 

	int buffersize;
	buffersize = 99;
	struct CMCB* temp = allocblocks->head;
	if (temp == NULL)
	{
	sys_req(WRITE,DEFAULT_DEVICE,"Empty\n", &buffersize);
	}
	else
	{
		sys_req(WRITE,DEFAULT_DEVICE,"Allocated memory\n", &buffersize);
	while(temp != NULL){
		buffersize = 99;
			sys_req(WRITE,DEFAULT_DEVICE,"Block size :\t", &buffersize);
			itoa(temp->size, itoabuffer2);
			buffersize = strlen(itoabuffer2);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer2, &buffersize);
			sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);
			sys_req(WRITE,DEFAULT_DEVICE,"Block address:\t", &buffersize);
			address =(int)temp->addr;
			itoa(address, itoabuffer2);
			buffersize = strlen(itoabuffer2);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer2, &buffersize); 
			//sys_req(WRITE,DEFAULT_DEVICE,itoa(address), &buffersize);
			buffersize = 3;
			sys_req(WRITE,DEFAULT_DEVICE,"\n\n", &buffersize);
			temp = temp->next;
		}
	}
}

void printaddr(int address){
	if (address <0 || address > 9){
		int newaddress = address/8;
		printaddr(newaddress);
	}
	int print = (address%8)+'0';
	outb(COM1,print);
}

struct CMCB* findCMCB(void* x)
{
	
	int buffersize = 100;	
	struct CMCB* temp = freeblocks->head;
	if(temp==NULL)
		sys_req(WRITE,DEFAULT_DEVICE,"freehead is null\n", &buffersize);	
	while(temp!= NULL)
	{
		if((u32int)temp->addr == (u32int)x)
		{
			itoa((u32int)temp->addr, itoabuffer2);
			buffersize = strlen(itoabuffer2);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer2, &buffersize);	
			sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);	
			return temp;
		}
		temp = temp->next;
	}
	temp = allocblocks->head;
	if(temp==NULL)
		sys_req(WRITE,DEFAULT_DEVICE,"allocblocks is null\n", &buffersize);	
	while(temp!= NULL)
	{
		if((u32int)temp->addr == (u32int)x)
		{
			itoa((u32int)temp, itoabuffer2);
			buffersize = strlen(itoabuffer2);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer2, &buffersize);
			sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);	
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
