#include "R2.h"

char itoabuffer[100] = {'\0'};
//memset(itoabuffer,'\0',100);

//state variables
//int ready, blocked, running;
int ready = 0;
int blocked = 1;
int running = 2;


struct pcb* cop;
struct context* saved_regs;

struct Queue readyQ = {0, NULL, NULL};
struct Queue *y = &readyQ;
struct Queue blockedQ = {0, NULL, NULL};
struct Queue *z = &blockedQ;
int buffersize = 100;

void emptyqueues()
{
	y->head = NULL;
	y->tail = NULL;
	y->numProcesses = 0;
	z->head = NULL;
	z->tail = NULL;
	z->numProcesses = 0;
}

/*
use sys_free_mem() to free all memory associated with a given PCB (the stack, the PCB itself, etc.)
Parameters: PCB pointer to be freed
returns success or error code
 */
int FreePCB(struct pcb *pointer){
	if(sys_free_mem(pointer) == -1)
		return 0;
	else
		return -1;

}



/** insert
 * generic insert function to be used by InsertPCB function, inserts a given PCB into a given Queue. Sorted in H->L priority, FIFO order
 * Inputs:	pcbPtr - pointer to PCB that is to be inserted
 * 			q - pointer to Queue that PCB is to be inserted into
 */
void insert (struct pcb* pcbPtr, struct Queue* q) {
	struct pcb* tempPCB;

    //set pcb to head and tail
	if (q->numProcesses == 0) {
		q->head = pcbPtr;
		q->tail = pcbPtr;
		pcbPtr->NextPtr = NULL;
		pcbPtr->PrevPtr = NULL;
                //insert pcb somewhere else in the queue
	} else {
		tempPCB = q->head;

		//insert at tail
		if(q->tail->priority >= pcbPtr->priority) {
			q->tail->NextPtr = pcbPtr;
			pcbPtr->PrevPtr = q->tail;
			pcbPtr->NextPtr = NULL;
			q->tail = pcbPtr;
		} else {
			while (tempPCB != NULL) {
				if (pcbPtr->priority > tempPCB->priority) {
        	        //Inserting at head
					if (tempPCB == q->head) {
						tempPCB->PrevPtr = pcbPtr;
						pcbPtr->NextPtr = tempPCB;
						pcbPtr->PrevPtr = NULL;
						q->head = pcbPtr;
						
						tempPCB = NULL; //satisfy end condition, terminate
                	    //Inserting in middle
					} 
				}else if (pcbPtr->priority > tempPCB->NextPtr->priority) {
					pcbPtr->NextPtr = tempPCB->NextPtr;
					pcbPtr->PrevPtr = tempPCB;
					tempPCB->NextPtr = pcbPtr;
					pcbPtr->NextPtr->PrevPtr = pcbPtr;



					tempPCB = NULL; //satisfy end condition, terminate
				}//end if..else if
            	tempPCB = tempPCB->NextPtr;

        	}//end while
    	}//end if..else
    }//end if..else
    q->numProcesses++;
}//end function


void insertblocked (struct pcb* pcbPtr, struct Queue* q) {
	if (q->numProcesses == 0) {
		q->head = pcbPtr;
		q->tail = pcbPtr;
		pcbPtr->NextPtr = NULL;
		pcbPtr->PrevPtr = NULL;
	} else {
		q->tail->NextPtr = pcbPtr;
		pcbPtr->PrevPtr = q->tail;
		q->tail = pcbPtr;
		pcbPtr->NextPtr = NULL;
	}//end if..else

	q->numProcesses = q->numProcesses + 1;
}


/*
use sys_alloc_mem() to allocate memory for a new PCB, possibly including the stack, and perform any reasonable initialization
returns PCB pointer if successful
*/
void* AllocatePCB(){
struct pcb* x;
x = (struct pcb*) sys_alloc_mem(sizeof(struct pcb));
x->top = x->stack + 1024  - sizeof(struct context); // allocates 1024 bytes to stack
return x;
}


