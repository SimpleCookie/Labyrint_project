
#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
	static const char TECKEN;
	Character();
	Character & walkUp();
	Character & walkDown();
	Character & walkLeft();
	Character & walkRight();

	int getX() const{return x;}
	int getY() const{return y;}
private:
	int x,y;	// positions, a coordinate to describe the characters current position
};

#endif
