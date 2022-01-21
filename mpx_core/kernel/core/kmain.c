/*
  ----- kmain.c -----

  Description..: Kernel main. The first function called after
      the bootloader. Initialization of hardware, system
      structures, devices, and initial processes happens here.
      
      Initial Kernel -- by Forrest Desjardin, 2013, 
      Modifications by:    Andrew Duncan 2014,  John Jacko 2017
      				Ben Smith 2018, and Alex Wilson 2019
*/

#include <stdint.h>
#include <string.h>
#include <system.h>

#include <core/io.h>
#include <core/serial.h>
#include <core/tables.h>
#include <core/interrupts.h>
#include <mem/heap.h>
#include <mem/paging.h>

#include "modules/mpx_supt.h"
#include "modules/comhand.c"
#include "modules/R2.h"
#include "modules/Startup.h"
#include "modules/R5.h"
void makeComhand();
void makeIdle();
void kmain(void)
{
   extern uint32_t magic;
   // Uncomment if you want to access the multiboot header
   // extern void *mbd;
   // char *boot_loader_name = (char*)((long*)mbd)[16];

  
   // 0) Initialize Serial I/O 
   // functions to initialize serial I/O can be found in serial.c
   // there are 3 functions to call
 	init_serial(COM1);
	set_serial_in(COM1);
	set_serial_out(COM1);

   klogv("Starting MPX boot sequence...");
   klogv("Initialized serial I/O on COM1 device...");

   // 1) Initialize the support software by identifying the current
   //     MPX Module.  This will change with each module.
   // you will need to call mpx_init from the mpx_supt.c
	//mpx_init(MODULE_R3);	
  
  mpx_init(MEM_MODULE);
  sys_set_malloc(allocateMem);
  sys_set_free(freeMem);
  initHeap(50000);
   // 2) Check that the boot was successful and correct when using grub
   // Comment this when booting the kernel directly using QEMU, etc.
   if ( magic != 0x2BADB002 ){
     //kpanic("Boot was not error free. Halting.");
   }
   
   // 3) Descriptor Tables -- tables.c
   //  you will need to initialize the global
   // this keeps track of allocated segments and pages
   klogv("Initializing descriptor tables...");
	 init_gdt();


    // 4)  Interrupt vector table --  tables.c
    // this creates and initializes a default interrupt vector table
    // this function is in tables.c
	 init_idt();
   init_pic();
   init_irq();
	 sti();	
   klogv("Interrupt vector table initialized!");

   // 5) Virtual Memory -- paging.c  -- init_paging
   //  this function creates the kernel's heap
   //  from which memory will be allocated when the program calls
   // sys_alloc_mem UNTIL the memory management module  is completed
   // this allocates memory using discrete "pages" of physical memory
   // NOTE:  You will only have about 70000 bytes of dynamic memory
   //
   klogv("Initializing virtual memory...");
	init_paging();
	//sys_alloc_mem(0);

  // MODULE 5 INTEGRATION
  klogv("Initializing heap...:");
  //initHeap(50000);
  //sys_set_malloc(allocateMem);
  //sys_set_free(freeMem);
  //isEmptyR5()

   // 6) Call YOUR command handler -  interface method
   klogv("Transferring control to commhand...");
   //comhand();
  startup();
  makeComhand();
  makeIdle();
  asm volatile("int $60");
   // 7) System Shutdown on return from your command handler
   klogv("Starting system shutdown procedure...");
   
   /* Shutdown Procedure */
   klogv("Shutdown complete. You may now turn off the machine. (QEMU: C-a x)");
   hlt();
}
void makeComhand(){
  struct pcb* command;
  command = SetupPCB("commhand",2,9);
  command->suspended = 0;
  struct context* cp = (struct context*)(command->top);
  memset(cp,0,sizeof(struct context));
  cp->fs = 0x10;
  cp->gs = 0x10;
  cp->ds = 0x10;
  cp->es = 0x10;
  cp->cs = 0x8;
  cp->ebp = (u32int)(command->stack);
  cp->esp = (u32int)(command->top);
  //cp->eip = (u32int)(*functions[i])();
  cp->eip = (u32int)comhand;
  cp->eflags = 0x202;
  InsertPCB(command);
}
void makeIdle(){
  struct pcb* idleproc;
  idleproc = SetupPCB("idle",2,0);
  idleproc->suspended = 0;
  struct context* cp = (struct context*)(idleproc->top);
  memset(cp,0,sizeof(struct context));
  cp->fs = 0x10;
  cp->gs = 0x10;
  cp->ds = 0x10;
  cp->es = 0x10;
  cp->cs = 0x8;
  cp->ebp = (u32int)(idleproc->stack);
  cp->esp = (u32int)(idleproc->top);
  //cp->eip = (u32int)(*functions[i])();
  cp->eip = (u32int)idle;
  cp->eflags = 0x202;
  InsertPCB(idleproc);
}