#include <core/io.h>
#include <core/serial.h>
#include <core/tables.h>
#include <core/interrupts.h>
#include <mem/heap.h>
#include <mem/paging.h>

#include "mpx_supt.h"
#include "DateTime.h"
#include "R2.h"
#include <core/io.h>
#include "itoa.h"
#include "R4.h"

struct alList list = {0, NULL, NULL};
struct alList* alarmlist = &list;
char itoabuffer[100];
//memset(itoabuffer, '\0',100);
//max time 86399 seconds
int convertsec(char* msg){
	//int buffersize = 99;
	int result = 0;
	char* tok = strtok(msg,":");
	result = result +(atoi(tok)*3600);
 	tok = strtok(NULL,":");
	result = result +(atoi(tok)*60);
	tok = strtok(NULL,":");
	result = result +(atoi(tok));
	//sys_req(WRITE,DEFAULT_DEVICE, itoa(result),&buffersize);
	//sys_req(WRITE,DEFAULT_DEVICE,"\n",&buffersize);
	return result;
}

void alarm(){
struct pcb* alarm;
alarm = SetupPCB("alarm", 2, 9);
alarm->suspended = 0;
struct context* cp = (struct context*)(alarm->top);
memset(cp,0,sizeof(struct context));
cp->fs = 0x10;
cp->gs = 0x10;
cp->ds = 0x10;
cp->es = 0x10;
cp->cs = 0x8;
cp->ebp = (u32int)(alarm->stack);
cp->esp = (u32int)(alarm->top);
cp->eip = (u32int)checkAlarm;
cp->eflags = 0x202;
InsertPCB(alarm);
}

void createAlarm(char *message, char* time){
	struct alarm* al = sys_alloc_mem(sizeof(struct alarm));
	al->time = convertsec(time);
	//itoa(al->time);
	strcpy(al->message,message);
	insertalarm(al);
}

void checkAlarm(){
  int buffersize = 100;
  int currtime = gettimeseconds();
  while(1){
  	struct alarm* tempAlarm = alarmlist->head;
  	//sys_req(WRITE, DEFAULT_DEVICE, tempAlarm -> message, &buffersize);
	while (tempAlarm != NULL) {
		//sys_req(WRITE, DEFAULT_DEVICE, "No if", &buffersize);
		currtime = gettimeseconds();

		itoa(tempAlarm->time, itoabuffer);
		buffersize = strlen(itoabuffer);
		sys_req(WRITE,DEFAULT_DEVICE, itoabuffer, &buffersize);
		buffersize = 2;
		sys_req(WRITE, DEFAULT_DEVICE, "\n", &buffersize);
		if (tempAlarm->time <= currtime) {
			buffersize = 8;
			sys_req(WRITE, DEFAULT_DEVICE, "Alarm: ", &buffersize);\
			//itoa(tempAlarm->message, itoabuffer);
			buffersize = strlen(tempAlarm->message);
			sys_req(WRITE,DEFAULT_DEVICE, tempAlarm->message, &buffersize);
			buffersize = 2;
			sys_req(WRITE, DEFAULT_DEVICE, "\n", &buffersize);
			itoa(currtime, itoabuffer);
			buffersize = strlen(itoabuffer);
			sys_req(WRITE,DEFAULT_DEVICE, itoabuffer, &buffersize);
			buffersize = 2;
			sys_req(WRITE, DEFAULT_DEVICE, "\n", &buffersize);
			struct alarm* tempNext = tempAlarm->NextPtr;
			removealarm(tempAlarm);
			tempAlarm = tempNext;
		} else {
			tempAlarm = tempAlarm->NextPtr;
		}
	}

    sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
  }
}



void createInfinite()
{
	//serial_print(proc[i]);
	struct pcb* newpcb;
	newpcb = SetupPCB("infinite",1,9);
	newpcb->suspended = 0;
	struct context* cp = (struct context*)(newpcb->top);
	memset(cp,0,sizeof(struct context));
	cp->fs = 0x10;
	cp->gs = 0x10;
	cp->ds = 0x10;
	cp->es = 0x10;
	cp->cs = 0x8;
	cp->ebp = (u32int)(newpcb->stack);
	cp->esp = (u32int)(newpcb->top);
	//cp->eip = (u32int)(*functions[i])();
	cp->eip = (u32int)infinite;
	cp->eflags = 0x202;
	InsertPCB(newpcb);
}
void infinite()
{
  char msg[30];
  int count=0;
	
	memset( msg, '\0', sizeof(msg));
	strcpy(msg, "INFINITE PROCESS EXECUTING.\n");
	count = strlen(msg);
  
  while(1){
  	sys_req(WRITE, DEFAULT_DEVICE, msg, &count);
    sys_req(IDLE, DEFAULT_DEVICE, NULL, NULL);
  }
}

void insertalarm (struct alarm* alPtr){
	if (alarmlist->numAlarms == 0) {
		alarmlist->head = alPtr;
		alarmlist->tail = alPtr;
		alPtr->NextPtr = NULL;
		alPtr->PrevPtr = NULL;
	} else {
		alarmlist->tail->NextPtr = alPtr;
		alPtr->PrevPtr = alarmlist->tail;
		alarmlist->tail = alPtr;
		alPtr->NextPtr = NULL;
	}//end if..else

	alarmlist->numAlarms = alarmlist->numAlarms + 1;
}

void removealarm(struct alarm *pointer){
		if(alarmlist->numAlarms< 2)
		{
			alarmlist->head = NULL;
			alarmlist->tail = NULL;
		}
		else if(alarmlist->head == pointer)
		{
			alarmlist->head = pointer->NextPtr;
			alarmlist->head->PrevPtr = NULL;
		}
		else if(alarmlist->tail == pointer)
		{
			alarmlist->tail = pointer->PrevPtr;
			alarmlist->tail->NextPtr = NULL;
		}
		else
		{
			pointer->PrevPtr->NextPtr = pointer->NextPtr;
			pointer->NextPtr->PrevPtr = pointer->PrevPtr;
		}
	alarmlist->numAlarms = alarmlist->numAlarms-1;
	
	pointer->NextPtr = NULL;
	pointer->PrevPtr = NULL;
}

