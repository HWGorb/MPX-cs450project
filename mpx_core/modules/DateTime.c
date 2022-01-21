#include <system.h>
#include <string.h>
#include "DateTime.h"
#include "mpx_supt.h"

#include <core/io.h>
#include "BCDConversions.h"
#include "itoa.h"

/** getdate
 * extracts and formats the date in mm/dd/yyyy format from RTC registers
 * Inputs:	date - character array (buffer) to write date into
 */
void getdate(char* args) {
	//disable interrupts
	cli();

	char date[11];

	char* delim = " ";
	char* arg_check = strtok(args, delim);
	int bufferSize;

	if (arg_check == NULL) {
		//declare temporary variable for grabbing from register
		unsigned char tempByte;
		int tempByteInt;
		
		//////////////////////////////////////////////////////////////
		//Grabbing  Month                                           //
		//////////////////////////////////////////////////////////////
		outb(0x70, 0x08);
		
		//read value from location 0x71 for month
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		
		//handle padding with zeroes if month is a single digit and
		//offset date by 4 to write to correct location, otherwise
		//offset by 3 to write to correct location
		
		//handle padding with zeroes if day is a single digit and
		//offset date by 1 to write to correct location
		if (tempByteInt < 10) {
			date[0] = '0';
			itoa(tempByteInt, date + 1);
		} else {
			itoa(tempByteInt, date);
			

		}//end if..else
		

		//////////////////////////////////////////////////////////////
		//Grabbing  Day                                             //
		//////////////////////////////////////////////////////////////
		
		//write value to RTC index register(0x07) to grab day
		outb(0x70, 0x07);
		
		//read value from location 0x71 for day
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		
		
		if (tempByteInt < 10) {
			date[3] = '0';
			itoa(tempByteInt, date + 4);
		} else {
			itoa(tempByteInt, date + 3);
		}//end if..else
		
		
		//////////////////////////////////////////////////////////////
		//Grabbing  Year                                             //
		//////////////////////////////////////////////////////////////
		
		//upper two digits of year
		outb(0x70, 0x32);
		
		//read value from location 0x32 for upper two digits of year
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		
		if (tempByteInt < 10) {
			itoa(0, date + 6);
			itoa(tempByteInt, date + 7);
		} else {
			itoa(tempByteInt, date + 6);	
		}
		//lower two digits of year
		outb(0x70, 0x09);
		
		//read value from location 0x09 for lower two digits of year
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		
		if (tempByteInt < 10) {
			itoa(0, date + 8);
			itoa(tempByteInt, date + 9);
		} else {
			itoa(tempByteInt, date + 8);	
		}
		
		//set specific characters of date to '/' and '\0' for formatting
		date[2] = '/';
		date[5] = '/';
		date[10] = '\0';

		bufferSize = 11;
		sys_req(WRITE,DEFAULT_DEVICE,date, &bufferSize);
		bufferSize = 2;
		sys_req(WRITE,DEFAULT_DEVICE,"\n", &bufferSize);
	} else {
		bufferSize = 57;
		sys_req(WRITE, DEFAULT_DEVICE, "Invalid arguments passed to getdate. Use syntax\ngetdate\n", &bufferSize);
	}

	//reenable intterupts
	sti();
}//end function


/** gettime
 * extracts and formats the time in hh:mm:ss format from RTC registers
 * Inputs:	time - character array (buffer) to write time into
 */
void gettime(char* args) {
	//disable interrupts
	cli();
	
	char time[9];
	char* delim = " ";
	char* arg_check = strtok(args, delim);
	int bufferSize;

	if (arg_check == NULL) {
		//declare temporary variable for grabbing from register
		unsigned char tempByte;
		int tempByteInt;

		//////////////////////////////////////////////////////////////
		//Grabbing  Hours                                            //
		//////////////////////////////////////////////////////////////
		
		//write value to RTC index register(0x04) to grab hours
		outb(0x70, 0x04);
		
		//read value from location 0x71 for hours
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		 
		//handle padding with zeroes if hours is a single digit
		//offset time by 1 to write to correct location
		if (tempByteInt < 10) {
			time[0] = '0';
			itoa(tempByteInt, time + 1);
		} else {
			itoa(tempByteInt, time);
		}//end if..else
		
		
		//////////////////////////////////////////////////////////////
		//Grabbing  Minutes                                         //
		//////////////////////////////////////////////////////////////
		
		//write value to RTC index register(0x02) to grab hours
		outb(0x70, 0x02);
		
		//read value from location 0x71 for minutes
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		 
		//handle padding with zeroes if hours is a single digit
		//offset time by 4 to write to correct location, otherwise
		//offset by 3 to write to correct location
		if (tempByteInt < 10) {
			time[3] = '0';
			itoa(tempByteInt, time + 4);
		} else {
			itoa(tempByteInt, time + 3);
		}//end if..else
		

		//////////////////////////////////////////////////////////////
		//Grabbing  Seconds                                         //
		//////////////////////////////////////////////////////////////
		
		//write value to RTC index register(0x02) to grab hours
		outb(0x70, 0x00);
		
		//read value from location 0x71 for seconds
		tempByte = inb(0x71);
		tempByteInt = BCDtoInt(tempByte);
		 
		//handle padding with zeroes if seconds is a single digit
		//offset time by 7 to write to correct location, otherwise
		//offset by 6 to write to correct location
		if (tempByteInt < 10) {
			time[6] = '0';
			itoa(tempByteInt, time + 7);
		} else {
			itoa(tempByteInt, time + 6);
		}//end if..else

		
 		//set specific characters of date to ':' and '\0' for formatting
		time[2] = ':';
		time[5] = ':';
		time[8] = '\0';

		bufferSize = 9;
		sys_req(WRITE,DEFAULT_DEVICE,time, &bufferSize);
		bufferSize = 2;
		sys_req(WRITE,DEFAULT_DEVICE,"\n", &bufferSize);
	} else {
		bufferSize = 57;
		sys_req(WRITE, DEFAULT_DEVICE, "Invalid arguments passed to gettime. Use syntax\ngettime\n", &bufferSize);
	}		

	//reenable intterupts
	sti();	
}//end function

