#include <stdio.h>
#include <conio.h>
#include "HTL_Konsole.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <set>
#include <cmath>
#include <stack>
#include "Map_Array.h"
#include <vector>
#include "Zombie.h"
#include "GameFunctions.h"

#define w 119
#define UP 72
#define a 97
#define LEFT 75
#define s 115
#define RIGHT 80
#define d 100
#define DOWN 77
#define SPACEBAR  32
#define e 101
#define ROWS 47
#define COLS 162
#define PlayerSize 4
#define HowManyZombiesExist 8
int PlayerX = 10;//62 //42 //115 // 55 // 10
int PlayerY = 29;//17 // 11 //16 // 29 // 29

using namespace std;

void PlayersMovement(int& input, int abbruch, int& area, int& sword, char starterArea[][COLS], int& lastNumberPressed, int& swordAnimationPhase, int inventory[], int& swordCooldown, int firstTimeInArea[], Zombie zombies[]);
int Borders(int area, int& abbruch, char starterArea[][COLS], int input, int& sword, int lastNumberPressed);
void ECheck(int area, char starterArea[][COLS], int sword, int lastNumberPressed, int input);
void Sword(int sword, int& lastNumberPressed, int input, char starterArea[][COLS]);
void WaitingTime(int& waitForNextMove, int& waitForSwordAnimation, int lastNumberPressed, int& swordCooldown, Zombie zombies[]);
void swordAnimations(int lastNumberPressed, char starterArea[][COLS], int swordAnimationPhase, int area, Zombie& zombie);
void HitCheck(int SwordX, int SwordY, int area, Zombie& zombie, int howFar, int lastNumberPressed);
void ChangeArea(int& area, char starterArea[][COLS], int firstTimeInArea[],int inventory[], Zombie zombies[]);
void BoxMaker(char starterArea[][COLS], int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int value, char zeichen);
void TextPrinter(int x, int y, char* text, int time);
void ZombieMoves(Zombie zombies[], int area, int i, int& win);
void AttackCheck(Zombie zombies[], int& swordAnimationPhase, int& waitForSwordAnimation, int& swordCooldown, int lastNumberPressed, int area);
void PrintRemover(char starterArea[][COLS], int x, int y);

int main()
{
    SetConsoleOutputCP(CP_UTF8);


    int win = 0;
    int input = 0;
    int area = 1;
    int abbruch = 0;
    int sword = 1;
    int swordAnimationPhase = 0;
    int waitForSwordAnimation = 0;
    int swordCooldown = 0;
    int testchange = 0;
    int lastNumberPressed = 5;
    //0: labdoor, 1: laptop looked at // 2: acids // 3: cleaning fluids // 4: Sample Jar // 5: Gloves // 6: screwdriver // 7: Clamps // 8: EG key 
    //9: generator, // 10 code4Key // 11: philips key
    int inventory[12] = { 0 };
    int waitForNextMove = 0;
    int firstTimeInArea[6] = { 0 };
    cursoroff();
    
 

    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    Sleep(500);

    srand((unsigned)time(NULL));
    

    gotoxy(PlayerX, PlayerY);
    printf("[\xC2\xB0-\xC2\xB0]");

    // X, Y, life, armor, damage, startspeed, speed, waitingtime, size, zombieDeathValue, area
    Zombie zombies[HowManyZombiesExist] = 
    {
         Zombie( 54, 27, 3, 1, 2, 20, 20,  7, 7, 20, 1), // zombie0 //Doctor
         Zombie(120, 29, 3, 1, 2, 20, 20,  5, 7, 10, 1), // zombie1
         Zombie(125,  7, 1, 1, 2, 10, 10,  0, 7, 10, 2), // zombie2 (Hallway)
         Zombie(  2,  4, 2, 1, 2, 20, 20,  2, 7, 10, 3), // zombie3 (storage)
         Zombie( 55, 15, 2, 1, 2, 20, 20,  5, 7, 10, 3), // zombie4 (storage)
         Zombie( 59,  7, 2, 1, 2, 15, 15,  0, 7, 10, 6), // zombie5 (locker)
         Zombie( 82, 28, 1, 1, 2, 50, 50, 30, 7, 10, 6), // zombie6 (locker)
         Zombie( 50,  4, 5, 1, 2, 30, 30, 20, 7, 11, 6)  // zombie7 (locker)
    };

    area = 6;

    if (area == 1)
    {
        PlayerX = 62;
        PlayerY = 17;
    }
    else if (area == 2)
    {
        PlayerX = 42;
        PlayerY = 11;
    }
    else if (area == 3)
    {
        PlayerX = 115;
        PlayerY = 16;
    }
    else if (area == 4)
    {
        PlayerX = 55;
        PlayerY = 29;
    }
    else if (area == 5)
    {
        PlayerX = 10;
        PlayerY = 29;
    }
    else if (area == 6)
    {
        PlayerX = 47;
        PlayerY = 29;
    }
    ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
    cursoroff();

    while (win == 0)
    {

        ZombieMoves(zombies, area, -1, win);
        
        
        
        if (_kbhit()) {
            if (waitForNextMove == 0 && swordAnimationPhase == 0)
            {
                input = _getch();
                PlayersMovement(input, abbruch, area, sword, starterArea, lastNumberPressed, swordAnimationPhase, inventory, swordCooldown, firstTimeInArea, zombies);
                ECheck(area, starterArea, sword, lastNumberPressed, input);
                waitForNextMove = 6;
            }
        }

        AttackCheck(zombies, swordAnimationPhase, waitForSwordAnimation, swordCooldown, lastNumberPressed, area);


        //AreaOfMap(area, playerX, playerY, starterArea);
        Sleep(1);
        WaitingTime(waitForNextMove, waitForSwordAnimation, lastNumberPressed, swordCooldown, zombies);
        

    }

    //gotoxy(5, 46);
    //printf("OHHHHH P.DIDDY NOOOOOOOOOOOO"),
    Sleep(5000);
}


void AttackCheck(Zombie zombies[], int& swordAnimationPhase, int& waitForSwordAnimation, int& swordCooldown, int lastNumberPressed, int area)
{
    if (swordAnimationPhase > 0 && waitForSwordAnimation == 0)
    {
        //printf("%d", swordAnimationPhase);
        if ((lastNumberPressed == 1 || lastNumberPressed == 3) && swordAnimationPhase < 6)
        {
            for (int i = 0; i < HowManyZombiesExist; i++)
            {
                if (area == zombies[i].ZombieArea)
                {
                    swordAnimations(lastNumberPressed, starterArea, swordAnimationPhase, area, zombies[i]);
                    if (zombies[i].Zombielives <= 0)
                    {
                        if ((area == 1 && i < 2) || (area == 2 && i == 2) || ((area == 3 && i >= 3 && i < 5) || (area == 6 && i >= 5 && i < 8)))
                        {
                            for (int j = 0; j < zombies[i].ZombieSize; j++)
                            {
                                starterArea[zombies[i].ZombieposY][zombies[i].ZombieposX + j] = zombies[i].ZombieDeathValue;
                            }
                            gotoxy(zombies[i].ZombieposX, zombies[i].ZombieposY);
                            printf("\033[0;32m[-X_X]-\033[0m");
                        }

                    }
                }
            }

            swordAnimationPhase++;
            waitForSwordAnimation++;
        }
        else if ((lastNumberPressed == 2 || lastNumberPressed == 4) && swordAnimationPhase < 5)
        {
            for (int i = 0; i < HowManyZombiesExist; i++)
            {
                if (area == zombies[i].ZombieArea)
                {
                    swordAnimations(lastNumberPressed, starterArea, swordAnimationPhase, area, zombies[i]);
                    if (zombies[i].Zombielives <= 0)
                    {

                        for (int j = 0; j < zombies[i].ZombieSize; j++)
                        {
                            starterArea[zombies[i].ZombieposY][zombies[i].ZombieposX + j] = zombies[i].ZombieDeathValue;
                        }
                        gotoxy(zombies[i].ZombieposX, zombies[i].ZombieposY);
                        printf("\033[0;32m[-X_X]-\033[0m");
                    }
                }
            }
            swordAnimationPhase++;
            waitForSwordAnimation++;
        }
        else
        {
            swordAnimationPhase = 0;
            waitForSwordAnimation = 0;
            swordCooldown = 30;

        }
    }
}
void PrintRemover(char starterArea[][COLS], int x, int y)
{
    if (starterArea[y][x] == 0)
    {
        gotoxy(x, y);
        printf(" ");
    }
}

// rekursion just because I want to
void ZombieMoves(Zombie zombies[], int area, int i, int& win)
{
    if (i >= HowManyZombiesExist)
        return;
    if (zombies[i].ZombieArea == area)
    {
        // Destination is the left-most top-most corner
        Pair dest = make_pair(PlayerY, PlayerX);

        if (zombies[i].waitForNextZombieMove == 0)
        {



            // Source is the left-most bottom-most corner
            zombies[i].src = make_pair(zombies[i].ZombieposY, zombies[i].ZombieposX);

            if (zombies[i].Zombielives > 0)
            {
                zombies[i].CloseRangeMovement(starterArea, zombies[i].src, dest, zombies[i].waitForNextZombieMove, win, zombies[i].ZombieXMove, zombies[i].ZombieDeathValue);
            }

        }
    }
    
    ZombieMoves(zombies, area, i + 1, win);


}