/*
will call AllocatePCB() to create an empty PCB, initializes the PCB information, sets the PCB state to ready, not suspended.
parameters: proccess name, class, and priority
returns: PCB pointer or NULL if error occurs
 */
void *SetupPCB(char *processname, int processclass, int processpriority){
	int buffersize = 31;
	if(FindPCB(processname)!= NULL){
		sys_req(WRITE,DEFAULT_DEVICE,"Process name should be unique\n",&buffersize);
		return NULL;
	}
	struct pcb* x = AllocatePCB();
	memset(x->name, '\0', 10);
	//process name error checking
 	
	if(strlen(processname) <= 10)
		strcpy(x->name,processname);
	
	else
	{
		buffersize = 52;
		sys_req(WRITE,DEFAULT_DEVICE,"Process name should be at least 8 characters long.\n",&buffersize);
		return NULL;
	}
	//Process name error checking
	if(processclass == 1 || processclass == 2)
		x->class = processclass;
	else
	{
		buffersize = 45;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid class, application = 1 , system = 2\n",&buffersize);
		return NULL;
	}
	//process priority error checking
	if(processpriority >= 0 && processpriority<10)
		x->priority = processpriority;
	else
	{
		buffersize = 52;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid class priority, has to be between 0 and 9.\n",&buffersize);
		return NULL;
	}

	x -> state = 0;
	x -> suspended = 0; // not  suspended.

	return x;
}


/*
will search all queues for a process with a given name
parameters: process name
returns: PCB pointer or NULL if not found
*/
struct pcb* FindPCB(char *name){
	struct pcb* temp = y->head;
	while(temp!= NULL)
	{
		if(!strcmp(temp->name,name))
		{
			return temp;
		}
		temp = temp->NextPtr;
	}
    	//check blocked
	temp = z->head;
	while(temp != NULL)
	{
		if(!strcmp(temp->name, name))
		{
			return temp;
		}
		temp = temp->NextPtr;
	}
	
	return NULL;
}


/** InsertPCB
 * inserts a given PCB into the corresponding queue
 * Inputs:	pointer - pointer to the PCB to be inserted
 */
void InsertPCB(struct pcb *pointer){
	//int buffersize = 100;
	//sys_req(WRITE,DEFAULT_DEVICE,pointer->name,&buffersize);
	if(pointer->state == 0)
	{
		//sys_req(WRITE,DEFAULT_DEVICE,"ready\n",&buffersize);
		insert(pointer, y); //call generic insert function to ready queue
	}
	else if (pointer->state == 1)
	{
		//sys_req(WRITE,DEFAULT_DEVICE,"blocked\n",&buffersize);
		insertblocked(pointer, z); //call generic insert function to blocked queue
	}
}


/*
will remove a PCB from the queue in which it is currently stored
parameters: PCB pointer
returns: Success or Error code
*/
void RemovePCB(struct pcb *pointer){
	if(pointer->state==0)
	{
		if(y->numProcesses < 2)
		{
			y->head = NULL;
			y->tail = NULL;
		}
		else if(y->head == pointer)
		{
			y->head = pointer->NextPtr;
			y->head->PrevPtr = NULL;
		}
		else if(y->tail == pointer)
		{
			y->tail = pointer->PrevPtr;
			y->tail->NextPtr = NULL;
		}
		else
		{
			pointer->PrevPtr->NextPtr = pointer->NextPtr;
			pointer->NextPtr->PrevPtr = pointer->PrevPtr;
		}
		y->numProcesses = y->numProcesses-1;
	}
	else if(pointer->state==1)
	{
		if(z->numProcesses < 2)
		{
			z->head = NULL;
			z->tail = NULL;
		}
		else if(z->head == pointer)
		{
			z->head = pointer->NextPtr;
			z->head->PrevPtr = NULL;
		}
		else if(z->tail == pointer)
		{
			z->tail = pointer->PrevPtr;
			z->tail->NextPtr = NULL;
		}
		else
		{
			pointer->PrevPtr->NextPtr = pointer->NextPtr;
			pointer->NextPtr->PrevPtr = pointer->PrevPtr;
		}
		z->numProcesses = z->numProcesses-1;
	}
	pointer->NextPtr = NULL;
	pointer->PrevPtr = NULL;
}


