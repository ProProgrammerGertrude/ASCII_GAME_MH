// HTL_Konsole.h

#ifndef _INC_HTL
#define _INC_HTL

#define WIN32_LEAN_AND_MEAN			// Selten verwendete Teile der Windows-Header nicht einbinden.
#define _WIN32_WINNT 0x0500			// wegen GetConsoleWindow
#include <windows.h>				// Windows-API
#pragma warning(disable:4996)		// Warnings ausschalten (getch(), ...)
#include <iostream>
using namespace std;				// cin, cout, ...

extern void clrscr();				// Funktionsprototypen
extern void gotoxy(int x, int y);
extern void cursoroff();
extern void cursoron();
extern void setcolor(int color);

// Farbkonstanten
#define CONSOLE_BLACK			0
#define CONSOLE_BLUE			1
#define CONSOLE_GREEN			2
#define CONSOLE_CYAN			3
#define CONSOLE_RED				4
#define CONSOLE_MAGENTA			5
#define CONSOLE_BROWN			6
#define CONSOLE_LIGHTGRAY		7
#define CONSOLE_DARKGRAY		8
#define CONSOLE_LIGHTBLUE		9
#define CONSOLE_LIGHTGREEN		10
#define CONSOLE_LIGHTCYAN		11
#define CONSOLE_LIGHTRED		12
#define CONSOLE_LIGHTMAGENTA	13
#define CONSOLE_YELLOW			14
#define CONSOLE_WHITE			15

#endif  /* _INC_HTL */