/** setdate
 * sets the system date to the given point in time
 * Inputs:	date - character array containing date to set system date to in mm/dd/yyyy format
 */
void setdate(char* date) {
	//disable interrupts
	cli();
	
	char* delim = "/";
	char* temp;

	char month[10];
	memset(month, '\0', 10);
	temp = strtok(date, delim);
	strcpy(month, temp);

	char day[10];
	memset(day, '\0', 10);
	temp = strtok(NULL, delim);
	strcpy(day, temp);

	char year[10];
	memset(year, '\0', 10);
	temp = strtok(NULL, delim);
	strcpy(year, temp);

	unsigned char tempByte;
	int tempByteInt;
	int bufferSize;
	char* tempStr = "";

	//check date validity
	if ((month[0] == '\0') || !(strcmp(day, NULL)) || !(strcmp(year, NULL))) {
		bufferSize = 58;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid syntax on setdate. Use syntax\nsetdate mm/dd/yyyy\n", &bufferSize); //invalid syntax
	} else if ((atoi(day) < 1) || (atoi(day) > 31)) { //invalid days in general
		bufferSize = 30;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid day used on setdate.\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,month)) < 1) || (atoi(strcpy(tempStr,month)) > 12)) { // invalid months
		bufferSize = 32;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid month used on setdate.\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,year)) < 1980) || (atoi(strcpy(tempStr,year)) > 2255)) { //invalid years
		bufferSize = 31;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid year used on setdate.\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,day)) > 28) && (atoi(strcpy(tempStr,month)) == 2) && isLeapYear(atoi(strcpy(tempStr,year))) == 0) { //invalid day in February if not a leap year
		bufferSize = 55;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid day used for the month of February on setdate\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,day)) > 29) && (atoi(strcpy(tempStr,month)) == 2) && isLeapYear(atoi(strcpy(tempStr,year)))) { //invalid day in February on a leap year
		bufferSize = 55;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid day used for the month of February on setdate\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,day)) > 30) && ((atoi(strcpy(tempStr,month)) == 4) || (atoi(strcpy(tempStr,month)) == 6) || (atoi(strcpy(tempStr,month)) == 9) || (atoi(strcpy(tempStr,month)) == 11))) {
		bufferSize = 82;
		sys_req(WRITE,DEFAULT_DEVICE,"Invalid day used for the month of April, June, September, or November on setdate\n", &bufferSize);
	} else {
		
		//////////////////////////////////////////////////////////////
		//Setting  Year                                             //
		//////////////////////////////////////////////////////////////

		//lower two digits of year
		tempByteInt = atoi(year) % 100; //convert to int
		tempByte = InttoBCD(tempByteInt); //convert to BCD

		//write values to 0x71 and 0x70 to set lower two digits of year
		outb(0x70, 0x09);
		outb(0x71, tempByte);


		//upper two digits of year
		
		//convert to int, divide by 100 to isolate upper two digits
		tempByteInt = atoi(year) / 100; 
		tempByte = InttoBCD(tempByteInt); //convert to BCD

		//write values to 0x71 and 0x70 to set upper two digits of year
		outb(0x70, 0x32);
		outb(0x71, tempByte);	


		//////////////////////////////////////////////////////////////
		//Setting  Month                                            //
		//////////////////////////////////////////////////////////////
		tempByteInt = atoi(month); //convert to int
		tempByte = InttoBCD(tempByteInt); //convert to BCD
		
		//write value to index register to set month
		outb(0x70,0x08);

		//write value to 0x71 to set month
		outb(0x71, tempByte);
		

		//////////////////////////////////////////////////////////////
		//Setting  Day                                              //
		//////////////////////////////////////////////////////////////
		tempByteInt = atoi(day); //convert to int
		tempByte = InttoBCD(tempByteInt); //convert to BCD
		
		//write value to index register to set day
		outb(0x70,0x07);

		//write value to 0x71 to set day
		outb(0x71, tempByte);
		
	}//end if..else if
	//reenable interrupts


