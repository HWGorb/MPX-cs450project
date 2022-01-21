/*
  ----- serial.c -----

  Description..: Contains methods and variables used for
    serial input and output.
*/

#include <stdint.h>
#include <string.h>

#include <core/io.h>
#include <core/serial.h>
#include "modules/mpx_supt.h"


#define NO_ERROR 0

// Active devices used for serial I/O
int serial_port_out = 0;
int serial_port_in = 0;

/*`
  Procedure..: init_serial
  Description..: Initializes devices for user interaction, logging, ...
*/
int init_serial(int device)
{
  outb(device + 1, 0x00); //disable interrupts
  outb(device + 3, 0x80); //set line control register
  outb(device + 0, 115200/9600); //set bsd least sig bit
  outb(device + 1, 0x00); //brd most significant bit
  outb(device + 3, 0x03); //lock divisor; 8bits, no parity, one stop
  outb(device + 2, 0xC7); //enable fifo, clear, 14byte threshold
  outb(device + 4, 0x0B); //enable interrupts, rts/dsr set
  (void)inb(device);      //read bit to reset port
  return NO_ERROR;
}

/*
  Procedure..: serial_println
  Description..: Writes a message to the active serial output device.
    Appends a newline character.
*/
int serial_println(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  outb(serial_port_out,'\r');
  outb(serial_port_out,'\n');  
  return NO_ERROR;
}

/*
  Procedure..: serial_print
  Description..: Writes a message to the active serial output device.
*/
int serial_print(const char *msg)
{
  int i;
  for(i=0; *(i+msg)!='\0'; i++){
    outb(serial_port_out,*(i+msg));
  }
  if (*msg == '\r') outb(serial_port_out,'\n');
  return NO_ERROR;
}

/*int (*student_read)(char *buffer, int *count);
  Procedure..: set_serial_out
  Description..: Sets serial_port_out to the given device address.
    All serial output, such as that from serial_println, will be
    directed to this device.
*/
int set_serial_out(int device)
{
  serial_port_out = device;
  return NO_ERROR;
}

/*
  Procedure..: set_serial_in
  Description..: Sets serial_port_in to the given device address.
    All serial input, such as console input via a virtual machine,
    QEMU/Bochs/etc, will be directed to this device.
*/
int set_serial_in(int device)
{
  serial_port_in = device;
  return NO_ERROR;
}

