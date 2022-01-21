#include <system.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>
#include <core/tables.h>
#include <core/interrupts.h>
#include <mem/heap.h>
#include <mem/paging.h>

#include "mpx_supt.h"
#include "R2.h"
#include "R3.h"
#include "procsr3.h"

void yield() {
	asm volatile ("int $60");
}

void* loadr3()
{
	char proc[5][6] = {"proc1\0","proc2\0","proc3\0","proc4\0","proc5\0"};
	//void (*functions[5])() = {proc1,proc2,proc3,proc4,proc5};
	u32int functions[5] = {(u32int)proc1, (u32int)proc2, (u32int)proc3, (u32int)proc4, (u32int)proc5};
	int i = 0;
	struct pcb* newpcb;
	for(i = 0; i<5; i++)
	{
		
		newpcb = SetupPCB(proc[i],1,9);
		newpcb->suspended = 1;
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
		cp->eip = (u32int)functions[i];
		cp->eflags = 0x202;
		InsertPCB(newpcb);
	}
	return newpcb;
}