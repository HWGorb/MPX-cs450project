#include "itoa.h"

#include <system.h>
#include "mpx_supt.h"
#include <mem/heap.h>

void itoa (int i, char* buffer) {
	
	//The implemented method naturally returns the integer as a reversed string
	//(e.g. 1234 --> "4321"), hence the existence of reverse

	char reverse[12];
	
	if (i == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
	} else {
		//instantiate character count so that terminating character is placed correctly
		int revCount = 0;
		int buffCount = 0;
		
		//copy absolute value of i into function
		int num = (i >= 0) ? (i) : (i*-1);
		
		//instantiate remainder for modulo calculations
		int rem = 0;
	
		
		//convert to string by extracting from num digit by digit and concatenating
		//digit to temporary char array (reverse)
		while (num > 0) {
			//add 48 to result of modulo to convert from int to ascii code for digit
			//48 --> '0', 49 --> '1', ...
			//num % 10 will always be 0-9
			rem = (num % 10) + 48;
			
			//save digit in reverse array
			reverse[revCount] = rem;
			
			//integer division cuts off last digit of number
			num = num/10;
			revCount++;
		}
		
		//check if (i < 0). If true, add a preceding negative to the buffer
		if (i < 0) {
			buffer[buffCount] = '-';
			buffCount++;
		}//end if
		
        //modify revCount since above while loop increments it one too many times
        revCount--;

		//fill buffer with the reversed string, in reverse
		for (;revCount >= 0; revCount--) {
			buffer[buffCount] = reverse[revCount];
			buffCount++;
		}//end for
		
		//ensure last character in string is '\0'
        buffer[buffCount] = '\0';
		
	}//end if...else
	
}//end function`
char* itoareturn (int i) 
{
	//The implemented method naturally returns the integer as a reversed string
	//(e.g. 1234 --> "4321"), hence the existence of reverse

	char reverse[12];
	char buffer[12];
	if (i == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
	} else {
		//instantiate character count so that terminating character is placed correctly
		int revCount = 0;
		int buffCount = 0;
		
		//copy absolute value of i into function
		int num = (i >= 0) ? (i) : (i*-1);
		
		//instantiate remainder for modulo calculations
		int rem = 0;
	
		
		//convert to string by extracting from num digit by digit and concatenating
		//digit to temporary char array (reverse)
		while (num > 0) {
			//add 48 to result of modulo to convert from int to ascii code for digit
			//48 --> '0', 49 --> '1', ...
			//num % 10 will always be 0-9
			rem = (num % 10) + 48;
			
			//save digit in reverse array
			reverse[revCount] = rem;
			
			//integer division cuts off last digit of number
			num = num/10;
			revCount++;
		}
		
		//check if (i < 0). If true, add a preceding negative to the buffer
		if (i < 0) {
			buffer[buffCount] = '-';
			buffCount++;
		}//end if
		
        //modify revCount since above while loop increments it one too many times
        revCount--;

		//fill buffer with the reversed string, in reverse
		for (;revCount >= 0; revCount--) {
			buffer[buffCount] = reverse[revCount];
			buffCount++;
		}//end for
		
		//ensure last character in string is '\0'
        buffer[buffCount] = '\0';
		
	}//end if...else
	//sys_free_mem(buffer);
	char* temp = buffer;
	return temp;
}//end function
