#include "R1.h"

char * version(){
	char buffer[100];
	int bufferSize = 26;
	memset(buffer,'\0',100);
	sys_req(WRITE,DEFAULT_DEVICE,"Version 4.0 : 04/09/2021\n", &bufferSize);
	return "Version 4.0 : 04/09/2021";
}

void help_help(){
		int buffersize=8;
		sys_req(WRITE,DEFAULT_DEVICE,"help\t\t\t",&buffersize);
	  	buffersize=110;
	  	sys_req(WRITE,DEFAULT_DEVICE,"this will print the list of help instructions. help <function> will only print instuctions for that function\n",&buffersize);

}
void help_version(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"version\t\t\t",&buffersize);
	  	buffersize=29;
	  	sys_req(WRITE,DEFAULT_DEVICE,"this will print the version\n",&buffersize);


}
void help_getdate(){
int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"getdate\t\t\t",&buffersize);
		buffersize=38;
	  	sys_req(WRITE,DEFAULT_DEVICE,"prints the date in format mm/dd/yyyy\n",&buffersize);
}
void help_setdate(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"setdate\t\t\t",&buffersize);
	  	buffersize=54;
	  	sys_req(WRITE,DEFAULT_DEVICE,"sets the date to the given date in format mm/dd/yyyy\n",&buffersize);

}
void help_gettime(){
		int buffersize=1;
		sys_req(WRITE,DEFAULT_DEVICE,"gettime\t\t\t",&buffersize);
		buffersize=36;
	  	sys_req(WRITE,DEFAULT_DEVICE,"prints the time in format hh:mm:ss\n",&buffersize);

}
void help_settime(){
		int buffersize=1;
		sys_req(WRITE,DEFAULT_DEVICE,"settime\t\t\t",&buffersize);
		buffersize=52;
	  	sys_req(WRITE,DEFAULT_DEVICE,"sets the time to the given time in format hh:mm:ss\n",&buffersize);

}
void help_shutdown(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"shutdown\t\t",&buffersize);
		buffersize=13;
	  	sys_req(WRITE,DEFAULT_DEVICE,"EXIT system\n",&buffersize);

}
void help_suspendpcb(){
		int buffersize=13;
		sys_req(WRITE,DEFAULT_DEVICE,"suspendpcb\t\t",&buffersize);
		buffersize=64;
	  	sys_req(WRITE,DEFAULT_DEVICE,"suspend <processName> suspends the process with the given name\n",&buffersize);

}
void help_resumepcb(){
		int buffersize=12;
		sys_req(WRITE,DEFAULT_DEVICE,"resumepcb\t\t",&buffersize);
		buffersize=64;
	  	sys_req(WRITE,DEFAULT_DEVICE,"resumes <processName> suspends the process with the given name\n",&buffersize);

}
void help_setpcbpriority(){
		int buffersize=17;
		sys_req(WRITE,DEFAULT_DEVICE,"setpcbpriority\t\t",&buffersize);
		buffersize=100;
	  	sys_req(WRITE,DEFAULT_DEVICE,"setpcbpriority <processName> <priority> sets the priority (0-9) of the process with the given name\n",&buffersize);

}
void help_showpcb(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"showpcb\t\t\t",&buffersize);
		buffersize=61;
	  	sys_req(WRITE,DEFAULT_DEVICE,"showpcb <processName> shows the process with the given name\n",&buffersize);

}
void help_showallprocesses(){
		int buffersize=18;
		sys_req(WRITE,DEFAULT_DEVICE,"showallprocesses\t",&buffersize);
		buffersize=59;
	  	sys_req(WRITE,DEFAULT_DEVICE,"showallprocesses displays all processes within the system\n",&buffersize);

}
void help_showreadyprocesses(){
		int buffersize=20;
		sys_req(WRITE,DEFAULT_DEVICE,"showreadyprocesses\t",&buffersize);
		buffersize=62;
	  	sys_req(WRITE,DEFAULT_DEVICE,"showreadyprocesses displays all processes in the ready queue\n",&buffersize);

}
void help_showblockedprocesses(){
		int buffersize=22;
		sys_req(WRITE,DEFAULT_DEVICE,"showblockedprocesses\t",&buffersize);
		buffersize=66;
	  	sys_req(WRITE,DEFAULT_DEVICE,"showblockedprocesses displays all processes in the blocked queue\n",&buffersize);

}
void help_deletePCB(){
		int buffersize=12;
		sys_req(WRITE,DEFAULT_DEVICE,"deletePCB\t\t",&buffersize);
		buffersize=65;
	  	sys_req(WRITE,DEFAULT_DEVICE,"deletepcb <processName> deletes the process with the given name\n",&buffersize);

}
void help_loadr3(){
		int buffersize=10;
		sys_req(WRITE,DEFAULT_DEVICE,"loadr3\t\t\t",&buffersize);
		buffersize=76;
	  	sys_req(WRITE,DEFAULT_DEVICE,"loadr3 Load R3 process into memory in a ready state at any priority chosen\n",&buffersize);

}
void help_color(){
		int buffersize=9;
		sys_req(WRITE,DEFAULT_DEVICE,"color\t\t\t",&buffersize);
		buffersize=69;
	  	sys_req(WRITE,DEFAULT_DEVICE,"color <color name>,{reset,yellow,white,red,blue,purple,green,black}\n",&buffersize);

}
void help_yield(){
		int buffersize=9;
		sys_req(WRITE,DEFAULT_DEVICE,"yield\t\t\t",&buffersize);
		buffersize=27;
	  	sys_req(WRITE,DEFAULT_DEVICE,"yield to other processes\n",&buffersize);

}

