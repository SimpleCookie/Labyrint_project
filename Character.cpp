
#include "Character.h"

const char Character::TECKEN = 'T';

Character::Character():x(1),y(1) {
	
}

Character & Character::walkUp(){
	if(y>0)
		y--;
	return *this;
}
Character & Character::walkDown(){
	y++;
	return *this;
}
Character & Character::walkLeft(){
	if(x>0)
		x--;
	return *this;
}
Character & Character::walkRight(){
	x++;
	return *this;
}