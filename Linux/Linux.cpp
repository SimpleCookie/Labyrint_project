#include <iostream>
#include <unistd.h>
#include "Linux.h"

keyboard::keyboard() {
	if(tcgetattr(0,&initial_settings) == -1) return;
	new_settings = initial_settings;
	new_settings.c_iflag &= ~IGNBRK;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	// new_settings.c_lflag &= ~ISIG; // <CTRL-C>
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	if(tcsetattr(0, TCSANOW, &new_settings) == -1) return;
	peek_character=-1;
}

keyboard::~keyboard() {
	tcsetattr(0, TCSANOW, &initial_settings);
}

int keyboard::kbhit() {
	unsigned char ch;
	int nread;

	if (peek_character != -1) return 1;
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);

	if (nread == 1)
	{
		peek_character = ch;
		return 1;
	}
	return 0;
}  

int keyboard::getch() {
	char ch;

	if (peek_character != -1) {
		ch = peek_character;
		peek_character = -1;
	} else read(0,&ch,1);

	return ch;
}


void Sleep(float ms){
	usleep(ms*1000);
}
bool GetAsyncKeyState(int key){
	keyboard k;
	if(k.kbhit()){
		//std::cout << k.peek_character << std::endl;
		//return 27;
		int ret;
		while(k.kbhit())
			ret = k.getch();
		return ret == key;
	}
	return false;
}