void help_inf(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"infinite\t\t",&buffersize);
		buffersize=28;
	  	sys_req(WRITE,DEFAULT_DEVICE,"Create an infinite process\n",&buffersize);

}
void help_alarm(){
		int buffersize=9;
		sys_req(WRITE,DEFAULT_DEVICE,"alarm\t\t\t",&buffersize);
		buffersize=43;
	  	sys_req(WRITE,DEFAULT_DEVICE,"Create an alarm that prints given message\n",&buffersize);

}


void help_isempty(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"isempty\t\t\t",&buffersize);
		buffersize=29;
	  	sys_req(WRITE,DEFAULT_DEVICE,"checks if the heap is empty\n",&buffersize);

}
void help_showallocated(){
		int buffersize=16;
		sys_req(WRITE,DEFAULT_DEVICE,"showallocated\t\t",&buffersize);
		buffersize=31;
	  	sys_req(WRITE,DEFAULT_DEVICE,"shows all allocated processes\n",&buffersize);

}
void help_showfree(){
		int buffersize=11;
		sys_req(WRITE,DEFAULT_DEVICE,"showfree\t\t",&buffersize);
		buffersize=26;
	  	sys_req(WRITE,DEFAULT_DEVICE,"shows all free processes\n",&buffersize);

}
void help(char* instr){

int buffersize;

//extract additional instructions if they exist
char* delim = " ";
char* additional_parameter = strtok(instr, delim);
//additional_parameter = strtok(NULL, delim);



if (additional_parameter == NULL) {
	buffersize = 26;
		sys_req(WRITE,DEFAULT_DEVICE,"\033[1;37mCommand\t\t\t Instructions\033[0m\n",&buffersize);

buffersize = 89;
		sys_req(WRITE,DEFAULT_DEVICE,"\033[1;37m______________________________________________________________________________________\033[0m\n",&buffersize);

buffersize = 1;
		sys_req(WRITE,DEFAULT_DEVICE,"\033[1;36m",&buffersize);
		help_help();
help_version();
help_getdate();
help_setdate();
help_gettime();
help_settime();
help_shutdown();
help_suspendpcb();
help_resumepcb();
help_setpcbpriority();
help_showpcb();
help_showallprocesses();
help_showreadyprocesses();
help_showblockedprocesses();
help_deletePCB();
help_loadr3();
help_color();
help_inf();
help_alarm();
help_showfree();
help_showallocated();
help_isempty();
} else {
	if (strcmp(additional_parameter, "version") == 0) {

help_version();

	} else if (strcmp(additional_parameter, "help") == 0) {

help_help();
	} else if (strcmp(additional_parameter, "getdate") == 0) {
help_getdate();


	} else if (strcmp(additional_parameter, "setdate") == 0) {
		help_setdate();


	} else if (strcmp(additional_parameter, "gettime") == 0) {
		help_gettime();


	} else if (strcmp(additional_parameter, "settime") == 0) {
		help_settime();


	} else if (strcmp(additional_parameter, "shutdown") == 0) {
		help_shutdown();


	} else if (strcmp(additional_parameter, "suspendpcb") == 0) {
		help_suspendpcb();


	} else if (strcmp(additional_parameter, "resumepcb") == 0) {
		help_resumepcb();


	} else if (strcmp(additional_parameter, "setpcbpriority") == 0) {
		help_setpcbpriority();


	} else if (strcmp(additional_parameter, "showpcb") == 0) {
		help_showpcb();


	} else if (strcmp(additional_parameter, "showallprocesses") == 0) {
		help_showallprocesses();



	} else if (strcmp(additional_parameter, "showreadyprocesses") == 0) {
		help_showreadyprocesses();


	} else if (strcmp(additional_parameter, "showblockedprocesses") == 0) {
		help_showblockedprocesses();

	
	}
	else if (strcmp(additional_parameter, "loadr3") == 0) {
	help_loadr3();
	
	} else if(strcmp(additional_parameter, "color") == 0){
		help_color();

	} else if(strcmp(additional_parameter, "deletePCB") == 0){
		help_deletePCB();

	} 
	 else if(strcmp(additional_parameter, "infinite") == 0){
	help_inf();
	} 
	else if(strcmp(additional_parameter, "alarm") == 0){
	help_alarm();
	} 
	else if(strcmp(additional_parameter, "showallocated") == 0){
	help_showallocated();
	} 
	else if(strcmp(additional_parameter, "showfree") == 0){
	help_showfree();
	} 
	else if(strcmp(additional_parameter, "isempty") == 0){
	help_isempty();
	} 
	else {
		int buffersize=50;
		sys_req(WRITE,DEFAULT_DEVICE,"Cannot provide information on an invalid command\n",&buffersize);
	}//end if..else

}//end if..else
buffersize =1;
		sys_req(WRITE,DEFAULT_DEVICE,"\033[0m\n",&buffersize);


}

void color(char* instr){
int buffersize;
char* delim = " ";
char* additional_parameter = strtok(instr, delim);
			buffersize = 1;   

if (strcmp(additional_parameter, "yellow") == 0) {
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0;33m",&buffersize);


	} else if (strcmp(additional_parameter, "white") == 0) {
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0;37m",&buffersize);

	} else if(strcmp(additional_parameter, "red") == 0){
		sys_req(WRITE,DEFAULT_DEVICE,"\033[0;31m",&buffersize);


	} else if(strcmp(additional_parameter, "blue") == 0){
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0;34m",&buffersize);


	}else if (strcmp(additional_parameter, "purple") == 0)
	{
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0;35m",&buffersize);

	} else if (strcmp(additional_parameter, "green") == 0)
	{
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0;32m",&buffersize);

	}else if (strcmp(additional_parameter, "black") == 0)
	{
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0;30m",&buffersize);

	}
	else if (strcmp(additional_parameter, "reset") == 0)
	{
					sys_req(WRITE,DEFAULT_DEVICE,"\033[0m",&buffersize);

	}

}