//	sys_req(WRITE,DEFAULT_DEVICE, month, &bufferSize);
//	sys_req(WRITE,DEFAULT_DEVICE, day, &bufferSize);
//	sys_req(WRITE,DEFAULT_DEVICE, year, &bufferSize);

//	klogv(month);
//	klogv(day);
//	klogv(year);
	sti();

}//end function

/** settime
 * sets the system clock to the given time
 * Inputs:	date - character array containing date to set system date to in hh/mm/ss format
 */
void settime(char* time) {
	//disable interrupts
	cli();
	

	int bufferSize;
	char* tempStr = "";

	//declare temporary variables for setting to register
	unsigned char tempByte;
	int tempByteInt;
	char* delim = ":";
	char* hours = strtok(time, delim);
	char* minutes = strtok(NULL, delim);
	char* seconds = strtok(NULL, delim);

	//check time validity
	if (!(strcmp(hours, NULL)) || !(strcmp(minutes, NULL)) || !(strcmp(seconds, NULL))) {
		bufferSize = 56;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid syntax on settime. Use syntax\nsettime hh:mm:ss\n", &bufferSize); //invalid syntax
	} else if ((atoi(strcpy(tempStr,hours)) < 0) || (atoi(strcpy(tempStr,hours)) > 23)) { //invalid hours
		bufferSize = 30;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid hour used on setime.\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,minutes)) < 0) || (atoi(strcpy(tempStr,minutes)) > 59)) { //invalid hours
		bufferSize = 32;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid minute used on setime.\n", &bufferSize);
	} else if ((atoi(strcpy(tempStr,seconds)) < 0) || (atoi(strcpy(tempStr,seconds)) > 59)) { //invalid hours
		bufferSize = 32;
		sys_req(WRITE,DEFAULT_DEVICE, "Invalid second used on setime.\n", &bufferSize);
	} else {
	//////////////////////////////////////////////////////////////
	//Setting  Hours                                            //
	//////////////////////////////////////////////////////////////
	

	tempByteInt = atoi(hours); //convert to int
	tempByte = InttoBCD(tempByteInt); //convert to BCD
	
	//write value to index register to set hours
	outb(0x70,0x04);

	//write value to 0x71 to set hours
	outb(0x71, tempByte);
	 
	//////////////////////////////////////////////////////////////
	//Setting  Minutes                                          //
	//////////////////////////////////////////////////////////////
	

	tempByteInt = atoi(minutes); //convert to int
	tempByte = InttoBCD(tempByteInt); //convert to BCD
	
	//write value to index register to set Minutes
	outb(0x70,0x02);

	//write value to 0x71 to set hours
	outb(0x71, tempByte);


	//////////////////////////////////////////////////////////////
	//Setting  Seconds                                          //
	//////////////////////////////////////////////////////////////
	

	tempByteInt = atoi(seconds); //convert to int
	tempByte = InttoBCD(tempByteInt); //convert to BCD
	
	//write value to index register to set hours
	outb(0x70,0x00);

	//write value to 0x71 to set hours
	outb(0x71, tempByte);
}
	//reenable interrupts
	sti();
}//end function


/** isLeapYear
 * checks to see if given year is a leap year
 * Inputs:	year - year to check as an integer
 * Outputs: 0 if the year is not a leap year, 1 if it is a leap year
 */
int isLeapYear(int year) {
	int result = 0;

	//a year is a leap year if it is divisible by 4 and not divisble by 100, unless it is also divisible by 400
	if (year % 4 == 0) {

		if (year % 100 == 0) {

			if (year % 400 == 0) {
				result = 1;

			} else {
				result = 0;
			}//end 400 check

		} else {
			result = 1;
		}//end 100 check

	} else {
		result = 0;
	}//end 4 check
return result;
}//end function


/** gettimeseconds
 * extracts and calculates current time in seconds
 * Outputs:	result - current time in seconds
 */
int gettimeseconds() {
	//disable interrupts
	cli();

	int result = 0;


	//////////////////////////////////////////////////////////////
	//Grabbing  Hours                                            //
	//////////////////////////////////////////////////////////////
	
	//write value to RTC index register(0x04) to grab hours
	outb(0x70, 0x04);
	
	//read value from location 0x71 for hours
	//convert to seconds, add to result
	result = result + BCDtoInt(inb(0x71)) * 3600;
	

	//////////////////////////////////////////////////////////////
	//Grabbing  Minutes                                         //
	//////////////////////////////////////////////////////////////
	
	//write value to RTC index register(0x02) to grab minutes
	outb(0x70, 0x02);
		
	//read value from location 0x71 for minutes
	//convert to seconds, add to result
	result = result + BCDtoInt(inb(0x71)) * 60;


	//////////////////////////////////////////////////////////////
	//Grabbing  Seconds                                         //
	//////////////////////////////////////////////////////////////
		
	//write value to RTC index register(0x00) to grab seconds
	outb(0x70, 0x00);
	
	//read value from location 0x71 for hours
	//convert to seconds, add to result
	result = result + BCDtoInt(inb(0x71));

	//reenable intterupts
	sti();	

	return result;
}//end function