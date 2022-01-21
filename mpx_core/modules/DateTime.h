#ifndef _DATETIME_H
#define _DATETIME_H

#include <system.h>

void settime(char* time);
void setdate(char* date);
void gettime(char* args);
void getdate(char* args);
int isLeapYear (int year);
int gettimeseconds();
#endif
