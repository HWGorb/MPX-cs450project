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
#include "DateTime.h"
#include "R1.h"
#include "R2.h"
#include "R3.h"
#include "R4.h"
#include "R5.h"


void comhand(){
char cmdBuffer[100];
char resultBuffer[25];
int bufferSize;
int quit = 0;
char cmd[100];
bufferSize = 31;
sys_req(WRITE,DEFAULT_DEVICE,"Welcome to\033[1;36m The Hopeless Four OS \033[0m\n", &bufferSize);

int alarmflag = 0;
while(!quit){
// get a command
memset(cmdBuffer,'\0',100);
bufferSize = 99;
sys_req(READ,DEFAULT_DEVICE,cmdBuffer, &bufferSize);
memset(cmd, '\0', 100);
strcpy(cmd,cmdBuffer);
char * delim = " ";
char * token = strtok(cmd,delim);


//process command
if(strcmp(token,"version") == 0){
version();
}
else if(strcmp(token,"help") == 0){
help(strtok(NULL, delim));
}
else if(strcmp(token, "getdate") == 0){
getdate(strtok(NULL, delim));
}
else if(strcmp(token, "setdate") == 0){
setdate(strtok(NULL, delim));
}
else if(strcmp(token, "gettime") == 0){
gettime(strtok(NULL, delim));
}
else if(strcmp(token, "settime") == 0){
settime(strtok(NULL, delim));
}
//checks for quit
else if(strcmp(token,"shutdown") == 0){
bufferSize = 44;
sys_req(WRITE,DEFAULT_DEVICE,"are you sure you want to shutdown? (yes/no)\n", &bufferSize);
bufferSize = 25;
memset(resultBuffer,'\0',25);
sys_req(READ,DEFAULT_DEVICE,resultBuffer,&bufferSize);
char * token2 = strtok(resultBuffer,delim);
if(strcmp(token2,"yes")==0){
	emptyqueues();
	sys_req(EXIT,DEFAULT_DEVICE,NULL,NULL);
quit = 1;
}
else if(strcmp(token2,"no")== 0){
bufferSize = 31;
sys_req(WRITE,DEFAULT_DEVICE,"Returning to Helpless Four OS\n", &bufferSize);	
}
else{
	bufferSize = 53;
sys_req(WRITE,DEFAULT_DEVICE,"Not valid a response, returning to Helpless Four OS\n", &bufferSize);	
}
}
else if(strcmp(token, "suspendpcb") == 0){
suspendPCB(strtok(NULL, delim));
}
else if(strcmp(token, "resumepcb") == 0){
resumePCB(strtok(NULL, delim));
}
else if(strcmp(token, "setpcbpriority") == 0){
	char * token1 = strtok(NULL,delim);
	int token2 = atoi(strtok(NULL,delim));
setPCBPriority(token1, token2);
}
else if(strcmp(token,"deletepcb")==0){
	deletePCB(strtok(NULL,delim));
}
else if(strcmp(token, "showpcb") == 0){
	showPCB(strtok(NULL,delim));
}
else if(strcmp(token, "showallprocesses") == 0){
	showAll();
}
else if(strcmp(token, "showreadyprocesses") == 0){
	showReady();
}
else if(strcmp(token, "showblockedprocesses") == 0){
	showBlocked();
}
else if(strcmp(token, "color") == 0){
	color(strtok(NULL, delim));

	} 
else if(strcmp(token, "loadr3") == 0)
{
	loadr3();
}

else if(strcmp(token,"clear")==0){
sys_req(WRITE,DEFAULT_DEVICE,"\e[1;1H\e[2J", &bufferSize);	
} 

else if(strcmp(token, "alarm") == 0){
	if (!alarmflag) {
		alarm();
		alarmflag = 1;
	}
	char* token1 = strtok(NULL,"\"");
	char* token2 = strtok(NULL," ");

	createAlarm(token1,token2);
}
else if(strcmp(token, "infinite") == 0){
	createInfinite();
}
/*
else if(strcmp(token, "initheap") == 0){
	initHeap(50000);
}
else if(strcmp(token, "allocatemem") == 0){
	int token1 = atoi(strtok(NULL,delim));
	allocateMem(token1);
}*/else if(strcmp(token, "showfree") == 0){
	showfree();
}
else if(strcmp(token, "showallocated") == 0){
	showallocated();
}
/*else if(strcmp(token, "freemem") == 0){
	u32int token1 = (u32int)atoi(strtok(NULL,delim));
	freeMem((void*)token1);
}
else if(strcmp(token, "showfree") == 0){
	showfree();
}*/
else if(strcmp(token, "isempty") == 0){
	isEmptyR5();
}
else{
//not valid command statement
bufferSize = 21;
sys_req(WRITE,DEFAULT_DEVICE,"Not a valid command\n",&bufferSize);
}
sys_req(IDLE,DEFAULT_DEVICE,NULL,NULL);
}
}