void TextPrinter(int x, int y, char* text, int time)
{
    int i;
    gotoxy(5, 46);
    printf("                     ");
    gotoxy(x, y);
    printf("%s", text);
    Sleep(time);
    for (i = 0; text[i] != NULL; i++)
    {
        gotoxy(x + i, y);
        printf(" ");
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void BoxMaker(char starterArea[][COLS], int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int value, char zeichen)
{
    int i;
    char forX = ' ';
    char forY = ' ';

    if (zeichen == '_')
    {
        forX = '_';
        forY = '|';
    }
    else if (zeichen == '#')
    {
        forX = '#';
        forY = '#';
    }

    for (i = topLeftX; i <= bottomRightX; i++)
    {

        gotoxy(i, topLeftY);
        printf("%c", forX);
        starterArea[topLeftY][i] = value;

        gotoxy(i, bottomRightY);
        printf("%c", forX);
        starterArea[bottomRightY][i] = value;
    }

    for (i = topLeftY + 1; i <= bottomRightY; i++)
    {

        gotoxy(topLeftX, i);
        printf("%c", forY);
        starterArea[i][topLeftX] = value;

        gotoxy(bottomRightX, i);
        printf("%c", forY);
        starterArea[i][bottomRightX] = value;
    }
}

void ChangeArea(int& area, char starterArea[][COLS], int firstTimeInArea[],int inventory[], Zombie zombies[])
{
    int value = 1;
    system("cls");
    gotoxy(PlayerX, PlayerY);
    printf("[\xC2\xB0-\xC2\xB0]");
    int i = 0;
    int k = 0;
    int j = 0;
    // set everything to 0
    
    for (k = 0; k < ROWS; k++)
    {
        for (i = 0; i < COLS; i++)
        {
            starterArea[k][i] = 0;
        }
    }
    if (area == 1)
    {

        for (i = 0; i < 2; i++)
        {
            if (zombies[i].Zombielives <= 0)
            {
                for (int j = 0; j < zombies[i].ZombieSize; j++)
                {
                    starterArea[zombies[i].ZombieposY][zombies[i].ZombieposX + j] = zombies[i].ZombieDeathValue;
                }
                gotoxy(zombies[i].ZombieposX, zombies[i].ZombieposY);
                printf("\033[0;32m[-X_X]-\033[0m");
            }
        }
        //Boarder
        BoxMaker(starterArea, 4, 1, 136, 45, 1, '_');

        gotoxy(13, 4);
        printf("_________________");
        gotoxy(12, 5);
        printf("| [Shelf]         |");
        gotoxy(12, 6);
        printf("| CH4  NH3  O2    |");
        gotoxy(12, 7);
        printf("| HNO3 KOH AcO    |");
        gotoxy(12, 8);
        printf("|-----------------|");
        gotoxy(12, 9);
        printf("| [Cabinet]       |");
        gotoxy(12, 10);
        printf("| Toxins Solvent  |");
        gotoxy(12, 11);
        printf("| EtOH   MeOH     |");
        gotoxy(12, 12);
        printf("|-----------------|");
        gotoxy(12, 13);
        printf("|[Safety Box]     |");
        gotoxy(12, 14);
        printf("| Gloves  Mask    |");
        gotoxy(12, 15);
        printf("|_________________|");

        for (k = 0; k < 12; k++)
        {
            for (i = 0; i < 20; i++)
            {
                starterArea[4 + k][11 + i] = 2;
            }
        }


        //Bed
        gotoxy(50, 19);
        printf("_________________ _______ ");
        for (i = 0; i < 26; i++) starterArea[19][50 + i] = 8; 
            
        

        for (int i = 0; i < 5; i++) {
            gotoxy(49, i + 20);
            printf("|");
            starterArea[20 + i][49] = 8;
            gotoxy(75, i + 20);
            printf("|");
            starterArea[20 + i][75] = 8;
        }
        gotoxy(60, 22);
        printf("BED");

        for (int i = 0; i < 4; i++)
        {
            gotoxy(67, i + 20);
            printf("|");
        }

        gotoxy(50, 24);
        printf("_________________________");
        for (i = 0; i < 26; i++) starterArea[24][50 + i] = 8;




        gotoxy(21, 33);
        printf("_______________________________________________________________________________________________");
        for (i = 0; i < 96; i++)
        {
            if ((i + 21) >= 25 && (i + 21) < 33)
            {
                starterArea[33][21 + i] = 5;
            }
            else if ((i + 21) >= 38 && (i + 21) < 45)
            {
                starterArea[33][21 + i] = 3;
            }
            else if ((i + 21) >= 53 && (i + 21) < 65)
            {
                starterArea[33][21 + i] = 4;
            }
            else if ((i + 21) >= 71 && (i + 21) < 83)
            {
                starterArea[33][21 + i] = 6;
            }
            else if ((i + 21) >= 91 && (i + 21) < 100)
            {
                starterArea[33][21 + i] = 11;
            }
            else
            {
                starterArea[33][21 + i] = 1;
            }
        }
        for (int i = 0; i < 8; i++)
        {
            gotoxy(20, 34 + i);
            printf("|");
            starterArea[34 + i][20] = 1;
            gotoxy(116, 34 + i);
            printf("|");
            starterArea[34 + i][116] = 1;
        }
        gotoxy(20, 41);
        printf("|_______________________________________________________________________________________________|");
        for (i = 0; i < 97; i++)
        {
            starterArea[41][20 + i] = 1;
        }

        // Microscope
        gotoxy(26, 34);
        printf("__________");
        gotoxy(25, 35);
        printf("|Microscope|");
        gotoxy(25, 36);
        printf("|__________|");
        gotoxy(25, 37);
        printf("|     /    |");
        gotoxy(25, 38);
        printf("|    / )   |");
        gotoxy(25, 39);
        printf("|  _\033[0;31m_\033[0m_|_   |");
        gotoxy(25, 40);
        printf("|__________|");

        //Laptop
        gotoxy(39, 35);
        printf("|\\_      0~");
        gotoxy(39, 36);
        printf("|  \\______");
        gotoxy(39, 37);
        printf("|    |++++|");
        gotoxy(40, 38);
        printf("\\_  |++++|");
        gotoxy(42, 39);
        printf("\\_|____|");
        gotoxy(42, 40);
        printf("Laptop");

        // Sketches
        gotoxy(54, 35);
        printf("_____________");
        gotoxy(53, 36);
        printf("| #§|&|§&!§~} |");
        gotoxy(53, 37);
        printf("| ||§|&~&§³$/ |");
        gotoxy(53, 38);
        printf("| $|§||~{²§&! |");
        gotoxy(53, 39);
        printf("|_____________|");
        gotoxy(57, 40);
        printf("Sketches");

        //¯

        gotoxy(72, 35);
        printf(",");
        gotoxy(71, 36);
        printf("/(_____________");
        gotoxy(70, 37);
        printf("|  >:===========`");
        gotoxy(71, 38);
        printf(")(     Tools");
        gotoxy(71, 39);
        printf("\"\"");



        gotoxy(90, 37);
        printf("Some other sht");

              
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 18; i++) {
            gotoxy(69 + i, 1);
            printf("_");
            starterArea[1][69 + i] = 7;

        }
        setcolor(CONSOLE_WHITE);

    }
    else if (area == 2)
    {
        if (zombies[2].Zombielives <= 0)
        {
            for (int j = 0; j < zombies[2].ZombieSize; j++)
            {
                starterArea[zombies[2].ZombieposY][zombies[2].ZombieposX + j] = zombies[2].ZombieDeathValue;
            }
            gotoxy(zombies[2].ZombieposX, zombies[2].ZombieposY);
            printf("\033[0;32m[-X_X]-\033[0m");
        }

        // second row changed to 1
        
        for (i = 1; i < COLS - 1; i++)
        {
            starterArea[2][i] = 1;
            gotoxy(i, 2);
            printf("_");
        }
       
        // 11the row changed to 1
        for (i = 1; i < COLS - 41; i++)
        {
            starterArea[12][i] = 1;
            gotoxy(i, 12);
            printf("_");
        }
        // Left Row down 
        for (i = 0; i < 10; i++)
        {
            starterArea[i + 3][1] = 1;
            // door to the lagerraum
            if (i >= 3 && i < 7)
            {
                setcolor(CONSOLE_BROWN);
                starterArea[i + 3][1] = 2;
            }
            else
            {
                setcolor(CONSOLE_WHITE);
            }
            gotoxy(1, i + 3);
            printf("|");
        }
        // Right Row all the way down 
        for (i = 0; i < 30; i++)
        {
            starterArea[i + 3][COLS - 1] = 1;
            gotoxy(COLS - 1, i + 3);
            printf("|");
        }
        // the Row for the Right corner
        for (i = 0; i < 20; i++)
        {
            starterArea[i + 13][COLS - 41] = 1;
            gotoxy(COLS - 41, i + 13);
            printf("|");
        }
        //The door to the exit
        for (i = 0; i < 39; i++)
        {
            if (i > 10 && i < 30)
            {
                setcolor(CONSOLE_BROWN);
                value = 3;
            }
            else
            {
                setcolor(CONSOLE_WHITE);
                value = 1;
            }
            starterArea[32][COLS - 40 + i] = value;
            gotoxy(COLS - 40 + i, 32);
            printf("_");
            
        }
        // Door to the lab
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 13; i++) {
            gotoxy(40 + i, 12);
            printf("_");
            starterArea[12][40 + i] = 4;
        }
        setcolor(CONSOLE_WHITE);
        // Door to the closet
        
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 10; i++) {
            gotoxy(112 + i, 2);
            printf("_");
            starterArea[2][112 + i] = 5;

        }
        setcolor(CONSOLE_WHITE);

        // open door
        gotoxy(32, 2);
        printf("          ");
        for (i = 0; i < 10; i++)
        {
            starterArea[2][32 + i] = 6;
        }
        gotoxy(42, 3);
        printf("\\");
        starterArea[3][42] = 1;
        gotoxy(43, 4);
        printf("\\__ ");
        for (i = 0; i < 3; i++)
        {
            starterArea[4][43 + i] = 1;
        }
        gotoxy(46, 5);
        printf("\\");
        starterArea[5][46] = 1;

        // Transporting Bed
        gotoxy(152, 13);
        printf("[\033[0;31m=\033[0m=\033[0;31m=\033[0m=]");
        gotoxy(152, 14);
        printf("| \033[0;31m~~~\033[0m|");
        gotoxy(152, 15);
        printf("\033[0;31m|   ~\033[0m|");
        gotoxy(152, 16);
        printf("o----o");
        for (k = 0; k < 4; k++)
        {
            for (i = 0; i < 6; i++)
            {
                starterArea[13 + k][152 + i] = 8;
            }
        }

        // Bodies:
        gotoxy(8, 10);
        printf("[X-X");
        gotoxy(12, 10);
        setcolor(CONSOLE_RED);
        printf("\\~~~");
        setcolor(CONSOLE_WHITE);
        for (i = 0; i < 8; i++)
        {
            starterArea[10][8 + i] = 7;
        }

        // Bodie2:
        gotoxy(150, 10);
        printf("[X-X\033[0;31m]\033[0m");
        for (i = 0; i < 5; i++)
        {
            starterArea[10][150] = 12;
        }
        if (firstTimeInArea[1] == 1 && zombies[2].Zombielives > 0)
        {
            gotoxy(126, 4);
            printf("[X-\033[0;31m~~\033[0m");
            for (i = 0; i < 5; i++)
            {
                starterArea[4][126 + i] = 11;
            }

            gotoxy(150, 10);
            printf("[X-X\033[0;31m]\033[0m");
            gotoxy(150, 10);
            setcolor(CONSOLE_RED);
            printf("~/");
            setcolor(CONSOLE_WHITE);
            for (i = 0; i < 5; i++)
            {
                starterArea[10][150] = 12;
            }
            firstTimeInArea[1] = 2;

            gotoxy(148, 9);
            printf("\033[0;32m[-\xC2\xB0O\xC2\xB0]-\033[0m");
            Sleep(1000);
            gotoxy(148, 9);
            printf("\033[0;32m[-\xC2\xB0_\xC2\xB0]-\033[0m");
            Sleep(1000);
            zombies[2].ZombieposX = 148;
            zombies[2].ZombieposY = 9;
            zombies[2].Zombiespeed = 5;
            zombies[2].ZombieStartSpeed = 5;
        }



        if (firstTimeInArea[1] == 0)
        {
            gotoxy(130, 5);
            printf("Oh my god Help!!!");
            gotoxy(130, 6);
            printf("[\xC2\xB0o\xC2\xB0]");
            gotoxy(131, 9);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");

            Sleep(2000);

            gotoxy(130, 5);
            printf("                 ");
            gotoxy(128, 5);
            printf("[\xC2\xB0-\xC2\xB0]");
            gotoxy(130, 8);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");

            gotoxy(130, 6);
            printf("     ");
            gotoxy(131, 9);
            printf("       ");

            Sleep(500);

            gotoxy(129, 7);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(130, 8);
            printf("       ");

            Sleep(500);

            gotoxy(126, 4);
            printf("[\xC2\xB0-\xC2\xB0]");
            for (i = 0; i < 5; i++)
            {
                starterArea[4][126 + i] = 11;
            }
            gotoxy(128, 6);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(128, 5);
            printf("     ");
            gotoxy(129, 7);
            printf("       ");

            Sleep(500);

            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(128, 6);
            printf("       ");
            gotoxy(126, 3);
            printf("Ahhhhhhhh");
            Sleep(1000);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0O\xC2\xB0-]\033[0m");
            gotoxy(130, 4);
            setcolor(CONSOLE_RED);
            printf("~");
            setcolor(CONSOLE_WHITE);
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0-\xC2\xB0-]\033[0m");
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0O\xC2\xB0-]\033[0m");
            gotoxy(129, 4);
            setcolor(CONSOLE_RED);
            printf("~");
            setcolor(CONSOLE_WHITE);
            gotoxy(126, 4);
            printf("[X-");
            gotoxy(126, 3);
            printf("         ");
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            Sleep(500);
            gotoxy(126, 6);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(127, 5);
            printf("       ");
            Sleep(100);
            gotoxy(126, 6);
            printf("       ");
            firstTimeInArea[1] = 1;

            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        }
        
        if (firstTimeInArea[1] > 1)
        {
            gotoxy(126, 4);
            printf("[X-\033[0;31m~~\033[0m");
            for (i = 0; i < 5; i++)
            {
                starterArea[4][126 + i] = 11;
            }

            gotoxy(150, 10);
            printf("[X-X\033[0;31m]\033[0m");
            gotoxy(150, 10);
            setcolor(CONSOLE_RED);
            printf("~/");
            setcolor(CONSOLE_WHITE);
            for (i = 0; i < 5; i++)
            {
                starterArea[10][150] = 12;
            }

        }
       

    }
    else if (area == 3)
    {
        // äußere box
        BoxMaker(starterArea, 1, 2, 120, 30, 1, '_');
    
        BoxMaker(starterArea, 12, 7, 37, 11, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // chem bottles
                if (i < 16 && k < 2) value = 2;
                // drums
                else if (i > 16 && k < 2) value = 3;
                // reagents
                else if (i < 13 && k > 2) value = 4;
                // acids
                else if (i > 13 && k > 2) value = 5;
                else value = 1;

                starterArea[k + 7][i + 12] = value;
            }
        }
        BoxMaker(starterArea, 49, 7, 71, 11, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 23; i++)
            {
                // boxes
                if (i < 9 && k < 2) value = 6;
                // Kits
                else if (i > 9 && i < 16 && k < 2) value = 7;
                // PPE
                else if (i > 16 && k > 2) value = 8;
                // sterile goods
                else if (k > 2) value = 51;
                else value = 1;
                starterArea[k + 7][i + 49] = value;
            }
        }
        BoxMaker(starterArea, 83, 7, 108, 11, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // screwdrivers
                if (i < 17 && k < 2) value = 52;
                // Wires
                else if (i > 17 && k < 2) value = 53;
                // spare parts
                else if (i < 14 && k > 2) value = 54;
                // bio bags
                else if (i > 14 && k > 2) value = 55;
                else value = 1;
                starterArea[k + 7][i + 83] = value;
            }
        }
        BoxMaker(starterArea, 12, 21, 37, 25, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // clamps
                if (i < 13 && k < 2) value = 56;
                // tubes
                else if (i > 13 && k < 2) value = 57;
                // masks
                else if (i < 12 && k > 2) value = 58;
                // gloves
                else if (i > 12 && k > 2) value = 59;
                else value = 1;
                starterArea[k + 21][i + 12] = value;
            }
        }
        BoxMaker(starterArea, 49, 21, 74, 25, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // cold packs
                if (i < 15 && k < 2) value = 60;
                // meds
                else if (i > 15 && k < 2) value = 61;
                // vials
                else if (i < 10 && k > 2) value = 62;
                // syringes
                else if (i > 10 && k > 2) value = 63;
                else value = 1;
                starterArea[k + 21][i + 49] = value;
            }
        }
        BoxMaker(starterArea, 86, 21, 109, 25, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 24; i++)
            {
                // sample jar
                if (k < 2) value = 64;
                // cleaning fluids
                else if (k > 2) value = 65;
                else value = 1;
                starterArea[k + 21][i + 86] = value;
            }
        }
        i < 10 ? i : -1;

        //box 1:
        gotoxy(13, 8);
        printf("  chem bottles | drums  ");
        gotoxy(13, 9);
        printf("------------------------");
        gotoxy(13, 10);
        printf("   reagents | acids     ");

        // box 2:
        gotoxy(50, 8);
        printf("  boxes | kits | PPE ");
        gotoxy(50, 9);
        printf("---------------------");
        gotoxy(50, 10);
        printf("   sterile goods     ");

        // box 3:
        gotoxy(84, 8);
        printf("  screwdrivers  | wires ");
        gotoxy(84, 9);
        printf("------------------------");
        gotoxy(84, 10);
        printf(" spare parts | bio bags ");

        // box 4:
        gotoxy(13, 22);
        printf("   clamps   |   tubes   ");
        gotoxy(13, 23);
        printf("------------------------");
        gotoxy(13, 24);
        printf("   masks   |   gloves   ");

        // box 5:
        gotoxy(50, 22);
        printf("   cold packs |  meds   ");
        gotoxy(50, 23);
        printf("------------------------");
        gotoxy(50, 24);
        printf("  vials  |   syringes   ");

        // box 6:
        gotoxy(87, 22);
        printf("      sample jars     ");
        gotoxy(87, 23);
        printf("----------------------");
        gotoxy(87, 24);
        printf("   cleaning fluids    ");


        //door to the mashine room
        for (i = 0; i < 10; i++)
        {
            gotoxy(52 + i, 2);
            printf(" ");
            starterArea[2][52 + i] = 66;
        }

        // door to the hallway
        for (i = 0; i < 5; i++)
        {
            gotoxy(120,14 + i);
            printf(" ");
            starterArea[14 + i][120] = 68;
        }

        // breakable pipe
        for (i = 0; i < 23; i++)
        {
            
            gotoxy(2 + i, 30);
            printf("\033[33m=\033[0m");
            starterArea[30][2 + i] = 69;
        }
    }
    else if (area == 4)
    {
        // Äußere box
        BoxMaker(starterArea, 12, 2, 102, 30, 1, '_');

        // boiler  2  // Volvo 7
        gotoxy(24, 5);
        printf("  ________        ________  ");
        for (i = 0; i < 8; i++)
        {
            starterArea[5][26 + i] = 7;
            starterArea[5][42 + i] = 2;
        }
        gotoxy(24, 6);
        printf(" |        |      |        | ");
        for (i = 0; i < 10; i++)
        {
            starterArea[6][25 + i] = 7;
            starterArea[6][41 + i] = 2;
        }
        gotoxy(24, 7);
        printf(" |  VALVE |======| GAUGE  | ");
        for (i = 0; i < 26; i++)
        {
            if(i < 13)
            starterArea[7][25 + i] = 7;
            else
            starterArea[7][25 + i] = 2;
        }
        gotoxy(24, 8);
        printf(" |________|      |________| ");
        for (i = 0; i < 10; i++)
        {
            starterArea[8][25 + i] = 7;
            starterArea[8][41 + i] = 2;
        }
        gotoxy(24, 9);
        printf("    |||||  BOILER   |||||   ");
        for (i = 0; i < 21; i++)
        {
            starterArea[9][28 + i] = 2;
        }
        gotoxy(24, 10);
        printf("____|||||___________|||||____");
        for (i = 0; i < 29; i++)
        {
            starterArea[10][24 + i] = 2;
        }
        gotoxy(24, 11);
        printf("|         HEAT CORE         |");
        for (i = 0; i < 29; i++)
        {
            starterArea[11][24 + i] = 2;
        }
        gotoxy(24, 12);
        printf("|___________________________|");
        for (i = 0; i < 29; i++)
        {
            starterArea[12][24 + i] = 2;
        }


        // Emergency Generator 3
        gotoxy(65, 5);
        printf("_____________________________");
        gotoxy(64, 6);
        printf("|     EMERGENCY GENERATOR     |");
        gotoxy(64, 7);
        printf("|  _________      ________    |");
        gotoxy(64, 8);
        printf("|  |        |====| START  |   |");
        if (inventory[9] == 0)
        {
            gotoxy(64, 9);
            printf("|  | ENGINE |    | PANEL \033[5;31mo\033[0m|   |");
        }
        else
        {
            gotoxy(64, 9);
            printf("|  | ENGINE |    | PANEL \033[5;32mo\033[0m|   |");
        }
        gotoxy(64, 10);
        printf("|  |  ||||  |    |________|   |");
        gotoxy(64, 11);
        printf("|  |  ||||  |        ||       |");
        gotoxy(64, 12);
        printf("|__|________|________||_______|");
        for (k = 0; k < 8; k++)
        {
            for (i = 0; i < 31; i++)
            {
                starterArea[5 + k][64 + i] = 3;
            }
        }
        starterArea[5][64] = 0;
        starterArea[5][94] = 0;



        // Serverbox1 4
        gotoxy(20,19);
        printf("______________________");
        gotoxy(19, 20);
        printf("/_____________________/|");
        gotoxy(18, 21);
        printf("|  [ UPS ]   ||||||   | |");
        gotoxy(18, 22);
        printf("|============||||||===| |");
        gotoxy(18, 23);
        printf("|  [ SBS ]   ||||||   | |");
        gotoxy(18, 24);
        printf("|============||||||===| |");
        gotoxy(18, 25);
        printf("|  [ CTRL ]  ||||||   | |");
        gotoxy(18, 26);
        printf("|============||||||===| |");
        gotoxy(18, 27);
        printf("|  [ NET ]   ||||||   | /");
        gotoxy(18, 28);
        printf("|_____________________|/");

        // Serverbox2 5
        gotoxy(74, 19);
        printf("______________________");
        gotoxy(73, 20);
        printf("/_____________________/|");
        gotoxy(72, 21);
        printf("|  [ UPS ]   ||||||   | |");
        gotoxy(72, 22);
        printf("|============||||||===| |");
        gotoxy(72, 23);
        printf("|  [ BACK ]  ||||||   | |");
        gotoxy(72, 24);
        printf("|============||||||===| |");
        gotoxy(72, 25);
        printf("|  [ HDD ]   [][][]   | |");
        gotoxy(72, 26);
        printf("|============||||||===| |");
        gotoxy(72, 27);
        printf("|  [ NET ]   ||||||   | /");
        gotoxy(72, 28);
        printf("|_____________________|/");

        for (k = 0; k < 10; k++)
        {
            for (i = 0; i < 25; i++)
            {
                starterArea[19 + k][18 + i] = 4;
                starterArea[19 + k][72 + i] = 5;
            }
        }
        starterArea[19][18] = 0;
        starterArea[19][19] = 0;
        starterArea[19][42] = 0;
        starterArea[20][18] = 0;
        starterArea[28][42] = 0;

        starterArea[19][72] = 0;
        starterArea[19][73] = 0;
        starterArea[19][96] = 0;
        starterArea[20][72] = 0;
        starterArea[28][96] = 0;



        
        //door to the lagerraum 6
        gotoxy(52, 30);
        printf("          ");

        for (i = 0; i < 10; i++)
        {
            starterArea[30][52 + i] = 6;
        }






    }
    else if (area == 5)
    {
        // outer box
        BoxMaker(starterArea, 5, 2, 70, 30, 1, '_');

        // Box bottom left
        BoxMaker(starterArea, 5, 17, 21, 30, 1, '_');

        // fix one broken character
        gotoxy(5,17);
        printf("|");

        // door for mens and womans room
        setcolor(CONSOLE_BROWN);
        for (i = 0; i < 5; i++)
        {
            // woman 2 
            gotoxy(5, 20 + i);
            printf("|");
            starterArea[20 + i][5] = 2;
            // men 3 
            gotoxy(21, 20 + i);
            printf(" ");
            starterArea[20 + i][21] = 0;
        }

        // door to the hallway 3
        for (i = 0; i < 9; i++)
        {
            gotoxy(9 + i, 30);
            printf(" ");
            starterArea[30][9 + i] = 3;
        }

        setcolor(CONSOLE_WHITE);

        // shower 4
        for (i = 0; i < 3; i++)
        {
            gotoxy(6, 2 + (5 * i));
            printf("_______________");
            for (k = 0; k < 15; k++)
            {
                starterArea[2 + (5 * i)][6 + k] = 1;
            }
            gotoxy(10, 3 + (5 * i));
            printf("shower");
            for(k = 0; k < 6; k++)
            {
                starterArea[3 + (5 * i)][10 + k] = 4;
            }
            gotoxy(7, 4 + (5 * i));
            printf("/'");
            starterArea[4 + (5 * i)][7] = 4;
            starterArea[4 + (5 * i)][8] = 4;
            gotoxy(6, 5 + (5 * i));
            printf("o ''");
            starterArea[5 + (5 * i)][7] = 4;
            starterArea[5 + (5 * i)][8] = 4;
            starterArea[5 + (5 * i)][9] = 4;
            gotoxy(8, 6 + (5 * i));
            printf("'~'");
            starterArea[6 + (5 * i)][8] = 4;
            starterArea[6 + (5 * i)][9] = 4;
            starterArea[6 + (5 * i)][10] = 4;
        }


        // stalls 5
        
        gotoxy(37, 3);
        printf("| /_____/  | /_____/  | /_____/");
        gotoxy(37, 4);
        printf("| |  O  |  | |  O  |  | |  O  |");
        gotoxy(37, 5);
        printf("| |     |  | |     |  | |     |");
        gotoxy(37, 6);
        printf("|  \\___/   |  \\___/   |  \\___/");
        gotoxy(37, 7);
        printf("|__________|__________|");

        for (i = 0; i < 4; i++)
        {
            for (k = 0; k < 31; k++)
                starterArea[3 + i][37 + k] = 5;
        }

        // small fixes
        for (i = 0; i < 23; i++)
            starterArea[7][37 + i] = 5;

        starterArea[6][67] = 0;

        gotoxy(60, 8);
        printf("\\");
        starterArea[8][60] = 1;
        gotoxy(61, 9);
        printf("|");
        starterArea[9][61] = 1;
        gotoxy(61, 10);
        printf("|");
        starterArea[10][61] = 1;


        // pissuars 6
        for (i = 0; i < 2; i++)
        {
            gotoxy(65, 13 + (4 * i));
            printf("-----");
            for (k = 0; k < 5; k++)
            {
                starterArea[13 + (4 * i)][65 + k] = 1;
            }
            gotoxy(67, 14 + (4 * i));
            printf("/¯¯");
            starterArea[14 + (4 * i)][67] = 6;
            starterArea[14 + (4 * i)][68] = 6;
            starterArea[14 + (4 * i)][69] = 6;

            gotoxy(67, 15 + (4 * i));
            printf("| O");
            starterArea[15 + (4 * i)][67] = 6;
            starterArea[15 + (4 * i)][68] = 6;
            starterArea[15 + (4 * i)][69] = 6;

            gotoxy(67, 16 + (4 * i));
            printf("\\__");
            starterArea[16 + (4 * i)][67] = 6;
            starterArea[16 + (4 * i)][68] = 6;
            starterArea[16 + (4 * i)][69] = 6;

            gotoxy(65, 17 + (4 * i));
            printf("-----");
            for (k = 0; k < 5; k++)
            {
                starterArea[17 + (4 * i)][65 + k] = 1;
            }
        }

        // sink 7
        gotoxy(35, 27);
        printf("_______________________");
        gotoxy(34, 28);
        printf("|  ___     ___     ___  |");
        gotoxy(34, 29);
        printf("| |___|   |___|   |___| |");
        gotoxy(34, 30);
        printf("|___|_______|_______|___|");

        for (i = 0; i < 3; i++)
        {
            for (k = 0; k < 25; k++)
                starterArea[27 + i][34 + k] = 7;
        }

        // small fixes
        starterArea[27][34] = 0;
        starterArea[27][58] = 0;
    }
    else if (area == 6)
    {
        // outer box
        BoxMaker(starterArea, 5, 2, 95, 30, 1, '_');

        //locker (empty 2)
        for (i = 0; i < 2; i++)
        {
            for (k = 0; k < 2; k++)
            {
                for (j = 0; j < 5; j++)
                {
                    gotoxy(i * 45 + k * 37 + 5, j * 3 + 6);
                    printf("|¯¯¯¯¯¯|");
                    gotoxy(i * 45 + k * 37 + 5, j * 3 + 6 + 1);
                    printf("|      |");
                    gotoxy(i * 45 + k * 37 + 5, j * 3 + 6 + 2);
                    printf("|      |");
                    for (int m = 0; m < 3; m++)
                        for (int n = 0; n < 8; n++)
                            starterArea[j * 3 + 6 + m][i * 45 + k * 37 + 5 + n] = 2;
                    gotoxy(i * 45 + k * 37 + 10 - ((k % 2) * 3), j * 3 + 6 + 2);
                    printf("o");
                }
                gotoxy(i * 45 + k * 37 + 6, (j - 1) * 3 + 6 + 3);
                printf("¯¯¯¯¯¯");
                for (int n = 0; n < 6; n++)
                    starterArea[(j - 1) * 3 + 6 + 3][i * 45 + k * 37 + 6 + n] = 2;
            }
        }


        //benches 3
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 14; j++)
            {
                gotoxy(i * 45 + 23, j + 7);
                printf("|   |   |");
                for (int m = 0; m < 9; m++)
                    starterArea[j + 7][i * 45 + 23 + m] = 3;
            }
            gotoxy(i * 45 + 23, 6);
            printf("|¯¯¯¯¯¯¯|");
            for (int m = 0; m < 9; m++)
                starterArea[6][i * 45 + 23 + m] = 3;
            gotoxy(i * 45 + 24, j + 7);
            printf("¯¯¯¯¯¯¯");
            for (int m = 0; m < 7; m++)
                starterArea[j + 7][i * 45 + 24 + m] = 3;
        }


        //keyholder 4
        setcolor(CONSOLE_BROWN);
        gotoxy(32, 30);
        printf("|¯¯|");
        setcolor(CONSOLE_WHITE);
        for (i = 0; i < 4; i++)
            starterArea[30][32 + i] = 4;
        

        // sink 5
        gotoxy(90, 27);
        printf("|¯¯¯¯");
        gotoxy(90, 28);
        printf("|  o ");
        gotoxy(90, 29);
        printf("|____");
        for (i = 0; i < 3; i++)
            for (j = 0; j < 5; j++)
                starterArea[i + 27][j + 90] = 5;

        // bin 6
        gotoxy(91, 24);
        printf("__");
        starterArea[24][91] = 6;
        starterArea[24][92] = 6;
        gotoxy(90, 25);
        printf("|  |");
        for (i = 0; i < 4; i++)
            starterArea[25][90 + i] = 6;
        gotoxy(91, 26);
        printf("¯¯");
        starterArea[26][91] = 6;
        starterArea[26][92] = 6;

        // door 7
        setcolor(CONSOLE_BROWN);
        gotoxy(44, 30);
        printf("__________");
        for (i = 0; i < 10; i++)
            starterArea[30][44 + i] = 7;
        setcolor(CONSOLE_WHITE);




        // bottom body 8
        gotoxy(24,27);
        printf("\033[0;31m~\033[0m");
        starterArea[27][24] = 8;
        gotoxy(23, 28);
        printf("\033[0;31m~~\033[0m");
        starterArea[28][23] = 8;
        starterArea[28][24] = 8;
        gotoxy(21, 29);
        printf("[xO\033[0;31mx]\033[0m");
        for (i = 0; i < 5; i++)
            starterArea[29][21 + i] = 8;


        // top body 21
        gotoxy(51, 5);
        printf("[\033[0;31mQ\033[0m-Q\033[0;31m~~\033[0m");
        for (i = 0; i < 6; i++)
            starterArea[5][51 + i] = 21;

        // special locker 22
        setcolor(CONSOLE_BROWN);
        gotoxy(50, 6);
        printf("|¯¯¯¯¯¯|");
        gotoxy(50, 7);
        printf("|      |");
        gotoxy(50, 8);
        printf("|    o |");
        gotoxy(51, 9);
        printf("¯¯¯¯¯¯");
        setcolor(CONSOLE_WHITE);
        for (int m = 0; m < 4; m++)
            for (int n = 0; n < 8; n++)
                starterArea[6 + m][50 + n] = 22;
        
        
        // secret locker 23
        for (int m = 0; m < 4; m++)
            for (int n = 0; n < 8; n++)
                starterArea[15 + m][5 + n] = 23;


        // special 
        
        // left locker
        gotoxy(12,15);
        printf("\033[0;31m|\033[0m");
        gotoxy(12, 16);
        printf("\033[0;31m|\033[0m");

        // left bench
        gotoxy(29, 13);
        printf("\033[2;31;101m\033[7;31m  \033[0m\033[0;31m|~~\033[0m");
        starterArea[13][32] = 1;
        starterArea[13][33] = 1;
        gotoxy(29, 14);
        printf("\033[2;31;101m\033[7;31m  \033[0m\033[0;31m|~\033[0m");
        starterArea[14][32] = 1;
        gotoxy(30, 15);
        printf("\033[2;31;101m\033[7;31m \033[0m");
        gotoxy(31, 16);
        printf("\033[0;31m|\033[0m");


        // 2cond locker row
        gotoxy(42, 19);
        printf("\033[0;31m|\033[0m");
        gotoxy(41, 20);
        printf("\033[0;31m~|\033[0m\033[2;31;101m\033[7;31m \033[0m");
        starterArea[20][41] = 1;
        gotoxy(42, 21);
        printf("\033[0;31m~\033[0m¯\033[0;31m¯¯¯\033[0m");
        starterArea[21][42] = 1;

        // upper 3d locker row
        gotoxy(52, 6);
        printf("\033[0;31m¯¯¯\033[0m");
        gotoxy(57, 10);
        printf("\033[0;31m|\033[0m");
        gotoxy(57, 11);
        printf("\033[0;31m|~\033[0m");
        starterArea[11][58] = 1;


        // 2cond bench
        gotoxy(68, 17);
        printf("\033[2;31m|\033[7;31m   \033[0m");
        gotoxy(68, 18);
        printf("\033[2;31m| \033[7;31m \033[0m");
        gotoxy(69, 19);
        printf("\033[2;31m\033[7;31m  \033[0m");
    }
    
}  
            
