#ifndef _R2_H
#define _R2_H

#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/io.h>
#include <core/serial.h>
#include <core/tables.h>
#include <core/interrupts.h>
#include <mem/heap.h>
#include <mem/paging.h>

#include "mpx_supt.h"
#include "itoa.h"


struct pcb
{
	char name[10];
	//application = 1, system process = 2
	int class;
	//between 0 and 9, 0 is lowest priority and 9 is highest
	int priority;
	//ready=0, blocked = 1, running = 2
	int state;
	//not suspended = 0, suspended = 1
	int suspended;
	//has to be at least 1024 bytes
	unsigned char stack[1024];
	unsigned char *top;
	//just calling the stack automatically is at the base.
	struct pcb* NextPtr;
	struct pcb* PrevPtr;
};

struct Queue {
	int numProcesses;
	struct pcb* head;
	struct pcb* tail;
};

struct context {
	u32int gs, fs, es, ds;
	u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32int eip, cs, eflags;
};

void emptyqueues();
int FreePCB(struct pcb *pointer);
int isEmpty(struct Queue* q);
void insert (struct pcb* pcbPtr, struct Queue* q);
void insertblocked (struct pcb* pcbPtr, struct Queue* q) ;
void* AllocatePCB();
void *SetupPCB(char *processname, int processclass, int processpriority);
struct pcb* FindPCB(char *name);
void InsertPCB(struct pcb *pointer);
void RemovePCB(struct pcb *pointer);
void createPCB(char *processName , int processClass, int processPriority);
void blockPCB(char *processName);
void unblockPCB(char *processName);
void deletePCB(char *name);
void suspendPCB(char *name);
void resumePCB(char *name);
void setPCBPriority(char *name, int priority);
void showPCB(char *processname);
void showReady();
void showBlocked();
void showAll();
u32int sys_call (struct context *registers);


#endif
