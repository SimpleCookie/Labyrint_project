#include <iostream>
#include "Inputs.h"
#include <string>
int Check_valid_size(std::string value){
	int size;
	// If it cannot be converted to an int, return false
	if (!(size = std::stoi(value)))
		return 0;
	// If it's a negative number and less than 3, convert it to positive
	if (size < -3)
		size *= -1;
	// If size is in the intervall [3, -3], return false
	if (size < 3 && size > -3)
		return 0;
	return size;
}

