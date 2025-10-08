// HTL_Konsole.cpp

#include "HTL_Konsole.h"

// Bildschirm löschen
void clrscr()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	GetConsoleScreenBufferInfo( hConsole, &csbi );
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter( hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition( hConsole, coordScreen );
}

// Den Cursor auf dem Konsolenfenster an eine bestimmte Position bewegen
void gotoxy(int x, int y)
{
    COORD point;
    point.X = x-1; point.Y = y-1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), point );
}

// Den Cursor ausschalten
void cursoroff()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hOut, &ConCurInf);

    ConCurInf.bVisible = FALSE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}

// Den Cursor einschalten
void cursoron()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hOut, &ConCurInf);

    ConCurInf.bVisible = TRUE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}

// Textfarbe setzen
void setcolor(int color)
{
	WORD wColor; 

    //We will need this handle to get the current background attribute
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
     
    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
		//Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);     
	}
}

