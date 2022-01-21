#ifndef _R5_H
#define _R5_H

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
#include "R2.h"
#include <core/io.h>

struct CMCB{
	//0 = free, 1 = allocated
	int type;
	void* addr;
	//u32int addr;
	int size;
	//char pcbname[15];
	struct CMCB* next;
	struct CMCB* prev;
};

/*
struct allocatedblocks {
int type;
void* addr;
int size;
char* pcbname;
struct CMCB* next;
struct CMCB* prev;
};
*/
struct allocatedblocks {
	struct CMCB* head;
};

struct freeblocks {
	struct CMCB* head;
};

int isEmptyR5();
void* initHeap(int size);
u32int allocateMem(u32int size);
int freeMem(void* x);
void showfree();
void showallocated();
void printaddr(int address);
struct CMCB* findCMCB(void* x);



#endif
