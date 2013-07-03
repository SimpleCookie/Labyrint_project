#ifndef _LINUX_
#define _LINUX_
#include <cstdlib>
#include <termios.h>

struct COORD{
	short X,Y;
	COORD(short x=0, short y=0):X(x),Y(y){}
};
class SMALL_RECT{
public:
	short Left, Right, Top, Bottom;
};


typedef wchar_t WCHAR;
typedef char CHAR;
typedef unsigned short WORD;

#ifndef KBHITh
#define KBHITh

class keyboard {
public:

      keyboard();
    ~keyboard();
    int kbhit();
    int getch();

    int peek_character;
private:

    struct termios initial_settings, new_settings;

};

#endif

void Sleep(float ms);
bool GetAsyncKeyState(int key);
#define VK_UP "\033[A"    // W-key
#define VK_LEFT "\033[D"  // A-key
#define VK_DOWN "\033[B"  // S-key
#define VK_RIGHT "\033[C" // D-key
#define VK_ESCAPE 27
#define VK_RETURN 10
#define VK_SPACEBAR 32

// Cursor settings
#define SAVE_CURSOR_POSITION "\033[s"
#define RESTORE_CURSOR_POSITION "\033[u"

// ANSI ESC Codes

#endif