//____________________________________________________________________________________________________________
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                    |¯¯¯¯¯¯¯¯|              |¯¯¯¯¯¯¯¯|                                     |
//|                                    |        |              |        |                                     |
//|                                    |        |______________|        |                                     |
//|                                    |                                |                                     |
//|                                    |                                |                                     |
//|                                    |________________________________|                                     |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                       [Xo~                |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//| |¯¯¯¯¯¯¯¯¯¯|                                                                                              |
//| |          |                                                                                              |
//| |          |       [x-\                                                                                   |
//| |          |                                                                                              |
//| |          |                                                                                              |
//| |          |                                                                                              |
//| |          ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|                                                                      |
//| |                                  |                                                                      |
//| |                                  |                                                                      |
//| |__________________________________|                                                                      |
//|____________________________________________                   ____________________________________________|


bool VisionCheck(int starterX, int starterY, int targetX, int targetY, char starterArea[][COLS], int starterArrayValue, int targetArrayValue)
{
    int x = starterX; 
    int y = starterY;

    while (x != targetX || y != targetY)
    {
        if (abs(x - targetX) > abs(y - targetY))
        {
            if (x > targetX)
            {
                x--;
            }
            else
            {
                x++;
            }
        }
        else
        {
            if (y > targetY)
            {
                y--;
            }
            else
            {
                y++;
            }
        }
        if (starterArea[y][x] != 0 && starterArea[y][x] != starterArrayValue && starterArea[y][x] != targetArrayValue)
        {
            return true;
        }
    }
    return false;
}