struct history *current=NULL;
int *polling(char *buffer, int *count){
  //count should contain max character count that can be stored in the buffer. should return the number of characters that were
  //entered into the buffer
  
  /*
  ESC       = "\033"
  up arrow  = "\033[A" 
  down      = "\033[B"
  right     = "\033[C"
  left      = "\033[D"
  */

  
  char special[10] = {'\0'};
  int loc = 0;
  int endline = 0;
    
  while(1)
  {
    char letter = ' ';
    if (inb(COM1+5)&1)
      {
        letter = inb(COM1);
        //START OF ESCAPE SEQUENCE
        if (letter=='\33' || letter=='[')
        {
          //serial_print("here");
          append(special,letter);
        }
        //A=UP, B=DOWN, C=RIGHT, D=LEFT
        else if (special[0] == '\033')
        {
          if(letter=='A' || letter=='B' || letter=='C' || 
            letter=='D' || letter=='3' || letter=='~')
            append(special,letter);
        }
        //printing char to terminal AND storing in buffer
        else
        {
          if(letter!='\177' && letter != '\15')
          {
            //buffer[loc]=letter;
            char temp = 0;
            if(loc < endline)
            {
              int i = 0;
              for(i=loc; i<=endline; i++)
              {
                temp = buffer[i];
                buffer[i] = letter;
                letter=temp;
              }
              serial_print("\033[s");//saves cursor position
              serial_print("\033[0F");//movescursor to beginning and line up
              serial_print("\033[0E");//moves cursor to beginning and line back down to original. no command just to move cursor to beginning of original line
              serial_print("\033[K");//erases line
              serial_print(buffer);
              serial_print("\033[u");//restores cursor pos
              serial_print("\033[C");
            }
            else
            {
              buffer[loc]=letter;
              serial_print(&letter); 
            }
            loc++;
            endline++;
          }
        }
        /**
        *DELETE AND BACKSPACE
        *checks if special = delete and the buffer isn't at the end of the line
        *OR checks if letter = backspace sequence and the char to be deleted isnt null and location is greater than 0
        */
        if((strcmp(special,"\033[3~")==0 && buffer[loc]!='\0') || (letter=='\177' && buffer[loc-1]!='\0' && loc >0))
        {
          serial_print("\033[s");//saves cursor position
          int i,x;
          if(strcmp(special,"\033[3~")==0)
            x=loc;
          else
            x=--loc;
          for(i=x;i<endline;i++)
          {
            buffer[i] = buffer[i+1];
          }
          //since everything is being moved down one, replaces the last character that now shouldnt be there
          buffer[endline--] = '\0';
          serial_print("\033[0F");//movescursor to beginning and line up
          serial_print("\033[0E");//moves cursor to beginning and line back down to original. no command just to move cursor to beginning of original line
          serial_print("\033[K");//erases line
          serial_print(buffer);
          serial_print("\033[u");//restores cursor pos
          //checks if backspace,then moves cursor to left
          if(letter=='\177')
            serial_print("\033[D");
          memset(special,'\0',10);
        }
        //resets special because the above if skips delete but the escape stays in special
        if(strcmp(special,"\033[3~")==0 && buffer[loc]=='\0')
          memset(special,'\0',10);

        //ARROW KEYS
        if (strcmp(special,"\033[A")==0 || strcmp(special,"\033[B")==0|| strcmp(special,"\033[C")==0 || strcmp(special,"\033[D")==0)
        {
          if(strcmp(special,"\033[C")==0 && loc != endline)
          {
            serial_print(special);
            loc++;
          }
          else if(strcmp(special, "\033[D")==0 && loc != 0)
          {
            serial_print(special);
            loc--;
          }
          /*
          else if(strcmp(special, "\033[A")==0 && current->prev != NULL)
          {
            current = current->prev;
            serial_print("\033[0F");//movescursor to beginning and line up
            serial_print("\033[0E");//moves cursor to beginning and line back down to original. no command just to move cursor to beginning of original line
            serial_print("\033[K");//erases line
            strcpy(buffer, current->buffer);
            loc = strlen(buffer);
            endline = strlen(buffer);
            serial_print(buffer);
          }
          else if(strcmp(special, "\033[B")==0)// && current->next != NULL)
          {
            if(current->next->next != NULL)
            {

              current = current->next;
              serial_print("\033[0F");//movescursor to beginning and line up
              serial_print("\033[0E");//moves cursor to beginning and line back down to original. no command just to move cursor to beginning of original line
              serial_print("\033[K");//erases line
              strcpy(buffer, current->buffer);
              loc = strlen(buffer);
              endline = strlen(buffer);
              serial_print(buffer);
              //serial_print("not ");
            }
            else
            {
              serial_print("\033[0F");//movescursor to beginning and line up
              serial_print("\033[0E");//moves cursor to beginning and line back down to original. no command just to move cursor to beginning of original line
              serial_print("\033[K");//erases line
              memset(buffer,'\0',100);
              loc = 0;
              endline = 0;
            }
            
            
          }
          */
          memset(special,0,10);
        }
        //ENTER
        if (letter=='\15')
        {//working correctly
         // insertAtEnd(&current,buffer);
          serial_print("\r");
          
          break;
        }
        //handles a-d getting put in special when just normally pressed
        if(special[0] != '\033')
        {
          memset(special,0,10);
        } 
      }
  }
// insert your code to gather keyboard input via the technique of polling.
// You must validat each key and handle special keys such as delete, back space, and
// arrow keys

count = (int *)endline;
return count;
}

void append(char* s, char c)
{
  int len = strlen(s);
  s[len]=c;
  s[len+1]='\0';
}

//push the buffer onto the history linked list 
//current needs to always be at the end and empty buffer
void insertAtEnd(struct history** current, char *newdata) 
{
  struct history* temp = (struct history*) sys_alloc_mem(sizeof(struct history));
  temp->buffer = sys_alloc_mem(200);
  //this empty node allows for command history access of most recent command, otherwise inaccessible
  struct history* newcurrent = (struct history*) sys_alloc_mem(sizeof(struct history));
  newcurrent->buffer = sys_alloc_mem(200);

  struct history *last = *current;
  strcpy(temp->buffer, newdata);
  temp->next = NULL;
  if(*current == NULL)
  {
    temp->prev = NULL;
    temp->next = newcurrent;
    newcurrent->prev = temp;

    //the current element should be the last one and should now be empty
    *current = newcurrent;
    return;
  }
  while(last->next != NULL)
    last = last->next;
  
  //go back one to overwrite the empty node
  last = last->prev;

  last->next = temp;

  temp->prev = last;
  temp->next = newcurrent;
  newcurrent->prev = temp;
  *current = newcurrent;
  
  return;
}