void createPCB(char *processName , int processClass, int processPriority){
	int buffersize;
	struct pcb *temp = SetupPCB(processName,processClass,processPriority);
	buffersize = 100;
	int processName_len; 
	processName_len = strlen(processName);

	if (processName_len > 10)  //if name was shorter
	{
		buffersize =36;
		sys_req(WRITE,DEFAULT_DEVICE,"Name is greater than 10 characters\n",&buffersize);
	
	} else if (processClass != 1 && processClass != 2)
	{
		buffersize =45;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid class, application = 1 , system = 2\n",&buffersize);
	
	} else if (processPriority < 0 || processPriority > 9 )
	{
		buffersize =52;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid class priority, has to be between 0 and 9.\n",&buffersize);
	}
	else if (FindPCB(processName) == NULL) // no similar name 
	{
		buffersize = 1;
		InsertPCB(temp);
		sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);

	} else if (FindPCB(processName)!=NULL)
	{
		buffersize =20;
		sys_req(WRITE,DEFAULT_DEVICE,"PCB name is taken.\n",&buffersize);

	}
}


void blockPCB(char *processName){
	int buffersize;
	struct pcb *temp;
	int process_state;
	temp = FindPCB(processName);

	if (!temp) // no PCB found 
	{
		buffersize =18;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid PCB name\n",&buffersize);

	} else  //if pcb is found 
	{

		process_state = temp->state;

		if (process_state == 1)
		{
			buffersize =21;
			sys_req(WRITE,DEFAULT_DEVICE,"PCB already blocked\n",&buffersize);

		} else if (process_state ==0) // process is ready
		{
			RemovePCB(temp);
			temp -> state = 1;
			InsertPCB(temp);
			buffersize = 1;
			sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);
			
		}else if (process_state == 2)
		{
			buffersize =16;
			sys_req(WRITE,DEFAULT_DEVICE,"PCB is running\n",&buffersize);


		} else if (process_state !=0 && process_state!= 1 && process_state!=2){
			buffersize =30;
			sys_req(WRITE,DEFAULT_DEVICE,"Error : PCB state is unknown\n",&buffersize);
		}
	}
}


void unblockPCB(char *processName){
	int buffersize;
	struct pcb *temp;
	int process_state;
	temp = FindPCB(processName);

	if (!temp) // no PCB found 
	{
		buffersize =19;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid PCB name \n",&buffersize);
	} else  //if pcb is found 
	{
		process_state = temp->state;

		if (process_state == 0 && process_state == 2)
		{
			buffersize =38;
			sys_req(WRITE,DEFAULT_DEVICE,"PCB already unblocked ready/running \n",&buffersize);

		} else if (process_state ==1) // process is blocked
		{
			RemovePCB(temp);
			temp -> state = 0;
			InsertPCB(temp);
		} else {
			buffersize =30;
			sys_req(WRITE,DEFAULT_DEVICE,"Error : PCB state is unknown\n",&buffersize);
		}
	}
}


void deletePCB(char *name){
	int buffersize = 99;
	struct pcb *temp;
	temp = FindPCB(name);
	
	if (!temp)
	{
		buffersize = 30;
		sys_req(WRITE,DEFAULT_DEVICE,"Error : PCB can not be found\n",&buffersize);
	//serial_print("PCB can not be found\n");
	}
	else if(strcmp(temp-> name, "infinite")==0 && temp-> suspended== 0)
	{
		buffersize = 57;
		sys_req(WRITE,DEFAULT_DEVICE,"Error : Can't delete infinite processs if not suspended\n",&buffersize);
	}
	else if(temp-> class == 2)
	{
		buffersize = 39;
		sys_req(WRITE,DEFAULT_DEVICE,"Error : Can't delete system processes\n",&buffersize);
	}


	else {
	RemovePCB(temp);
	FreePCB(temp);
	}
}