void HitCheck(int SwordX, int SwordY, int area, Zombie& zombie, int howFar, int lastNumberPressed)
    {
        
        //gotoxy(40, 10);
        //printf("SX: %d, ZX: %d SY: %d, ZY: %d",SwordX, zombie.ZombieposX, SwordY, zombie.ZombieposY );
        for (int j = 0; j < howFar; j++)
        {
            for (int i = 0; i < zombie.ZombieSize; i++)
            {
                if (SwordX + j == zombie.ZombieposX + i && SwordY == zombie.ZombieposY)
                {
                    
                    // Handle hit logic here
                    zombie.Zombielives--; // Example: Reduce zombie's lives
                    gotoxy(zombie.ZombieposX, zombie.ZombieposY);
                    printf("       ");
                    if (lastNumberPressed == 1)
                    {
                        zombie.ZombieposY -= 2;
                    }
                    else if (lastNumberPressed == 2)
                    {
                        zombie.ZombieposX -= 3;
                    }
                    else if (lastNumberPressed == 3)
                    {
                        zombie.ZombieposY += 2;
                    }
                    else if (lastNumberPressed == 4)
                    {
                        zombie.ZombieposX += 3;
                    }
                                       
                }
            }
        }
        
    }

void swordAnimations(int lastNumberPressed, char starterArea[][COLS], int swordAnimationPhase, int area, Zombie& zombie, bool swordCancel)
    {
        if (lastNumberPressed == 1)
        {
            if (swordAnimationPhase == 1)
            {
                // Zombie hat nur beim tot ne zahl davor nur einen bereich
                if (starterArea[PlayerY - 1][PlayerX + 5] == 0)
                {
                    gotoxy(PlayerX + 5, PlayerY - 1);
                    printf("  /");
                    HitCheck(PlayerX + 5, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                else
                    swordCancel = true;
            }
            else if (swordAnimationPhase == 2 && !swordCancel)
            {
                if (starterArea[PlayerY - 1][PlayerX + 4] == 0)
                {
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf(" / ");
                    HitCheck(PlayerX + 4, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                else
                    swordCancel = true;
            }
            else if (swordAnimationPhase == 3 && !swordCancel)
            {
                if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                {
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf("| ");
                    HitCheck(PlayerX + 3, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                else
                    swordCancel = true;
            }
            else if (swordAnimationPhase == 4 && !swordCancel)
            {
                if (starterArea[PlayerY - 1][PlayerX + 2] == 0)
                {
                    gotoxy(PlayerX + 2, PlayerY - 1);
                    printf("\\ ");
                    HitCheck(PlayerX + 2, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                else
                    swordCancel = true;
            }
            else if (swordAnimationPhase == 5)
            {
                if (starterArea[PlayerY - 1][PlayerX + 5] == 0)
                {
                    PrintRemover(starterArea, PlayerX + 2, PlayerY - 1);
                    PrintRemover(starterArea, PlayerX + 3, PlayerY - 1);
                    PrintRemover(starterArea, PlayerX + 4, PlayerY - 1);
                    PrintRemover(starterArea, PlayerX + 5, PlayerY - 1);
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf("|");
                }
             
            }
        }
        else if (lastNumberPressed == 2)
        {

            if (starterArea[PlayerY + 1][PlayerX - 2] == 0 && starterArea[PlayerY - 1][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3] == 0)
            {
                if (swordAnimationPhase == 1)
                {
                    gotoxy(PlayerX - 3, PlayerY);
                    printf("   ");
                    gotoxy(PlayerX - 2, PlayerY - 1);
                    printf("\\");
                    HitCheck(PlayerX - 2, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 2)
                {
                    gotoxy(PlayerX - 2, PlayerY - 1);
                    printf(" ");
                    gotoxy(PlayerX - 3, PlayerY);
                    printf("--<");
                    HitCheck(PlayerX - 3, PlayerY, area, zombie, 3, lastNumberPressed);
                }
                //Sleep(50);
                if (swordAnimationPhase == 3)
                {
                    gotoxy(PlayerX - 3, PlayerY);
                    printf("   ");
                    gotoxy(PlayerX - 2, PlayerY + 1);
                    printf("/");
                    HitCheck(PlayerX - 2, PlayerY + 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 4)
                {
                    gotoxy(PlayerX - 2, PlayerY + 1);
                    printf(" ");
                    gotoxy(PlayerX - 3, PlayerY);
                    printf("--<");
                }
            }



        }
        else if (lastNumberPressed == 3)
        {

            if (starterArea[PlayerY + 1][PlayerX - 1] == 0 && starterArea[PlayerY + 1][PlayerX] == 0 && starterArea[PlayerY + 1][PlayerX + 1] == 0 && starterArea[PlayerY + 1][PlayerX + 2] == 0)
            {
                if (swordAnimationPhase == 1)
                {
                    gotoxy(PlayerX - 1, PlayerY + 1);
                    printf("/  ");
                    HitCheck(PlayerX - 1, PlayerY + 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 2)
                {
                    gotoxy(PlayerX - 1, PlayerY + 1);
                    printf(" /");
                    HitCheck(PlayerX, PlayerY + 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(50);
                if (swordAnimationPhase == 3)
                {
                    gotoxy(PlayerX, PlayerY + 1);
                    printf(" |");
                    HitCheck(PlayerX + 1, PlayerY + 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(50);
                if (swordAnimationPhase == 4)
                {
                    gotoxy(PlayerX + 1, PlayerY + 1);
                    printf(" \\");
                    HitCheck(PlayerX + 2, PlayerY + 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 5)
                {
                    gotoxy(PlayerX + 2, PlayerY + 1);
                    printf(" ");
                    gotoxy(PlayerX + 1, PlayerY + 1);
                    printf("| ");
                }
            }

        }
        else if (lastNumberPressed == 4)
        {
            if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY - 1][PlayerX + 6] == 0 && starterArea[PlayerY + 1][PlayerX + 6] == 0)
            {
                if (swordAnimationPhase == 1)
                {
                    gotoxy(PlayerX + 5, PlayerY);
                    printf("   ");
                    gotoxy(PlayerX + 6, PlayerY - 1);
                    printf("/");
                    HitCheck(PlayerX + 6, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 2)
                {
                    gotoxy(PlayerX + 6, PlayerY - 1);
                    printf(" ");
                    gotoxy(PlayerX + 5, PlayerY);
                    printf(">--");
                    HitCheck(PlayerX + 5, PlayerY, area, zombie, 3, lastNumberPressed);
                }
                //Sleep(50);
                if (swordAnimationPhase == 3)
                {
                    gotoxy(PlayerX + 5, PlayerY);
                    printf("   ");
                    gotoxy(PlayerX + 6, PlayerY + 1);
                    printf("\\");
                    HitCheck(PlayerX + 6, PlayerY + 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 4)
                {
                    gotoxy(PlayerX + 6, PlayerY + 1);
                    printf(" ");
                    gotoxy(PlayerX + 5, PlayerY);
                    printf(">--");
                }
            }

        }
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    }    

void WaitingTime(int& waitForNextMove, int& waitForSwordAnimation, int lastNumberPressed, int& swordCooldown, Zombie zombies[])
{
    int i;
    for (i = 0; i < HowManyZombiesExist; i++)
    {
        if (zombies[i].waitForNextZombieMove > 0)
        {
            zombies[i].waitForNextZombieMove--;
        } 
    }

    if (waitForNextMove > 0)
    {
        waitForNextMove--;
        //printf("%d", waitForNextMove);
    }

    //Sword
    if (waitForSwordAnimation > 0)
    {
        waitForSwordAnimation++;
        //printf("d");
        //Sleep(1000);
    }
    if (swordCooldown > 0)
        swordCooldown--;

    if (waitForSwordAnimation >= 4 && (lastNumberPressed == 1 || lastNumberPressed == 3))
        waitForSwordAnimation = 0;
    if (waitForSwordAnimation >= 6 && (lastNumberPressed == 2 || lastNumberPressed == 4))
        waitForSwordAnimation = 0;
}

void Sword(int sword, int& lastNumberPressed, int input, char starterArea[][COLS])
{
    int i;
    if (sword == 1)
    {
        if (input == 119 || input == 72)
        {
            if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY - 1);
                printf("|");
            }
        }
        else if (input == 97 || input == 75)
        {
            if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
            {
                gotoxy(PlayerX - 3, PlayerY);
                printf("--<");
            }
        }
        else if (input == 115 || input == 80)
        {
            if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY + 1);
                printf("|");
            }
        }
        else if (input == 100 || input == 77)
        {
            if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY);
                printf(">--");
            }
        }
        // für w
        if (lastNumberPressed == 1 && (input == 97 || input == 75))
        {
            if (starterArea[PlayerY - 1][PlayerX + 5] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY - 1);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 1 && (input == 115 || input == 80))
        {
            if (starterArea[PlayerY - 2][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY - 2);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 1 && (input == 100 || input == 77))
        {
            if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY - 1);
                printf(" ");
            }
        }
        // für a
        else if (lastNumberPressed == 2 && (input == 119 || input == 72))
        {
            for (i = 1; i <= 3; i++)
            {
                if (starterArea[PlayerY + 1][PlayerX - i] == 0)
                {
                    gotoxy(PlayerX - i, PlayerY + 1);
                    printf(" ");
                }
            }
        }
        else if (lastNumberPressed == 2 && (input == 115 || input == 80))
        {
            for (i = 1; i <= 3; i++)
            {
                if (starterArea[PlayerY - 1][PlayerX - i] == 0)
                {
                    gotoxy(PlayerX - i, PlayerY - 1);
                    printf(" ");
                }
            }
        }
        else if (lastNumberPressed == 2 && (input == 100 || input == 77))
        {
            for (i = 3; i <= 5; i++)
            {
                if (starterArea[PlayerY][PlayerX - i] == 0)
                {
                    gotoxy(PlayerX - i, PlayerY);
                    printf(" ");
                }
            }
        }
        // für s
        else if (lastNumberPressed == 3 && (input == 119 || input == 72))
        {
            if (starterArea[PlayerY + 2][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY + 2);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 3 && (input == 97 || input == 75))
        {
            if (starterArea[PlayerY + 1][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY + 1);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 3 && (input == 100 || input == 77))
        {
            if (starterArea[PlayerY + 1][PlayerX - 1] == 0)
            {
                gotoxy(PlayerX - 1, PlayerY + 1);
                printf(" ");
            }
        }
        // für d
        else if (lastNumberPressed == 4 && (input == 119 || input == 72))
        {
            for (i = 5; i <= 7; i++)
            {
                if (starterArea[PlayerY + 1][PlayerX + i] == 0)
                {
                    gotoxy(PlayerX + i, PlayerY + 1);
                    printf(" ");
                }
            }
        }
        else if (lastNumberPressed == 4 && (input == 97 || input == 75))
        {
            for (i = 7; i <= 9; i++)
            {
                if (starterArea[PlayerY][PlayerX + i] == 0)
                {
                    gotoxy(PlayerX + i, PlayerY);
                    printf(" ");
                }
            }
        }
        else if (lastNumberPressed == 4 && (input == 115 || input == 80))
        {
            for (i = 5; i <= 7; i++)
            {
                if (starterArea[PlayerY - 1][PlayerX + i] == 0)
                {
                    gotoxy(PlayerX + i, PlayerY - 1);
                    printf(" ");
                }
            }
        }
    }
}

void ECheck(int area, char starterArea[][COLS], int sword, int lastNumberPressed, int input)
{
        int i;
        int j;
        int addX = 0;
        int addY = -1;
        int length = 5;
        bool found = false;
        for (i = 0; i < 4 && found == false; i++)
        {
            for (j = 0; j < length; j++)
            {
                if (starterArea[PlayerY + addY][PlayerX + addX + j] >= 2 && starterArea[PlayerY + addY][PlayerX + addX + j] != 9)
                {
                    gotoxy(5, 46);
                    printf("*press e to interact*");
                    found = true;
                    break;
                   
                }
            }
            if (i == 0)
            {
                addY = +1;
                addX = 0;
                length = 5;
            }
            else if (i == 1)
            {
                addY = 0;
                addX = 4;

            }
            else if (i == 2)
            {
                addY = 0;
                addX = -2;
                length = 2;
            }
        }
        if (found == true)
        {
            gotoxy(5, 46);
            printf("*press e to interact*");
        }
        else
        {
            gotoxy(5, 46);
            printf("                     ");
        }
}

int Borders(int area, int& abbruch, char starterArea[][COLS], int input, int& sword, int lastNumberPressed)
{
    // 0 = nichts
    // 1 = wand
    // 2 = junk table
    // 3 = laptop
    // 4 = sketches
    // 5 = microscope
    // 6 = bottles
    // 7 = Door
    // 8 = Bed
    // 9 = player

     
        if (sword == 0 || sword == 2)   
        {
            if (input == 119 || input == 72)      
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (starterArea[PlayerY - 1][PlayerX + i] >= 1)
                    {
                        return abbruch = 1;
                    }
                }
            }
            else if (input == 97 || input == 75)
            {
                
                for (int i = 0; i <= 2; i++)
                {
                    if (starterArea[PlayerY][PlayerX - i] >= 1 && starterArea[PlayerY][PlayerX - i] != 9 )
                    {

                        return abbruch = 1;

                    }
                }
            }
            else if (input == 115 || input == 80)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9)
                    {

                        return abbruch = 1;
                    }
                }
            }
            else if (input == 100 || input == 77)
            {
                for (int i = 5; i < 7; i++)
                {
                    if (starterArea[PlayerY][PlayerX + i] >= 1 && starterArea[PlayerY][PlayerX + i] != 9)
                    {
                        
                        if (starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 7, PlayerY);
                            printf(" ");
                        }
                        return abbruch = 1;
                    }
                }
            }
            
        }
        // sword == 1
        else if (sword == 1)
        {
            if (input == 119 || input == 72)
            {
                for (int i = 0; i <= 4; i++)
                {

                    if (starterArea[PlayerY - 2][PlayerX + 3] >= 1 && starterArea[PlayerY - 2][PlayerX + 3] != 9)
                    {

                        sword = 2;

                    }
                    if (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9)
                    {
                        sword = 2;
                        return abbruch = 1;
                    }
                }
            }
            else if (input == 97 || input == 75)
            {
                for (int i = 0; i <= 5; i++)
                {
                    
                    if (starterArea[PlayerY][PlayerX - i] >= 1 && starterArea[PlayerY][PlayerX - i] != 9)
                    {
                        if (starterArea[PlayerY][PlayerX - 3] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf(" ");
                        }
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY + 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY - 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                        {
                            gotoxy(PlayerX + 3, PlayerY - 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY + 1][PlayerX + 3] == 0)
                        {
                            gotoxy(PlayerX + 3, PlayerY + 1);
                            printf(" ");
                        }
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 1] >= 1 || starterArea[PlayerY][PlayerX - 2] >= 1)
                        {
                            return abbruch = 1;
                        }
                        else
                        {
                            return abbruch = 0;
                        }

                    }

                }
            }
            else  if (input == 115 || input == 80)
            {
                for (int i = 0; i <= 4; i++)
                {
                   
                    if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                    {
                        gotoxy(PlayerX + 3, PlayerY - 1);
                        printf(" ");
                    }
                    if (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9)
                    {
                        sword = 2;
                    }
                    if (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9)
                    {
                        sword = 2;
                        return abbruch = 1;
                    }
                }
            }
            else  if (input == 100 || input == 77)
            {

                for (int i = 0; i <= 5; i++)
                {
                    if (starterArea[PlayerY][PlayerX + 5 + i] >= 1 && starterArea[PlayerY][PlayerX + 5 + i] != 9)
                    {
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6 ] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY + 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf("   ");
                        }
                        if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY - 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                        {
                            gotoxy(PlayerX + 3, PlayerY - 1);
                            printf(" ");
                        }
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX + 5] >= 1 || starterArea[PlayerY][PlayerX + 6])
                        {
                            return abbruch = 1;
                        }
                        else {
                            return abbruch = 0;
                        }
                    }

                }
            }
        }

        //sword = 2
        if (sword == 2)
        {



            if ((input != 119 && input != 72) && lastNumberPressed == 1)
            {
                for (int i = 0; i <= 4; i++)
                {

                    if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX + 1] == 1 || starterArea[PlayerY][PlayerX] == 1))
                    {
                        return abbruch = 1;
                    }
                    else if ((input == 115 || input == 80) && (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i]))
                    {
                        return abbruch = 1;
                    }
                    // sword in no wall
                    else if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY - 1);
                            printf(" ");
                        }
                        return abbruch = 0;
                    }
                    else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + 5 + 1] == 1 || starterArea[PlayerY][PlayerX + 5 + 2] == 1))
                    {
                        return abbruch = 1;
                    }


                }
                if (starterArea[PlayerY][PlayerX - 1] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3] == 0)
                {
                    gotoxy(PlayerX - 3, PlayerY);
                    printf("   ");
                }
                if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                {
                    gotoxy(PlayerX + 5, PlayerY);
                    printf("   ");
                }
                sword = 1;
            }
            else if ((input != 97 && input != 75) && lastNumberPressed == 2)
            {
                for (int i = 0; i <= 4; i++)
                {

                    if ((input == 119 || input == 72) && (starterArea[PlayerY - 1][PlayerX + i] == 1))
                    {

                        return abbruch = 0;
                    }
                    // sword in no wall
                    else if ((input == 119 || input == 72)&& (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if ((input == 115 || input == 80) && (starterArea[PlayerY + 1][PlayerX + i] == 1))
                    {
                        return abbruch = 1;
                    }
                    else if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + 4 + i] >= 1 && starterArea[PlayerY][PlayerX + 4 + i] != 9 ))
                    {
                        if (starterArea[PlayerY][PlayerX - 3] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf(" ");
                        }
                        sword = 2;
                        return abbruch = 0;
                    }

                }

                sword = 1;
            }
            else if ((input != 115 && input != 80) && lastNumberPressed == 3)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if ((input == 119 || input == 72) && (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9))
                    {
                        return abbruch = 1;
                    }
                    // sword in no wall
                    else if ((input == 119 || input == 72) && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY + 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX - i] >= 1 || starterArea[PlayerY][PlayerX - i] != 9))
                    {

                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        sword = 1;
                        return abbruch = 0;
                    }
                    else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + 2 + i] >= 1 && starterArea[PlayerY][PlayerX + 2 + i] != 9))
                    {
                        return abbruch = 1;
                    }
                    else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX - 1] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3 == 0]))
                    {
                        
                        return abbruch = 0;
                    }
                }
                if (starterArea[PlayerY][PlayerX - 1] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3] == 0)
                {
                    gotoxy(PlayerX - 3, PlayerY);
                    printf("   ");
                }
                if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                {
                    gotoxy(PlayerX + 5, PlayerY);
                    printf("   ");
                }
                
                sword = 1;
            }
            else if ((input != 100 && input != 77) && lastNumberPressed == 4)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if ((input == 119 || input == 72) && (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9))
                    {

                        return abbruch = 1;
                    }
                    // sword in no wall
                    else if ((input == 119 || input == 72) && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX - 1 - i] >= 1 && starterArea[PlayerY][PlayerX - 1 - i] != 9))
                    {
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 1] >= 1 || starterArea[PlayerY][PlayerX - 2] >= 1)
                        {
                            return abbruch = 1;
                        }
                        else {
                            return abbruch = 0;
                        }
                    }
                    else if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9 || starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9))
                    {

                        //sword = 2;
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        
                        if (starterArea[PlayerY + 1][PlayerX + i] >= 1 )
                        {
                            return abbruch = 1;
                        }
                        else {
                            return abbruch = 0;
                        }
                    }
                    else if ((input == 115 || input == 80) && (starterArea[PlayerY + 1][PlayerX + i] == 1))
                    {

                        return abbruch = 1;
                    }
                }

                sword = 1;
            }
            else if ((input == 119 || input == 72) && lastNumberPressed == 1)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9)
                    {

                        sword = 2;
                        return abbruch = 0;
                    }
                }

                sword = 1;
            }
            else if ((input == 97 || input == 75) && (lastNumberPressed == 2))
            {
                for (int i = 0; i <= 4; i++)
                {
                    if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX - 1 - i] >= 1 && starterArea[PlayerY][PlayerX - 1 - i] != 9))
                    {
                        sword = 2;
                        return abbruch = 0;
                    }
                }
                sword = 1;

            }
            else if ((input == 115 || input == 80) && lastNumberPressed == 3)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        
                        return abbruch = 0;
                    }
                }
                sword = 1;
            }
            else if ((input == 100 || input == 77) && (lastNumberPressed == 4))
            {
                for (int i = 0; i <= 7; i++)
                {
                    if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + i] >= 1 && starterArea[PlayerY][PlayerX + i] != 9))
                    {
                        sword = 2;
                        return abbruch = 0;
                    }
                }

                sword = 1;

            }
            


        }
       

        if ((starterArea[PlayerY][PlayerX] >= 2 && starterArea[PlayerY][PlayerX] != 9) || (starterArea[PlayerY][PlayerX + 1] >= 2 && starterArea[PlayerY][PlayerX + 1] != 9) || (starterArea[PlayerY][PlayerX + 2] >= 2 && starterArea[PlayerY][PlayerX + 2] != 9) || (starterArea[PlayerY][PlayerX + 3] >= 2 && starterArea[PlayerY][PlayerX + 3] != 9) || (starterArea[PlayerY][PlayerX + 4] >= 2 && starterArea[PlayerY][PlayerX + 4] != 9))
        {
            return abbruch = 2;
        }
        //oben
        else if (((starterArea[PlayerY - 1][PlayerX] >= 2 && starterArea[PlayerY - 1][PlayerX] != 9) || (starterArea[PlayerY - 1][PlayerX + 1] >= 2 && starterArea[PlayerY - 1][PlayerX + 1] != 9) || (starterArea[PlayerY - 1][PlayerX + 2] >= 2 && starterArea[PlayerY - 1][PlayerX + 2] != 9) || (starterArea[PlayerY - 1][PlayerX + 3] >= 2 && starterArea[PlayerY - 1][PlayerX + 3] != 9) || (starterArea[PlayerY - 1][PlayerX + 4] >= 2 && starterArea[PlayerY - 1][PlayerX + 4] != 9)) && (input == 119 || input == 72))
        {

            return abbruch = 2;

        }
        //unten
        else if (((starterArea[PlayerY + 1][PlayerX] >= 2 && starterArea[PlayerY + 1][PlayerX] != 9) || (starterArea[PlayerY + 1][PlayerX + 1] >= 2 && starterArea[PlayerY + 1][PlayerX + 1] != 9) || (starterArea[PlayerY + 1][PlayerX + 2] >= 2 && starterArea[PlayerY + 1][PlayerX + 2] != 9) || (starterArea[PlayerY + 1][PlayerX + 3] >= 2 && starterArea[PlayerY + 1][PlayerX + 3] != 9) || (starterArea[PlayerY + 1][PlayerX + 4] >= 2 && starterArea[PlayerY + 1][PlayerX + 4] != 9)) && (input == 115 || input == 80))
        {
            return abbruch = 2;

        }
        //rechts
        else if (((starterArea[PlayerY][PlayerX + 1] >= 2 && starterArea[PlayerY][PlayerX + 1] != 9) || (starterArea[PlayerY][PlayerX + 1 + 1] >= 2 && starterArea[PlayerY][PlayerX + 1 + 1] != 9) || (starterArea[PlayerY][PlayerX + 2 + 1] >= 2 && starterArea[PlayerY][PlayerX + 2 + 1] != 9) || (starterArea[PlayerY][PlayerX + 3 + 1] >= 2 && starterArea[PlayerY][PlayerX + 3 + 1] != 9) || (starterArea[PlayerY][PlayerX + 4 + 1] >= 2 && starterArea[PlayerY][PlayerX + 4 + 1] != 9)) && (input == 100 || input == 77))
        {
            return abbruch = 2;

        }
        //links
        else if (((starterArea[PlayerY][PlayerX - 1] >= 2 && starterArea[PlayerY][PlayerX - 1] != 9) || (starterArea[PlayerY][PlayerX + 1 - 1] >= 2 && starterArea[PlayerY][PlayerX + 1 - 1] != 9) || (starterArea[PlayerY][PlayerX + 2 - 1] >= 2 && starterArea[PlayerY][PlayerX + 2 - 1] != 9) || (starterArea[PlayerY][PlayerX + 3 - 1] >= 2 && starterArea[PlayerY][PlayerX + 3 - 1] != 9) || (starterArea[PlayerY][PlayerX + 4 - 1] >= 2 && starterArea[PlayerY][PlayerX + 4 - 1] != 9)) && (input == 97 || input == 75))
        {
            return abbruch = 2;

        }

        else
        {

            return abbruch = 0;
        }

    
}

