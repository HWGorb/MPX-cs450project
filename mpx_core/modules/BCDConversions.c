#include <system.h>
#include "BCDConversions.h"

/** BCDtoInt
 * converts a value stored as BCD (unsigned char) to an integer
 * Inputs:	c - BCD value to be converted
 * Outputs: result - converted value as an integer
 */
int BCDtoInt(unsigned char c){
	unsigned char left_half;
	unsigned char right_half;
	int result;
	
	//isolate left 4 bits and ensure only the those bits can be nonzero
	left_half = (c >> 4) & 15; // (XXXX YYYY) & 0000 1111 --> (???? XXXX) & 0000 1111 --> 0000 XXXX
	
	//isolate right 4 bits and ensure only the those bits can be nonzero
	right_half = c & 15; // (XXXX YYYY) & 0000 1111 --> 0000 YYYY
	
	//The left half represents the "tens" place, so multiply it by 10 and add to the right half
	//end Expanded Form, "Tens + Ones" is equivalent to "(left_half*10) + right_half"
	result = (left_half*10) + right_half;
	
	return result;
}//end function

/** InttoBCD
 * converts a value stored as integer to BCD (unsigned char)
 * Inputs:	i - integer value to be converted
 * Outputs: result - converted value as BCD
 */
unsigned char InttoBCD(int i) {

	unsigned char result;
	//BCD tens place
	unsigned int left_half;

	//BCD ones place
	unsigned int right_half;


	//extract ones place and tens place and process
	left_half = (i/10) << 4 ; // (i/10) --> (???? XXXX) & 1111 0000--> (XXXX ????) % 1111 0000 --> XXXX 0000
	right_half = (i % 10); //(i%10) --> (???? YYYY) & 0000 1111 --> 0000 YYYY

	result = left_half | right_half; // (XXXX 0000) + (0000 YYYY) --> XXXX YYYY
	return result;
}