void suspendPCB(char *name){
	int is_suspended; //not suspended = 0, suspended = 1
	struct pcb *temp = FindPCB(name);
	int buffersize = 99;

	if(!temp){
		buffersize = 24;
		sys_req(WRITE,DEFAULT_DEVICE,"PCB couldn't be found \n", &buffersize);
	} 
	else if(temp-> class == 2)
	{
		buffersize = 40;
		sys_req(WRITE,DEFAULT_DEVICE,"Error : Can't suspend system processes\n",&buffersize);
	}
	else{
		is_suspended = temp ->suspended;
		if (is_suspended ==0){
			RemovePCB(temp);
			temp -> suspended =1;
			InsertPCB(temp);
		} 
		else if (is_suspended != 0 && is_suspended != 1){
			buffersize =39;
			sys_req(WRITE,DEFAULT_DEVICE,"Error : PCB suspend value is unkown\n\n",&buffersize);
		}
		

	}
}


void resumePCB(char *name){
	int is_suspended; //not suspended = 0, suspended = 1
	struct pcb *temp = FindPCB(name);
	int buffersize = 99;

	if(!temp){
		buffersize = 24;
		sys_req(WRITE,DEFAULT_DEVICE,"PCB couldn't be found \n", &buffersize);
	} 
	else if(temp-> class == 2)
	{
		buffersize = 39;
		sys_req(WRITE,DEFAULT_DEVICE,"Error : Can't resume system processes\n",&buffersize);
	}
	else 
	{
		is_suspended = temp ->suspended;
		if (is_suspended ==1){
			RemovePCB(temp);
			temp -> suspended =0;
			InsertPCB(temp);
		} 
		else if (is_suspended != 0 && is_suspended != 1){
			buffersize =39;
			sys_req(WRITE,DEFAULT_DEVICE,"Error : PCB suspend value is unknown\n\n",&buffersize);
		}
		

	}
}


void setPCBPriority(char *name, int priority){
	struct pcb *temp = FindPCB(name);
	int buffersize = 99;

	if(!temp){
		buffersize = 32;
		sys_req(WRITE,DEFAULT_DEVICE,"PCB couldn't be found == NULL \n", &buffersize);
	}
	else if(temp-> class == 2)
	{
		buffersize = 46;
		sys_req(WRITE,DEFAULT_DEVICE,"Error : Can't change system process priority\n",&buffersize);
	}

	else if(priority > 9 || priority < 0){
		buffersize = 39;
		sys_req(WRITE,DEFAULT_DEVICE,"PCB couldn't be found. Wrong priority\n", &buffersize);
	}

	else{
		if (strcmp(temp->name, "infinite")==0)
		{
			temp->suspended = 1;
		}
		temp -> priority = priority;
		deletePCB(name);
		InsertPCB(temp);
	}
}


