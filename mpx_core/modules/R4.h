#ifndef _R4_H
#define _R4_H
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
#include "R2.h"
#include <core/io.h>
#include "BCDConversions.h"
#include "itoa.h"

struct alarm
{
	//message to be printed when alarm hits
	char message[20];
	//time in seconds for alarm to go off
	int time;
	struct alarm* NextPtr;
	struct alarm* PrevPtr;
};

struct alList {
	int numAlarms;
	struct alarm* head;
	struct alarm* tail;
};
void alarm();
void checkAlarm();
void createAlarm(char *message, char* time);
void infinite();
void createInfinite();
int convertsec(char* time);
void insertalarm(struct alarm* al);
void removealarm(struct alarm *pointer);

#endif