void PlayersMovement(int& input, int abbruch, int& area, int& sword, char starterArea[][COLS], int& lastNumberPressed, int& swordAnimationPhase, int inventory[], int& swordCooldown, int firstTimeInArea[], Zombie zombies[])
{
    int i;
    int k;

    //fürs nach oben scrollen
    gotoxy(140, 1);
    printf(" ");
    //input = _getch();

    if (input == 119 || input == 72)
    {
        //playerY--;
        Borders(area, abbruch, starterArea, input, sword, lastNumberPressed);

        if (abbruch == 0)
        {
            PlayerY--;
            for (int i = 0; i <= 4; i++)
            {
                starterArea[PlayerY][PlayerX + i] = 9;
                starterArea[PlayerY + 1][PlayerX + i] = 0;
            }


            gotoxy(PlayerX, PlayerY);
            printf("[\xC2\xB0-\xC2\xB0]");
            /*
            gotoxy(playerX - 1, playerY);
            printf("%d%d%d%d%d%d%d%d", starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
            */


            Sword(sword, lastNumberPressed, input, starterArea);

            lastNumberPressed = 1;

            gotoxy(PlayerX, PlayerY + 1);
            printf("     ");

        }
        else
        {
            //lastNumberPressed = 1;
            //playerY++;
        }
    }
    else if (input == 97 || input == 75)
    {

        //playerX -= 2;
        Borders(area, abbruch, starterArea, input, sword, lastNumberPressed);


        if (abbruch == 0)
        {
            PlayerX -= 2;
            for (int i = 0; i < 2; i++)
            {
                starterArea[PlayerY][PlayerX + i] = 9;

                starterArea[PlayerY][PlayerX + i + 5] = 0;
            }
            gotoxy(PlayerX, PlayerY);
            printf("[\xC2\xB0-\xC2\xB0]");
            /*
            gotoxy(playerX - 1, playerY);
            printf("%d%d%d%d%d%d%d%d", starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
            */

            Sword(sword, lastNumberPressed, input, starterArea);

            lastNumberPressed = 2;

            gotoxy(PlayerX + 5, PlayerY);
            printf("  ");
        }
        else
        {
            //lastNumberPressed = 2;

            //playerX += 2;

        }
    }
    else if (input == 115 || input == 80)
    {

        //playerY++;
        Borders(area, abbruch, starterArea, input, sword, lastNumberPressed);

        if (abbruch == 0)
        {
            PlayerY++;
            for (int i = 0; i <= 4; i++)
            {
                starterArea[PlayerY][PlayerX + i] = 9;

                starterArea[PlayerY - 1][PlayerX + i] = 0;
            }

            gotoxy(PlayerX, PlayerY);
            printf("[\xC2\xB0-\xC2\xB0]");  
            /*
             gotoxy(playerX - 1, playerY);
             printf("%d%d%d%d%d%d%d%d", starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
             */


            Sword(sword, lastNumberPressed, input, starterArea);

            lastNumberPressed = 3;

            gotoxy(PlayerX, PlayerY - 1);
            printf("     ");
        }
        else
        {
            //lastNumberPressed = 3;

            // playerY--;

        }
    }
    else if (input == 100 || input == 77)
    {

        //playerX += 2;
        Borders(area, abbruch, starterArea, input, sword, lastNumberPressed);

        if (abbruch == 0)
        {
            PlayerX += 2;
            for (int i = 0; i < 2; i++)
            {
                    starterArea[PlayerY][PlayerX + 3 + i] = 9;
                    starterArea[PlayerY][PlayerX - i - 1] = 0;
            }


            gotoxy(PlayerX, PlayerY);
            printf("[\xC2\xB0-\xC2\xB0]");

            //gotoxy(PlayerX - 2, PlayerY);
            //printf("%d%d%d%d%d%d%d%d%d",starterArea[PlayerY][PlayerX - 2], starterArea[PlayerY][PlayerX - 1], starterArea[PlayerY][PlayerX], starterArea[PlayerY][PlayerX + 1], starterArea[PlayerY][PlayerX + 2], starterArea[PlayerY][PlayerX + 3], starterArea[PlayerY][PlayerX + 4], starterArea[PlayerY][PlayerX + 5], starterArea[PlayerY][PlayerX + 6]);
            

            Sword(sword, lastNumberPressed, input, starterArea);
            lastNumberPressed = 4;

            gotoxy(PlayerX - 2, PlayerY);
            printf("  ");
        }
        else
        {
            //lastNumberPressed = 4;

            //playerX -= 2;

        }
    }
    else if (input == 101)
    {
        int SeenValue = 0;
        for (i = 1; i <= 2; i++)
        {
            if (starterArea[PlayerY][PlayerX + 4 + i] > 1)
            {
                SeenValue = starterArea[PlayerY][PlayerX + 4 + i];
                break;
            }
        }
        for (i = 1; i <= 2; i++)
        {
            if (starterArea[PlayerY][PlayerX - i] > 1)
            {
                SeenValue = starterArea[PlayerY][PlayerX - i];
                break;
            }
        }
        for (i = 0; i < 5; i++)
        {
            if (starterArea[PlayerY + 1][PlayerX + i] > 1)
            {
                SeenValue = starterArea[PlayerY + 1][PlayerX + i];
                break;
            }
        }
        for (i = 0; i < 5; i++)
        {
            if (starterArea[PlayerY - 1][PlayerX + i] > 1)
            {
                SeenValue = starterArea[PlayerY - 1][PlayerX + i];
                break;
            }
        }
        

        if (area == 1)
        {
            //für 2
            if (SeenValue == 2)
            {
                    TextPrinter(5, 46, "stuff that you need for some science shit", 2000);
            }

            //für 3
            else if (SeenValue == 3)
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("A Laptop...");
                Sleep(1000);
                gotoxy(17, 46);
                printf("on the screen is a indian guy giving a tutorial on how to make a dissolvant acid *you finish the video*");
                Sleep(6000);
                gotoxy(5, 46);
                printf("                                                                                                                      ");

                inventory[1] = 1;

                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

            }

            //für 4
            else if (SeenValue == 4)
            {
                TextPrinter(5, 46, "*A paper with lots of science, that you are to dumb for!*", 3000);
            }
            //für 5
            else if (SeenValue == 5)
            {
                TextPrinter(5, 46, "*A microscope with blood on it.*", 2000);
            }
            //für 6 tools
            else if (SeenValue == 6)
            {
                TextPrinter(5, 46, "*A couple of tools* and no you cant pick them up because im to lazy*", 5000);
            }
            // für 7
            else if (SeenValue == 7)
            {
                TextPrinter(5, 46, "*the door opens*", 1000);

                PlayerX = 42;
                PlayerY = 11;
                area = 2;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }

            //für 8 sickbed
            else if (SeenValue == 8)
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("A sickbed");
                Sleep(1000);
                gotoxy(5, 46);
                printf("         ");
                TextPrinter(5, 46, "*the door opens*", 1000);
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
            //für 10 standard Zombie(kein loot)
            else if (SeenValue == 10)
            {
                TextPrinter(5, 46, "Hes a btch with no loot", 2000);
            }
            //für 11 (some random stuff)
            else if (SeenValue == 11)
            {
                TextPrinter(5, 46, "Im to stupid to think of other stuff", 4000);
            }    
            //für 20 DoctorsZombie
            else if (SeenValue == 20)
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("He seemed to be a lab supervisor...");
                Sleep(2000);
                if (inventory[0] == 0)
                {
                    printf(" *you took his ID Badge*");
                    Sleep(2000);
                    inventory[0] = 1;
                }
                gotoxy(5, 46);
                printf("                                                      ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
        }
        else if (area == 2)
        {
            // door to the lagerraum
            if (SeenValue == 2)
            {

                TextPrinter(5, 46, "*the door opens*", 1000);

                PlayerX = 115;
                PlayerY = 16;
                area = 3;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);


            }
            //door to the exit
            else if (SeenValue == 3)
            {
                if (inventory[9] == 1)
                {
                    TextPrinter(5, 46, "*the door opens*", 1000);
                }
                else
                {
                    TextPrinter(5, 46, "*the door needs electricity to open*", 3000);
                }
            }
            // door to the lab
            else if (SeenValue == 4)
            {
                TextPrinter(5, 46, "*the door opens*", 1000);
                PlayerX = 69;
                PlayerY = 2;
                area = 1;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }
            // door to the closet
            else if (SeenValue == 5)
            {
                TextPrinter(5, 46, "*the door opens*", 1000);
                PlayerX = 47;
                PlayerY = 29;
                area = 6;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }
            // the open door
            else if (SeenValue == 6)
            {
                TextPrinter(5, 46, "*the door opens*", 1000);
                PlayerX = 10;
                PlayerY = 29;
                area = 5;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }
            // left dead person
            else if (SeenValue == 7)
            {
                TextPrinter(5, 46, "This person died a terrifying death", 3000);
            }
            // the rolling bed
            else if (SeenValue == 8)
            {
                TextPrinter(5, 46, "what happend to the person on that bed?", 4000);
            }
            // the fast Zombie
            else if (SeenValue == 10)
            {
                TextPrinter(5, 46, "Is he like a mutation or what was that", 3000);
            }
            // the eaten up person
            else if (SeenValue == 11)
            {
                gotoxy(5, 46);
                printf("Hey are you still alive?");
                Sleep(2000);
                gotoxy(5, 46);
                printf("                        ");
                gotoxy(5, 46);
                printf("*silence*");
                Sleep(1000);
                gotoxy(5, 46);
                printf("         ");

                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
            else if (SeenValue == 12)
            {
                TextPrinter(5, 46, "yeah I dont think hes alive!", 2000);
            }
        }
        else if (area == 3)
        {
            // chem bottles
            if (SeenValue == 2)
            {
                TextPrinter(5, 46, "*Assorted chemical bottles. Labels are faded.*", 3000);
            }
            // drums
            else if (SeenValue == 3)
            {
                TextPrinter(5, 46, "*Heavy chemical drums. Too large to move.*", 3000);
            }
            // reagents
            else if (SeenValue == 4)
            {
                TextPrinter(5, 46, "*Various lab reagents. Some look unstable.*", 3000);
            }
            // acids
            else if (SeenValue == 5)
            {
                TextPrinter(5, 46, "*Strong acids. The container is still intact.*", 3000);
                if (inventory[1] == 1 && inventory[2] != 1)
                {
                    TextPrinter(5, 46, "Always nice *You grab the container*", 3000);
                    inventory[2] = 1;
                }
            }
            // boxes
            else if (SeenValue == 6)
            {
                TextPrinter(5, 46, "*Cardboard boxes filled with paperwork.*", 3000);
            }
            // kits
            else if (SeenValue == 7)
            {
                TextPrinter(5, 46, "*Emergency kits. Most are empty.*", 2000);
            }
            // PPE
            else if (SeenValue == 8)
            {
                TextPrinter(5, 46, "*Protective gear. Some pieces are missing.*", 3000);
            }
            else if (SeenValue == 10)
            {
                TextPrinter(5, 46, "Hes a btch with no loot", 2000);
            }
            // sterile goods
            else if (SeenValue == 51)
            {
                TextPrinter(5, 46, "*Sterile supplies sealed in plastic.*", 3000);
            }
            // screwdrivers
            else if (SeenValue == 52)
            {
                TextPrinter(5, 46, "*A set of screwdrivers. Still usable.*", 3000);
                if (inventory[1] != 1 && inventory[6] != 1)
                {
                    TextPrinter(5, 46, "Always usefull *You grab it*", 3000);
                    inventory[6] = 1;
                }
            }
            // wires
            else if (SeenValue == 53)
            {
                TextPrinter(5, 46, "*Loose wiring. Insulation is damaged.*", 3000);
            }
            // spare parts
            else if (SeenValue == 54)
            {
                TextPrinter(5, 46, "*Mechanical spare parts. Mostly rusted.*", 3000);
            }
            // bio bags
            else if (SeenValue == 55)
            {
                TextPrinter(5, 46, "*Biohazard bags. Some are leaking.*", 3000);
            }
            // clamps
            else if (SeenValue == 56)
            {
                TextPrinter(5, 46, "*Metal clamps. Some covered in corrosion.*", 3000);
                if (inventory[1] != 1 && inventory[7] != 1)
                {
                    TextPrinter(5, 46, "They look handy *You grab them*", 3000);
                    inventory[7] = 1;
                }
            }
            // tubes
            else if (SeenValue == 57)
            {
                TextPrinter(5, 46, "*Flexible tubing. Brittle with age.*", 2000);
            }
            // masks
            else if (SeenValue == 58)
            {
                TextPrinter(5, 46, "*Disposable masks. Most are expired.*", 3000);
            }
            // gloves
            else if (SeenValue == 59)
            {
                TextPrinter(5, 46, "*Protective gloves. Still intact.*", 2000);
                if (inventory[1] != 1 && inventory[5] != 1)
                {
                    TextPrinter(5, 46, "Dont want to hurt myself! right? *You equip them*", 4000);
                    inventory[5] = 1;
                }
            }
            // cold packs
            else if (SeenValue == 60)
            {
                TextPrinter(5, 46, "*Cold packs. No longer cold.*", 2000);
            }
            // meds
            else if (SeenValue == 61)
            {
                TextPrinter(5, 46, "*Medication. Labels scratched off.*", 2000);
            }
            // vials
            else if (SeenValue == 62)
            {
                TextPrinter(5, 46, "*Glass vials filled with unknown liquids.*", 3000);
            }
            // syringes
            else if (SeenValue == 63)
            {
                TextPrinter(5, 46, "*Used syringes. Better not touch.*", 3000);
            }
            // sample jar
            else if (SeenValue == 64)
            {
                TextPrinter(5, 46, "*A sample jar containing organic residue.*", 3000);
                if (inventory[1] == 1 && inventory[4] != 1)
                {
                    TextPrinter(5, 46, "great for mixing and maybe usefull *You grab it*", 4000);
                    inventory[4] = 1;
                }
            }
            // cleaning fluids
            else if (SeenValue == 65)
            {
                TextPrinter(5, 46, "*Industrial cleaning fluids. Strong smell.*", 3000);
                if (inventory[1] == 1 && inventory[3] != 1)
                {
                    TextPrinter(5, 46, "*You pick it up*", 2000);
                    inventory[3] = 1;
                }
            }
            // door to the machine room
            else if (SeenValue == 66)
            {
                TextPrinter(5, 46, "*You open the door*", 2000);
                PlayerX = 55;
                PlayerY = 29;
                area = 4;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
                }
            // door to the hallway
            else if (SeenValue == 68)
            {
                TextPrinter(5, 46, "*You open the door*", 2000);
                PlayerX = 2;
                PlayerY = 8;
                area = 2;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
                }
            // breakable pipe
            else if (SeenValue == 69)
            {
                if (!(inventory[2] == 1 && inventory[3] == 1 && inventory[4] == 1)||!(inventory[5] == 1 && inventory[6] == 1 && inventory[7] == 1))
                {
                    TextPrinter(5, 46, "*A damaged pipe fixed to the wall. Maybe its good as a weapon.*", 4000);
                }

                if (inventory[1] == 1)
                {
                    if (inventory[2] != 1)
                    {
                        gotoxy(27, 10);
                        printf("\033[33macids\033[0m");
                    }
                    if (inventory[3] != 1)
                    {
                        gotoxy(90, 24);
                        printf("\033[33mcleaning fluids\033[0m");
                    }
                    if (inventory[4] != 1)
                    {
                        gotoxy(93, 22);
                        printf("\033[33msample jars\033[0m");
                    }
                }
                else
                {
                    if (inventory[7] != 1)
                    {
                        gotoxy(16, 22);
                        printf("\033[33mclamps\033[0m");
                    }
                    if (inventory[5] != 1)
                    {
                        gotoxy(28, 24);
                        printf("\033[33mgloves\033[0m");
                    }
                    if (inventory[6] != 1)
                    {
                        gotoxy(86, 8);
                        printf("\033[33mscrewdrivers\033[0m");
                    }
                }
                if (inventory[2] == 1 && inventory[3] == 1 && inventory[4] == 1)
                {
                    TextPrinter(5, 46, "*You broke down the pipe using chemicals*", 3000);
                    TextPrinter(5, 46, "*You equiped the pipe*", 2000);
                    sword = 1;
                }
                if (inventory[2] != 1 && inventory[5] == 1 && inventory[6] == 1 && inventory[7] == 1)
                {
                    TextPrinter(5, 46, "*You broke down the pipe*", 3000);
                    TextPrinter(5, 46, "*You equiped the pipe*", 2000);
                    sword = 1;
                }
            }
            
        }
        else if (area == 4)
        {
            if (SeenValue == 2)
            {
                TextPrinter(5, 46, "Please Hargassner I need this!!!", 3000);
            }
            else if (SeenValue == 3)
            {
                if (inventory[8] == 1)
                {
                    TextPrinter(5, 46, "*The generator starts running*", 3000);
                    inventory[9] = 1;
                    gotoxy(89, 9);
                    printf("\033[5;32mo\033[0m");
                }
                else
                {
                    TextPrinter(5, 46, "*Generator not running, missing key*", 3000);
                }
            }
            else if (SeenValue == 4)
            {
                if (inventory[9] == 1)
                    TextPrinter(5, 46, "*Control systems are active under emergency power.*", 3000);
                else
                    TextPrinter(5, 46, "*The control server appear to be offline.*", 3000);
            }
            else if (SeenValue == 5)
            {
                TextPrinter(5, 46, "*You notice this server is used for backups and data storage.*", 3000);
            }
            else if (SeenValue == 6)
            {
                TextPrinter(5, 46, "*You open the door*", 2000);
                PlayerX = 55;
                PlayerY = 3;
                area = 3;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }
            else if (SeenValue == 7)
            {
                TextPrinter(5, 46, "*VOLVO i need a GOLD GOLD GOLD*", 2000);
            }
            }
        else if (area == 5)
        {
            // Woman room
            if (SeenValue == 2)
            {
                TextPrinter(5, 46, "DLC needed to unlock the woman's bathroom", 4000);
            }
            //door to the hallway
            else if (SeenValue == 3)
            {
                TextPrinter(5, 46, "*You walk through the door*", 2000);
                PlayerX = 35;
                PlayerY = 3;
                area = 2;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }
            // shower
            else if (SeenValue == 4)
            {
                TextPrinter(5, 46, "The floor is still a bit Wet", 2000);
            }
            // stalls
            else if (SeenValue == 5)
            {
                TextPrinter(5, 46, "Holy SHIT", 2000);
            }
            else if (SeenValue == 6)
            {
                TextPrinter(5, 46, "wow almost completly full of piss!", 3000);
            }
            else if (SeenValue == 7)
            {
                TextPrinter(5, 46, "* 3 sinks, water won't come out *", 3000);
            }
        }
        else if (area == 6)
        {
            // closed lockers
            if (SeenValue == 2)
            {
                TextPrinter(5, 46, "*You can't open this locker*", 2000);
            }
            // bench
            else if (SeenValue == 3)
            {
                TextPrinter(5, 46, "*Just a ordinary bench*", 2000);
            }
            // key holder
            else if (SeenValue == 4)
            {
                if (inventory[8] == 0)
                {
                    char input2;
                    vector<char> code;
                    vector<char> actChar(4);
                    actChar[0] = '1';
                    actChar[1] = '3';
                    actChar[2] = '5';
                    actChar[3] = '3';
                    gotoxy(5, 46);
                    printf("Press esc to exit, Enter Code: ");
                    while (true)
                    {
                        if (_kbhit()) {
                            input = _getch();

                            if (input == 27)
                            {
                                gotoxy(5, 46);
                                printf("                                    ");
                                break;
                            }
                            code.push_back(input);

                            gotoxy(36 + code.size(), 46);
                            printf("*");
                            
                            if (code.size() == 4)
                            {
                                if (code == actChar)
                                {
                                    gotoxy(5, 46);
                                    printf("                                    ");
                                    TextPrinter(5, 46, "*it opens and you acquire a key*", 2000);
                                    inventory[8] = 1;
                                    break;
                                }
                                else
                                {
                                    gotoxy(5, 46);
                                    printf("                                    ");
                                    TextPrinter(5, 46, "*wrong code buddy*", 1000);
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    TextPrinter(5, 46, "*You already took what was inside*", 2000);
                }
            }
            // sink
            else if (SeenValue == 5)
            {
                if(inventory[9] == 0)
                    TextPrinter(5, 46, "*Water isn't flowing from this sink*", 2000);
                else
                    TextPrinter(5, 46, "*Water is flowing from this sink*", 2000);
            }
            // bin
            else if (SeenValue == 6)
            {
                TextPrinter(5, 46, "*A bin with a couple of paper towels inside*", 3000);
            }
            // door
            else if (SeenValue == 7)
            {
                TextPrinter(5, 46, "*You walk through the door*", 2000);
                PlayerX = 115;
                PlayerY = 3;
                area = 2;
                ChangeArea(area, starterArea, firstTimeInArea, inventory, zombies);
            }
            // bottom body
            else if (SeenValue == 8)
            {
                TextPrinter(5, 46, "*Well he's dead*", 1000);
            }
            else if (SeenValue == 10)
            {
                TextPrinter(5, 46, "Hes a btch with no loot", 2000);
            }
            // philips zombie
            else if (SeenValue == 11)
            {
                if (inventory[11] == 0)
                {
                    TextPrinter(5, 46, "*You get the key to philip's locker*", 2000);
                    inventory[11] = 1;
                }
                else
                    TextPrinter(5, 46, "*He had nothing else of value*", 2000);
            }
            // top body
            else if (SeenValue == 21)
            {
                TextPrinter(5, 46, "*Don't wish to be him!*", 2000);
            }
            // code locker
            else if (SeenValue == 22)
            {
                if (inventory[10] == 0)
                {
                    TextPrinter(5, 46, "*In the locker are a couple of postit's, on them are numbers*", 4000);
                    inventory[10] = 1;
                }
                TextPrinter(5, 46, "*c:5; a:1; d:3; b:3*", 4000);
            }
            // phillips secret locker
            else if (SeenValue == 23)
            {
                if(inventory[11] == 1)
                    TextPrinter(5, 46, "*In this locker is: 1 Bottle of lube, 69 different Dildos and an invitation letter from sir mister Epstein*",5000);
                else
                    TextPrinter(5, 46, "*philips locker (key needed)*", 2000);
            }

        }
    }
    else if (input == 32)
    {

        if (sword == 1 && swordCooldown == 0)
        {
            swordAnimationPhase = 1;
        }
        //lastNumberPressed = 5;
    }
    //Sleep(75);
}