void showPCB(char *processname)
{
	int buffersize = 100;
	struct pcb* temp = FindPCB(processname);
	
	if (temp != NULL)
	{
		buffersize = 15;
		sys_req(WRITE,DEFAULT_DEVICE,"Process name: ", &buffersize);
		buffersize = strlen(temp->name);
		sys_req(WRITE,DEFAULT_DEVICE, temp->name, &buffersize);
		buffersize = 2;
		sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);
		
		buffersize = 8;
		sys_req(WRITE,DEFAULT_DEVICE,"Class: ", &buffersize);
		itoa(temp->class, itoabuffer);
		buffersize = strlen(itoabuffer);
		sys_req(WRITE,DEFAULT_DEVICE, itoabuffer, &buffersize);
		buffersize = 2;
		sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);

		buffersize = 8;
		sys_req(WRITE,DEFAULT_DEVICE,"State: ", &buffersize);
		itoa(temp->state, itoabuffer);
		buffersize = strlen(itoabuffer);
		sys_req(WRITE,DEFAULT_DEVICE, itoabuffer, &buffersize);
		buffersize = 2;
		sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);
		
		buffersize = 19;
		sys_req(WRITE,DEFAULT_DEVICE,"Suspended Status: ", &buffersize);
		itoa(temp->suspended, itoabuffer);
		buffersize = strlen(itoabuffer);
		sys_req(WRITE,DEFAULT_DEVICE, itoabuffer, &buffersize);
		buffersize = 2;
		sys_req(WRITE,DEFAULT_DEVICE,"\n", &buffersize);

		buffersize = 11;
		sys_req(WRITE,DEFAULT_DEVICE,"Priority: ", &buffersize);
		itoa(temp->priority, itoabuffer);
		buffersize = strlen(itoabuffer);
		sys_req(WRITE,DEFAULT_DEVICE, itoabuffer, &buffersize);
		buffersize = 3;
		sys_req(WRITE,DEFAULT_DEVICE,"\n\n", &buffersize);
	}
	else{
		buffersize = 29;
		sys_req(WRITE,DEFAULT_DEVICE,"ERROR: Invalid process name\n", &buffersize);
	}
}


void showReady()
{
	struct pcb* current = y->head;
	if(y->head == NULL){
		buffersize = 7;
		sys_req(WRITE,DEFAULT_DEVICE,"Empty\n", &buffersize);
	}
	while(current != NULL)
	{
		showPCB(current->name);
		current = current->NextPtr;
	}
	return;
}


void showBlocked()
{
	struct pcb* current = z->head;
	if(z->head == NULL){
		buffersize = 7;
		sys_req(WRITE,DEFAULT_DEVICE,"Empty\n", &buffersize);
	}
	while(current != NULL)
	{
		showPCB(current->name);
		current = current->NextPtr;
	}
	return;
}


void showAll()
{
	int buffersize = 18;
	sys_req(WRITE,DEFAULT_DEVICE,"Ready Queue PCBs\n", &buffersize);
	showReady();
	buffersize = 20;
	sys_req(WRITE,DEFAULT_DEVICE,"Blocked Queue PCBs\n", &buffersize);
	showBlocked();
}


u32int sys_call (struct context *registers) {
	param* pars = getparam();
	struct pcb* tempPCB = NULL;
	struct pcb* iterPCB = y -> head;	
		//Proceed through loop in search for the next non-suspended ready process
		//Terminate loop when a non-suspended ready process is found or end of queue is reached
		while (iterPCB != NULL){
			//check if suspended
			if (iterPCB->suspended == 0) {
				tempPCB = iterPCB;
				break;
			}
			else {
				iterPCB = iterPCB->NextPtr;
			}//end if..else
		}//end while
	
	//if cop is null, this is the first sys_call call
	if (cop == NULL) {
		//save context of caller's registers
		saved_regs = registers;
	} else {
		//if the op code is IDLE, save context
		if (pars->op_code == IDLE) {
			cop->top = (unsigned char*) registers;
			cop->state = 0;
			InsertPCB(cop);
		//if op code is Exit, free cop
		} else if (pars->op_code == EXIT) {
			FreePCB(cop);
		}
	}

	//check for Ready Processes
	if (readyQ.head != NULL) {
		//Proceed through loop in search for the next non-suspended ready process
		//Terminate loop when a non-suspended ready process is found or end of queue is reached
		while (tempPCB != NULL){
			//check if suspended
			if (tempPCB->suspended == 0) {
				cop = tempPCB;
				RemovePCB(tempPCB);
				cop->state = 2;
				return (u32int) cop->top;
			}else {
				tempPCB = tempPCB->NextPtr;
			}//end if..else
		}//end while
	}//end if
	//if reached, all ready processes are suspended
	//if no other processes to run, return previously saved registers from caller
	return (u32int) saved_regs;
}

