#include <iostream>
#include "Inputs.h"
#include <string>
int Check_valid_size(unsigned int size){
	// If size is in the intervall [3, -3], return false
	if (size <= 3)
		return 0;
	return size;
}

