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


#define w 119
#define a 97
#define s 115
#define d 100
#define SPACEBAR  32
#define e 101
#define ROWS 47
#define COLS 162
#define PlayerSize 4
#define HowManyZombiesExist 2
int PlayerX = 22;//62
int PlayerY = 11;//17


using namespace std;
// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) &&
        (row < ROWS) &&
        (col >= 0) &&
        (col < COLS);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int starterArea[][COLS], int row, int col, Pair src, int directionX, int directionY)
{
    bool result = true;
    if (row == src.first + directionY && col == src.second + directionX) {
        result = ((starterArea[row][col] == 0 || starterArea[row][col] == 9) &&
            (starterArea[row][col + 1] == 0 || starterArea[row][col + 1] == 9) &&
            (starterArea[row][col + 2] == 0 || starterArea[row][col + 2] == 9) &&
            (starterArea[row][col + 3] == 0 || starterArea[row][col + 3] == 9) &&
            (starterArea[row][col + 4] == 0 || starterArea[row][col + 4] == 9) &&
            (starterArea[row][col + 5] == 0 || starterArea[row][col + 5] == 9) &&
            (starterArea[row][col + 6] == 0 || starterArea[row][col + 6] == 9));
    }
    else {
        result = ((starterArea[row][col] == 0 || starterArea[row][col] == 9) &&
            (starterArea[row][col + 1] == 0 || starterArea[row][col + 1] == 9) &&
            (starterArea[row][col + 2] == 0 || starterArea[row][col + 2] == 9) &&
            (starterArea[row][col + 3] == 0 || starterArea[row][col + 3] == 9) &&
            (starterArea[row][col + 4] == 0 || starterArea[row][col + 4] == 9) &&
            (starterArea[row][col + 5] == 0 || starterArea[row][col + 5] == 9));
    }

    //printf("Checking Cell (%d, %d) -> %s\n", row, col, result ? "Open" : "Blocked");
    return result;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, int destY, int destX) {
    int i;
    //for ( i = 0; i < 5; i++)
    //{

        if (row == destY && col == destX) 
        {
            //printf("Checking: row=%d, col=%d, dest=(%d, %d)\n", row, col, dest.first, dest.second);
            //printf("Destination reached!\n");
            return true;
        }
    //}
    //printf("Checking: row=%d, col=%d, i = %d dest=(%d, %d)\n", row, col, i, dest.first, dest.second);
    //printf("Not a destination.\n");
    return false;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COLS], int row, int col,int& ZombieposX,int& ZombieposY, int& waitForNextZombieMove, bool& ZombieXMove)
{
    //int row = destY;
    //int col = destX;
    int XChange = 0;
    int YChange = 0;
    stack<Pair> Path;

    if (cellDetails[row][col].parent_i == -1 && cellDetails[row][col].parent_j == -1) {
        //printf("Processing Cell: (%d, %d) -> f: %.2f, g: %.2f, h: %.2f\n", row, col, cellDetails[row][col].f, cellDetails[row][col].g, cellDetails[row][col].h);

        //return;
    }
    // Reconstruct the path
    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
        //printf("z");
    }
    Path.push(make_pair(row, col)); // Push the starting position

    // Find the first move after the start position
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        
        // If this is the first move after the start, update Zombie position
        if (!(p.first == ZombieposY && p.second == ZombieposX)) 
        {
            if (ZombieposX - p.second < -1)
            {
                XChange--;
                ZombieposX++;

            }
            else
            {
                XChange = ZombieposX - p.second;
                ZombieposX = p.second;
            }
            YChange = ZombieposY - p.first;
            ZombieposY = p.first;
            break;  // Exit loop after finding the first move

        }
    }
    if (XChange != 0)
        ZombieXMove = true;
    else
        ZombieXMove = false;
    // Move the zombie to the new position
    
    gotoxy(ZombieposX + XChange, ZombieposY + YChange);
    printf("       ");
    gotoxy(ZombieposX, ZombieposY);
    printf("\033[0;32m[-º_°]-\033[0m");
       
    waitForNextZombieMove++;
}
class Zombie
{
public:
    int Zombielives;
    int ZombieArmor;
    int Zombiedamage;
    int Zombiespeed;
    int ZombieposX;
    int ZombieposY;
    int waitForNextZombieMove;
    int win;
    int playerX;
    int playerY;
    int ZombieSize;
    int ZombieDeathValue;
    bool ZombieXMove;

    Pair src;
    
    // Constructor to initialize values
    Zombie(int posX, int posY, int lives, int armor, int damage, int speed, int waitfornextzombiemove, int win, int size, int zombieDeathValue) {
        Zombielives = lives;
        ZombieArmor = armor;
        Zombiedamage = damage;
        Zombiespeed = speed;
        ZombieposX = posX;
        ZombieposY = posY;
        ZombieSize = size;
        ZombieDeathValue = zombieDeathValue;
        waitForNextZombieMove = waitfornextzombiemove;

        src = make_pair(ZombieposY, ZombieposX);
    }
    void CloseRangeMovement(int starterArea[][COLS],Pair src,Pair dest,int& waitForNextZombieMove, int& win, bool& ZombieXMove, int ZombieDeathValue);
};



void PlayersMovement(int& input, int abbruch, int& area, int& sword, int starterArea[][COLS], int& lastNumberPressed, int& swordAnimationPhase, int keys[], int& swordCooldown);
void AreaOfMap(int area, int starterArea[][COLS]);
int Borders(int area, int& abbruch, int starterArea[][COLS], int input, int& sword, int lastNumberPressed);
void ECheck(int area, int starterArea[][COLS], int sword, int lastNumberPressed, int input);
void Sword(int sword, int& lastNumberPressed, int input, int starterArea[][COLS]);
void WaitingTime(int& waitForNextMove, int& waitForSwordAnimation, int lastNumberPressed, int& swordCooldown, Zombie zombies[]);
void swordAnimations(int lastNumberPressed, int starterArea[][COLS], int swordAnimationPhase, int area, Zombie& zombie);
void HitCheck(int SwordX, int SwordY, int area, Zombie& zombie, int howFar, int lastNumberPressed);
bool VisionCheck(int starterX, int starterY, int targetX, int targetY, int starterArea[][COLS], int starterArrayValue, int targetArrayValue);
void ChangeArea(int& area, int starterArea[][COLS]);

int main()
{
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
    //0: labdoor 1: ?
    int keys[1] = { 0 };
    int waitForNextMove = 0;
    cursoroff();
    setlocale(LC_ALL, "");
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
    SetConsoleOutputCP(CP_UTF8);

    srand((unsigned)time(NULL));



    gotoxy(PlayerX, PlayerY);
    printf("[°-°]");
    AreaOfMap(area, starterArea);
    area = 2;
    ChangeArea(area, starterArea);
    // X, Y, life, armor, damage, speed, waitingtime, win, size, zombieDeathValue
    Zombie zombies[HowManyZombiesExist] = 
    {
         Zombie(54,27, 3, 1, 2, 20, 0, 0, 7, 20),  // zombie1
         Zombie(120,29, 3, 1, 2, 20, 0, 0, 7, 10)   // zombie2
    };
     
    cursoroff();

    while (win == 0)
    {
        for (int i = 0; i < HowManyZombiesExist; i++)
        {
            if (area == 1)
            {
                if (zombies[i].waitForNextZombieMove == 0)
                {

                    // Destination is the left-most top-most corner
                    Pair dest = make_pair(PlayerY, PlayerX);

                    // Source is the left-most bottom-most corner
                    zombies[i].src = make_pair(zombies[i].ZombieposY, zombies[i].ZombieposX);

                    if (zombies[i].Zombielives > 0)
                    {
                        zombies[i].CloseRangeMovement(starterArea, zombies[i].src, dest, zombies[i].waitForNextZombieMove, win, zombies[i].ZombieXMove, zombies[i].ZombieDeathValue);
                    }

                }
            }
        }
        
        if (_kbhit()) {
            if (waitForNextMove == 0 && swordAnimationPhase == 0)
            {
                input = _getch();
                PlayersMovement(input, abbruch, area, sword, starterArea, lastNumberPressed, swordAnimationPhase, keys, swordCooldown);
                ECheck(area, starterArea, sword, lastNumberPressed, input);
                waitForNextMove++;
            }
        }

        if (swordAnimationPhase > 0 && waitForSwordAnimation == 0)
        {
            //printf("%d", swordAnimationPhase);
            if ((lastNumberPressed == 1 || lastNumberPressed == 3) && swordAnimationPhase < 6)
            {
                for (int i = 0; i < HowManyZombiesExist; i++)
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
                
                swordAnimationPhase++;
                waitForSwordAnimation++;
            }
            else if ((lastNumberPressed == 2 || lastNumberPressed == 4) && swordAnimationPhase < 5)
            {
                for (int i = 0; i < 2; i++)
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

        //AreaOfMap(area, playerX, playerY, starterArea);
        Sleep(1);
        WaitingTime(waitForNextMove, waitForSwordAnimation, lastNumberPressed, swordCooldown, zombies);
        

    }

    //gotoxy(5, 46);
    //printf("OHHHHH P.DIDDY NOOOOOOOOOOOO"),
    Sleep(5000);
}
void ChangeArea(int& area, int starterArea[][COLS])
{
    int NumberForDoor = 1;
    system("cls");
   
    gotoxy(PlayerX, PlayerY);
    printf("[°-°]");

    // set everything to 0
    memset(starterArea, 0, ROWS * COLS * sizeof(int));

    if (area == 2)
    {
        // second row changed to 1
        memset(&starterArea[2], 1, COLS * sizeof(int));
        for (int i = 0; i < COLS; i++)
        {
            gotoxy(i, 2);
            printf("_");
        }

        // 11the row changed to 1
        memset(&starterArea[12][0], 1, (COLS - 40) * sizeof(int));
        for (int i = 1; i < COLS - 41; i++)
        {
            gotoxy(i, 12);
            printf("_");
        }
        // Left Row down 
        for (int i = 0; i < 10; i++)
        {
            starterArea[i + 3][1] = 1;
            gotoxy(1, i + 3);
            printf("|");
        }
        // Right Row all the way down 
        for (int i = 0; i < 30; i++)
        {
            starterArea[i + 3][COLS - 1] = 1;
            gotoxy(COLS - 1, i + 3);
            printf("|");
        }
        // the Row for the Right corner
        for (int i = 0; i < 20; i++)
        {
            starterArea[i + 13][COLS - 41] = 1;
            gotoxy(COLS - 41, i + 13);
            printf("|");
        }
        //The door to the exit
        for (int i = 0; i < 39; i++)
        {
            if (i > 10 && i < 30)
            {
                setcolor(CONSOLE_BROWN);
                NumberForDoor = 9;
            }
            else
            {
                setcolor(CONSOLE_WHITE);
                NumberForDoor = 1;
            }
            starterArea[32][COLS - 40 + i] = NumberForDoor;
            gotoxy(COLS - 40 + i, 32);
            printf("_");
            
        }

    }
}


bool VisionCheck(int starterX, int starterY, int targetX, int targetY, int starterArea[][COLS], int starterArrayValue, int targetArrayValue)
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

void swordAnimations(int lastNumberPressed, int starterArea[][COLS], int swordAnimationPhase, int area, Zombie& zombie)
    {
        if (lastNumberPressed == 1)
        {
            if ((starterArea[PlayerY - 1][PlayerX + 2] == 0) && (starterArea[PlayerY - 1][PlayerX + 3] == 0) && (starterArea[PlayerY - 1][PlayerX + 4] == 0) && (starterArea[PlayerY - 1][PlayerX + 5] == 0))
            {
                if (swordAnimationPhase == 1)
                {
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf("  /");
                    HitCheck(PlayerX + 5, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(100);
                if (swordAnimationPhase == 2)
                {
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf(" / ");
                    HitCheck(PlayerX + 4, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(50);
                if (swordAnimationPhase == 3)
                {
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf("| ");
                    HitCheck(PlayerX + 3, PlayerY - 1, area, zombie, 1, lastNumberPressed);
                }
                //Sleep(50);
                if (swordAnimationPhase == 4)
                {
                    gotoxy(PlayerX + 2, PlayerY - 1);
                    printf("\\ ");
                    HitCheck(PlayerX + 2, PlayerY - 1, area, zombie, 1, lastNumberPressed);

                }
                //Sleep(100);
                if (swordAnimationPhase == 5)
                {
                    gotoxy(PlayerX + 2, PlayerY - 1);
                    printf(" ");
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf("| ");
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

void Zombie::CloseRangeMovement(int starterArea[][COLS], Pair src, Pair dest, int& waitForNextZombieMove, int& win, bool& ZombieXMove, int ZombieDeathValue)
    {
    int randomNumber;



        this->ZombieposY;
        this->ZombieposX;

        bool hittingWall = false;
        
        
        
        

        //check if the Zombie hasnt got vision
        if (VisionCheck(ZombieposX, ZombieposY, PlayerX, PlayerY, starterArea, ZombieDeathValue, 9))
        {
            randomNumber = rand() % 4;
            
            if (randomNumber == 0)
            {
                for (int i = 0; i < ZombieSize; i++)
                {
                    if (starterArea[ZombieposY - 1][ZombieposX + i] == 0 || starterArea[ZombieposY - 1][ZombieposX + i] == 9)
                    {
                        
                    }
                    else
                    {
                        hittingWall = true;
                        break;
                    }
                }
                if (!hittingWall)
                {
                    ZombieposY--;
                    gotoxy(ZombieposX, ZombieposY + 1);
                    printf("       ");

                }
            }
            else if (randomNumber == 1)
            {
                for (int i = 0; i < ZombieSize; i++)
                {
                    if (starterArea[ZombieposY][ZombieposX - 1 + i] == 0 || starterArea[ZombieposY][ZombieposX - 1 + i] == 9)
                    {
                       
                    }
                    else
                    {
                        hittingWall = true;
                        break;
                    }
                }
                if (!hittingWall)
                {
                    ZombieposX--;
                    gotoxy(ZombieposX + 7, ZombieposY);
                    printf(" ");
                }
            }
            else if (randomNumber == 2)
            {
                for (int i = 0; i < ZombieSize; i++)
                {
                    if (starterArea[ZombieposY + 1][ZombieposX + i] == 0 || starterArea[ZombieposY + 1][ZombieposX + i] == 9)
                    {
                        
                    }
                    else
                    {
                        hittingWall = true;
                        break;
                    }
                }
                if (!hittingWall)
                {
                    ZombieposY++;
                    gotoxy(ZombieposX, ZombieposY - 1);
                    printf("       ");
                }
            }
            else
            {
                for (int i = 0; i < ZombieSize; i++)
                {
                    if (starterArea[ZombieposY][ZombieposX + i + 1] == 0 || starterArea[ZombieposY][ZombieposX + i + 1] == 9)
                    {
                        
                    }
                    else
                    {
                        hittingWall = true;
                        break;
                    }
                }
                if (!hittingWall)
                {
                    ZombieposX++;
                    gotoxy(ZombieposX - 1, ZombieposY);
                    printf(" ");
                }
            }
            gotoxy(ZombieposX, ZombieposY);
            printf("\033[0;32m[-º_°]-\033[0m");

            Zombiespeed = 80;
            waitForNextZombieMove++;
            return;
        }

        Zombiespeed = 20;
        // If the source is out of range
        if (!isValid(src.first, src.second)) {
            printf("Source is invalid\n");
            return;
        }

        // If the destination is out of range
        if (isValid(dest.first, dest.second) == false) {
            printf("Destination is invalid\n");
            return;
        }

        // Either the source or the destination is blocked so the point of dest and src is a blocking unit
        if (isUnBlocked(starterArea, src.first, src.second, src, 0, 0) == false || isUnBlocked(starterArea, dest.first, dest.second, src, 0, 0) == false) {
            //printf("Source or the destination is blocked\n");
            if (isUnBlocked(starterArea, src.first, src.second, src, 0, 0) == false || isUnBlocked(starterArea, dest.first, dest.second - 1, src, -1, 0) == false)
            {
                //printf("Source or the destination is blocked\n");
                return;
            }
        }

        // If the destination cell is the same as source cell
        
        for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
        {
            for (int g = 0; g <= PlayerSize; g++)
            {
                if (isDestination(src.first, src.second + c, dest.first, dest.second + g))
                {
                    win = 2;
                    return;
                }
            }
        }

        // Create a closed list and initialise it to false which
        // means that no cell has been included yet This closed
        // list is implemented as a boolean 2D array
        bool closedList[ROWS][COLS];
        memset(closedList, false, sizeof(closedList));

        // Declare a 2D array of structure to hold the details
        // of that cell
        cell cellDetails[ROWS][COLS];

        int i, j;

        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }

        // Initialising the parameters of the starting node
        i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;

        /*
         Create an open list having information as-
         <f, <i, j>>
         where f = g + h,
         and i, j are the row and column index of that cell
         Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
         This open list is implemented as a set of pair of
         pair.*/
        set<pPair> openList;

        // Put the starting cell on the open list and set its
        // 'f' as 0
        openList.insert(make_pair(0.0, make_pair(i, j)));

        // We set this boolean value as false as initially
        // the destination is not reached.
        bool foundDest = false;

        while (!openList.empty()) {
            pPair p = *openList.begin();
            // Remove this vertex from the open list
            openList.erase(openList.begin());

            // Add this vertex to the closed list
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            /*
             Generating all the 8 successor of this cell

                 N.W   N   N.E
                   \   |   /
                    \  |  /
                 W----Cell----E
                      / | \
                    /   |  \
                 S.W    S   S.E

             Cell-->Popped Cell (i, j)
             N -->  North       (i-1, j)
             S -->  South       (i+1, j)
             E -->  East        (i, j+1)
             W -->  West           (i, j-1)
             N.E--> North-East  (i-1, j+1)
             N.W--> North-West  (i-1, j-1)
             S.E--> South-East  (i+1, j+1)
             S.W--> South-West  (i+1, j-1)*/

             // To store the 'g', 'h' and 'f' of the 8 successors
            double gNew, hNew, fNew;

            //----------- 1st Successor (North) ------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j)) {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i - 1, j + c, dest.first, dest.second + g)) {
                            // Set the Parent of the destination cell
                            //printf("f");
                            cellDetails[i - 1][j + c].parent_i = i;
                            cellDetails[i - 1][j + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i - 1][j] && isUnBlocked(starterArea, i - 1, j, src, 0, -1)) {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i - 1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i - 1][j].f == FLT_MAX
                        || cellDetails[i - 1][j].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j)));

                        // Update the details of this cell
                        cellDetails[i - 1][j].f = fNew;
                        cellDetails[i - 1][j].g = gNew;
                        cellDetails[i - 1][j].h = hNew;
                        cellDetails[i - 1][j].parent_i = i;
                        cellDetails[i - 1][j].parent_j = j;
                    }
                }
            }

            //----------- 2nd Successor (South) ------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j)) {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i + 1, j + c, dest.first, dest.second + g)) {
                            //printf("d");
                            // Set the Parent of the destination cell
                            cellDetails[i + 1][j + c].parent_i = i;
                            cellDetails[i + 1][j + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i + 1][j] && isUnBlocked(starterArea, i + 1, j, src, 0, 1))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i + 1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i + 1][j].f == FLT_MAX
                        || cellDetails[i + 1][j].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j)));
                        // Update the details of this cell
                        cellDetails[i + 1][j].f = fNew;
                        cellDetails[i + 1][j].g = gNew;
                        cellDetails[i + 1][j].h = hNew;
                        cellDetails[i + 1][j].parent_i = i;
                        cellDetails[i + 1][j].parent_j = j;
                    }
                }
            }

            //----------- 3rd Successor (East) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j + 1)) {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i, j + 1 + c, dest.first, dest.second + g)) {
                            // Set the Parent of the destination cell
                            //printf("s");
                            cellDetails[i][j + 1 + c].parent_i = i;
                            cellDetails[i][j + 1 + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i][j + 1] && isUnBlocked(starterArea, i, j + 1, src, 1, 0))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i][j + 1].f == FLT_MAX
                        || cellDetails[i][j + 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j + 1)));

                        // Update the details of this cell
                        cellDetails[i][j + 1].f = fNew;
                        cellDetails[i][j + 1].g = gNew;
                        cellDetails[i][j + 1].h = hNew;
                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 4th Successor (West) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j - 1)) {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i, j - 1 + c, dest.first, dest.second + g)) {
                            // Set the Parent of the destination cell
                            //printf("a");
                            cellDetails[i][j - 1 + c].parent_i = i;
                            cellDetails[i][j - 1 + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i][j - 1] && isUnBlocked(starterArea, i, j - 1, src, -1, 0))
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i][j - 1].f == FLT_MAX
                        || cellDetails[i][j - 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j - 1)));

                        // Update the details of this cell
                        cellDetails[i][j - 1].f = fNew;
                        cellDetails[i][j - 1].g = gNew;
                        cellDetails[i][j - 1].h = hNew;
                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                    }
                }
            }

            //----------- 5th Successor (North-East)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j + 1)) {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i - 1, j + 1 + c, dest.first, dest.second))
                        {
                            // Set the Parent of the destination cell
                            //printf("q");
                            cellDetails[i - 1][j + 1 + c].parent_i = i;
                            cellDetails[i - 1][j + 1 + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i - 1][j + 1] && isUnBlocked(starterArea, i - 1, j + 1, src, 1, -1))
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i - 1][j + 1].f == FLT_MAX
                        || cellDetails[i - 1][j + 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j + 1)));

                        // Update the details of this cell
                        cellDetails[i - 1][j + 1].f = fNew;
                        cellDetails[i - 1][j + 1].g = gNew;
                        cellDetails[i - 1][j + 1].h = hNew;
                        cellDetails[i - 1][j + 1].parent_i = i;
                        cellDetails[i - 1][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 6th Successor (North-West)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j - 1))
            {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i - 1, j - 1 + c, dest.first, dest.second + g)) {
                            // Set the Parent of the destination cell
                            //printf("w");
                            cellDetails[i - 1][j - 1 + c].parent_i = i;
                            cellDetails[i - 1][j - 1 + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i - 1][j - 1] && isUnBlocked(starterArea, i - 1, j - 1, src, -1, -1))
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i - 1][j - 1].f == FLT_MAX
                        || cellDetails[i - 1][j - 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j - 1)));
                        // Update the details of this cell
                        cellDetails[i - 1][j - 1].f = fNew;
                        cellDetails[i - 1][j - 1].g = gNew;
                        cellDetails[i - 1][j - 1].h = hNew;
                        cellDetails[i - 1][j - 1].parent_i = i;
                        cellDetails[i - 1][j - 1].parent_j = j;
                    }
                }
            }

            //----------- 7th Successor (South-East)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j + 1))
            {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i + 1, j + 1 + c, dest.first, dest.second + g))
                        {
                            // Set the Parent of the destination cell
                            //printf("j = %d, c = %d", j, c);
                            //printf("e");

                            cellDetails[i + 1][j + 1 + c].parent_i = i;
                            cellDetails[i + 1][j + 1 + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i + 1][j + 1] && isUnBlocked(starterArea, i + 1, j + 1, src, 1, 1))
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i + 1][j + 1].f == FLT_MAX
                        || cellDetails[i + 1][j + 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j + 1)));

                        // Update the details of this cell
                        cellDetails[i + 1][j + 1].f = fNew;
                        cellDetails[i + 1][j + 1].g = gNew;
                        cellDetails[i + 1][j + 1].h = hNew;
                        cellDetails[i + 1][j + 1].parent_i = i;
                        cellDetails[i + 1][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 8th Successor (South-West)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j - 1))
            {
                // If the destination cell is the same as the
                // current successor
                for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
                {
                    for (int g = 0; g <= PlayerSize; g++)
                    {
                        if (isDestination(i + 1, j - 1 + c, dest.first, dest.second + g))
                        {
                            // Set the Parent of the destination              
                            //printf("r");
                            cellDetails[i + 1][j - 1 + c].parent_i = i;
                            cellDetails[i + 1][j - 1 + c].parent_j = j;
                            //printf("The destination cell is found\n");
                            tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, waitForNextZombieMove, ZombieXMove);
                            foundDest = true;
                            return;
                        }
                    }
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                if (!closedList[i + 1][j - 1] && isUnBlocked(starterArea, i + 1, j - 1, src, -1, 1))
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i + 1][j - 1].f == FLT_MAX
                        || cellDetails[i + 1][j - 1].f > fNew) {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j - 1)));

                        // Update the details of this cell
                        cellDetails[i + 1][j - 1].f = fNew;
                        cellDetails[i + 1][j - 1].g = gNew;
                        cellDetails[i + 1][j - 1].h = hNew;
                        cellDetails[i + 1][j - 1].parent_i = i;
                        cellDetails[i + 1][j - 1].parent_j = j;
                    }
                }
            }
        }

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination cell. This may happen when the
        // there is no way to destination cell (due to
        // blockages)
        if (foundDest == false)
           printf("Failed to find the Destination Cell\n");

        return;
    }

void WaitingTime(int& waitForNextMove, int& waitForSwordAnimation, int lastNumberPressed, int& swordCooldown, Zombie zombies[])
{
    int i;
    for (i = 0; i < HowManyZombiesExist; i++)
    {
        if (zombies[i].waitForNextZombieMove > 0)
        {
            zombies[i].waitForNextZombieMove++;
        }
        if ((zombies[i].waitForNextZombieMove >= zombies[i].Zombiespeed && !zombies[i].ZombieXMove) || (zombies[i].waitForNextZombieMove >= (zombies[i].Zombiespeed / 2)  && zombies[i].ZombieXMove))
        {
            zombies[i].waitForNextZombieMove = 0;
        }
    }

    if (waitForNextMove > 0)
    {
        waitForNextMove++;
        //printf("%d", waitForNextMove);
    }
    if (waitForNextMove >= 6)
    {
        waitForNextMove = 0;
        //printf("d");
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

void Sword(int sword, int& lastNumberPressed, int input, int starterArea[][COLS])
{
    
    if (sword == 1)
    {
        if (input == 119)
        {
            gotoxy(PlayerX + 3, PlayerY - 1);
            printf("|");
        }
        else if (input == 97)
        {
            gotoxy(PlayerX - 3, PlayerY);
            printf("--<");
           
        }
        else if (input == 115)
        {
            gotoxy(PlayerX + 1, PlayerY + 1);
            printf("|");
        }
        else if (input == 100)
        {
            if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY);
                printf(">--");
            }
        }
        // für w
        if (lastNumberPressed == 1 && input == 97)
        {
            if (starterArea[PlayerY - 1][PlayerX + 5] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY - 1);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 1 && input == 115)
        {
            if (starterArea[PlayerY - 2][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY - 2);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 1 && input == 100)
        {
            if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY - 1);
                printf(" ");
            }
        }
        // für a
        else if (lastNumberPressed == 2 && input == 119)
        {
            if (starterArea[PlayerY + 1][PlayerX - 3] == 0 && starterArea[PlayerY + 1][PlayerX - 2] == 0 && starterArea[PlayerY + 1][PlayerX - 1] == 0)
            {
                gotoxy(PlayerX - 3, PlayerY + 1);
                printf("   ");
            }
        }
        else if (lastNumberPressed == 2 && input == 115)
        {
            if (starterArea[PlayerY - 1][PlayerX - 3] == 0 && starterArea[PlayerY - 1][PlayerX - 2] == 0 && starterArea[PlayerY - 1][PlayerX - 1] == 0)
            {
                gotoxy(PlayerX - 3, PlayerY - 1);
                printf("   ");
            }
        }
        else if (lastNumberPressed == 2 && input == 100)
        {
            if (starterArea[PlayerY][PlayerX - 5] == 0 && starterArea[PlayerY][PlayerX - 4] == 0 && starterArea[PlayerY][PlayerX - 3] == 0)
            {
                gotoxy(PlayerX - 5, PlayerY);
                printf("   ");
            }
        }
        // für s
        else if (lastNumberPressed == 3 && input == 119)
        {
            if (starterArea[PlayerY + 2][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY + 2);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 3 && input == 97)
        {
            if (starterArea[PlayerY + 1][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY + 1);
                printf(" ");
            }
        }
        else if (lastNumberPressed == 3 && input == 100)
        {
            if (starterArea[PlayerY + 1][PlayerX - 1] == 0)
            {
                gotoxy(PlayerX - 1, PlayerY + 1);
                printf(" ");
            }
        }
        // für d
        else if (lastNumberPressed == 4 && input == 119)
        {
            if (starterArea[PlayerY + 1][PlayerX + 5] == 0 && starterArea[PlayerY + 1][PlayerX + 6] == 0 && starterArea[PlayerY + 1][PlayerX + 7] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY + 1);
                printf("   ");
            }
        }
        else if (lastNumberPressed == 4 && input == 97)
        {
            if (starterArea[PlayerY][PlayerX + 7] == 0 && starterArea[PlayerY][PlayerX + 8] == 0 && starterArea[PlayerY][PlayerX + 9] == 0)
            {
                gotoxy(PlayerX + 7, PlayerY);
                printf("   ");
            }
        }
        else if (lastNumberPressed == 4 && input == 115)
        {
            if (starterArea[PlayerY - 1][PlayerX + 5] == 0 && starterArea[PlayerY - 1][PlayerX + 6] == 0 && starterArea[PlayerY - 1][PlayerX + 7] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY - 1);
                printf("   ");
            }
        }
    }
}

void AreaOfMap(int area, int starterArea[][COLS])
{
    if (area == 1)
    {
        
        
        //Boarder
        gotoxy(4, 1);
        printf("___________________________________________________________________________________________________________________________________");

        for (int i = 2; i < 46; i++) {
            gotoxy(3, i);
            printf("|");
            gotoxy(135, i);
            printf("|");
        }
        
        gotoxy(4, 45);
        printf("___________________________________________________________________________________________________________________________________");
       
        /*//Resurchtable
        gotoxy(26, 28);
        printf("__________________________");



        for (int i = 29; i < 42; i++) {
            gotoxy(25, i);
            printf("%d", starterArea[i][26]);
            gotoxy(52, i);
            printf("|");
        }
        
        gotoxy(32, 30);
        printf("Research Table");
        gotoxy(26, 31);
        printf("__________________________");
        //Laptop
        gotoxy(37, 32);
        printf("|\\_      0~");
        gotoxy(28, 33);
        printf("Laptop   |  \\______");
        gotoxy(37, 34);
        printf("|    |++++|");
        gotoxy(38, 35);
        printf("\\_  |++++|");
        gotoxy(40, 36);
        printf("\\_|____|");
        // Sketches
        gotoxy(42, 37);
        printf("_______");
        gotoxy(41, 38);
        printf("| #§|&| |");
        gotoxy(28, 39);
        printf("sketches     | ||§|& |");
        gotoxy(41, 40);
        printf("| $|§|| |");
        gotoxy(41, 41);
        printf("|_______|");
       
        
        
        gotoxy(25, 42);
        printf("|__________________________|");
        

       

        
        //Junkttable
        gotoxy(7, 2);
        printf("________________________");

        for (int i = 0; i < 9; i++) {
            gotoxy(6, i + 3);
            printf("|");
            gotoxy(31, i + 3);
            printf("|");
        }

        gotoxy(12, 4);
        printf("Junk Table");
        gotoxy(7, 5);
        printf("________________________");
        gotoxy(7, 6);
        printf("j7m@o * p & g % h#q!w(9)r ^");
        gotoxy(7, 7);
        printf("ow(d g#jkdSfjh o%%492f%hs$");
        gotoxy(7, 8);
        printf("t@z W x~ y* 1!b ^c#d(3$");
        gotoxy(7, 9);
        printf("x1yOu7r4mkp6bRvgn9h0d");
        gotoxy(7, 10);
        printf("§f & g!h * D@k ^ l % z$r#q");
        gotoxy(6, 11);
        printf("|________________________|");
        */

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
        
       
        //Bed
        gotoxy(50, 19);
        printf("_________________ _______ ");

        for (int i = 0; i < 5; i++) {
            gotoxy(49, i + 20);
            printf("|");
            gotoxy(75, i + 20);
            printf("|");
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

        for (int i = 0; i < 5; i++)
        {
            gotoxy(67, i + 20);
            printf("|");
        }


        gotoxy(21, 33);
        printf("_______________________________________________________________________________________________");
        for (int i = 0; i < 8; i++)
        {
            gotoxy(20, 34 + i);
            printf("|");
            gotoxy(116, 34 + i);
            printf("|");
        }
        gotoxy(20, 41);
        printf("|_______________________________________________________________________________________________|");

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

  //       _______
  //      |       |
  //      |       |
  //      |_______|
  // |__  |scanner|                  
  // |  | |_______|
  //      |       |
  //      |       |
  //      |       |
  //      |_______|


        /*
        gotoxy(115, 32);
        printf("_______");
        gotoxy(114, 33);
        printf("|Potions|");
        gotoxy(114, 34);
        printf("|_______|");
        gotoxy(114, 35);
        printf("|  \033[0;32m[ ]\033[0m  |  ");
        gotoxy(114, 36);
        printf("|  \033[0;32m[X~~\033[0m |   ");
        gotoxy(114, 37);
        printf("|_______|");

        */
        
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 18; i++) {
            gotoxy(69 + i, 1);
            printf("_");
            
        }
        setcolor(CONSOLE_WHITE);

    }
}

void ECheck(int area, int starterArea[][COLS], int sword, int lastNumberPressed, int input)
{
        int i;
        if (((starterArea[PlayerY][PlayerX] >= 2 && starterArea[PlayerY][PlayerX] != 9) || (starterArea[PlayerY][PlayerX + 1] >= 2 && starterArea[PlayerY][PlayerX + 1] != 9) || (starterArea[PlayerY][PlayerX + 2] >= 2 && starterArea[PlayerY][PlayerX + 2] != 9) || (starterArea[PlayerY][PlayerX + 3] >= 2 && starterArea[PlayerY][PlayerX + 3] != 9) || (starterArea[PlayerY][PlayerX + 4] >= 2 && starterArea[PlayerY][PlayerX + 4] != 9)))
        {

            gotoxy(5, 46);
            printf("*press e to interact*");
            //waitForECheck[1] = playerX + i;
            //waitForECheck[2] = playerY + k;
            //gotoxy(playerX + i, playerY + k);
            //printf("   ");


        }
        //oben
        else if (((starterArea[PlayerY - 1][PlayerX] >= 2 && starterArea[PlayerY - 1][PlayerX] != 9) || (starterArea[PlayerY - 1][PlayerX + 1] >= 2 && starterArea[PlayerY - 1][PlayerX + 1] != 9) || (starterArea[PlayerY - 1][PlayerX + 2] >= 2 && starterArea[PlayerY - 1][PlayerX + 2] != 9) || (starterArea[PlayerY - 1][PlayerX + 3] >= 2 && starterArea[PlayerY - 1][PlayerX + 3] != 9) || (starterArea[PlayerY - 1][PlayerX + 4] >= 2 && starterArea[PlayerY - 1][PlayerX + 4] != 9)))
        {

            gotoxy(5, 46);
            printf("*press e to interact*");
            //waitForECheck[4] = playerX + i;
            //waitForECheck[5] = playerY + k; 
            //Sleep(150);
            //gotoxy(playerX + i, playerY + k);
            //printf("   ");

        }
        //unten
        else if (((starterArea[PlayerY + 1][PlayerX] >= 2 && starterArea[PlayerY + 1][PlayerX] != 9) || (starterArea[PlayerY + 1][PlayerX + 1] >= 2 && starterArea[PlayerY + 1][PlayerX + 1] != 9) || (starterArea[PlayerY + 1][PlayerX + 2] >= 2 && starterArea[PlayerY + 1][PlayerX + 2] != 9) || (starterArea[PlayerY + 1][PlayerX + 3] >= 2 && starterArea[PlayerY + 1][PlayerX + 3] != 9) || (starterArea[PlayerY + 1][PlayerX + 4] >= 2 && starterArea[PlayerY + 1][PlayerX + 4] != 9)))
        {

            gotoxy(5, 46);
            printf("*press e to interact*");
            //waitForECheck[7] = playerX + i;
            //waitForECheck[8] = playerY + k;
            //Sleep(150);
            //gotoxy(playerX + i, playerY + k);
            //printf("   ");

        }
        //rechts
        else if (((starterArea[PlayerY][PlayerX + 4 + 1] >= 2 && starterArea[PlayerY][PlayerX + 4 + 1] != 9) || (starterArea[PlayerY][PlayerX + 4 + 2] >= 2 && starterArea[PlayerY][PlayerX + 4 + 2] != 9)))
        {


            gotoxy(5, 46);
            printf("*press e to interact*");
            //waitForECheck[10] = playerX + i;
            //waitForECheck[11] = playerY + k;
            //Sleep(150);
            //gotoxy(playerX + i, playerY + k);
            //printf("   ");

        }

        //links
        else if (((starterArea[PlayerY][PlayerX - 1] >= 2 && starterArea[PlayerY][PlayerX - 1] != 9) || (starterArea[PlayerY][PlayerX - 2] >= 2 && starterArea[PlayerY][PlayerX - 2] != 9)))
        {

            gotoxy(5, 46);
            printf("*press e to interact*");
            //waitForECheck[13] = playerX + i;
            //waitForECheck[14] = playerY + k;

            //Sleep(150);
            //gotoxy(playerX + i, playerY + k);
            //printf("   ");

        }
        else
        {
            gotoxy(5, 46);
            printf("                     ");
        }
}

int Borders(int area, int& abbruch, int starterArea[][COLS], int input, int& sword, int lastNumberPressed)
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
            if (input == 119)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (starterArea[PlayerY - 1][PlayerX + i] >= 1)
                    {
                        return abbruch = 1;
                    }
                }
            }
            else if (input == 97)
            {
                
                for (int i = 0; i <= 2; i++)
                {
                    if (starterArea[PlayerY][PlayerX - i] >= 1 && starterArea[PlayerY][PlayerX - i] != 9 )
                    {

                        return abbruch = 1;

                    }
                }
            }
            else if (input == 115)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9)
                    {

                        return abbruch = 1;
                    }
                }
            }
            else if (input == 100)
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
            if (input == 119)
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
            else if (input == 97)
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
                        if (starterArea[PlayerY + 1][PlayerX + 3])
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
            else  if (input == 115)
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
            else  if (input == 100)
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



            if (input != 119 && lastNumberPressed == 1)
            {
                for (int i = 0; i <= 4; i++)
                {

                    if (input == 97 && (starterArea[PlayerY][PlayerX + 1] == 1 || starterArea[PlayerY][PlayerX] == 1))
                    {
                        return abbruch = 1;
                    }
                    else if (input == 115 && (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i]))
                    {
                        return abbruch = 1;
                    }
                    // sword in no wall
                    else if (input == 115 && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY - 1);
                            printf(" ");
                        }
                        return abbruch = 0;
                    }
                    else if (input == 100 && (starterArea[PlayerY][PlayerX + 5 + 1] == 1 || starterArea[PlayerY][PlayerX + 5 + 2] == 1))
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
            else if (input != 97 && lastNumberPressed == 2)
            {
                for (int i = 0; i <= 4; i++)
                {

                    if (input == 119 && (starterArea[PlayerY - 1][PlayerX + i] == 1))
                    {

                        return abbruch = 0;
                    }
                    // sword in no wall
                    else if (input == 119 && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if (input == 115 && (starterArea[PlayerY + 1][PlayerX + i] == 1))
                    {
                        return abbruch = 1;
                    }
                    else if (input == 115 && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if (input == 100 && (starterArea[PlayerY][PlayerX + 4 + i] >= 1 && starterArea[PlayerY][PlayerX + 4 + i] != 9 ))
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
            else if (input != 115 && lastNumberPressed == 3)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (input == 119 && (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9))
                    {
                        return abbruch = 1;
                    }
                    // sword in no wall
                    else if (input == 119 && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
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
                    else if (input == 97 && (starterArea[PlayerY][PlayerX - i] >= 1 || starterArea[PlayerY][PlayerX - i] != 9))
                    {

                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        sword = 1;
                        return abbruch = 0;
                    }
                    else if (input == 100 && (starterArea[PlayerY][PlayerX + 2 + i] >= 1 && starterArea[PlayerY][PlayerX + 2 + i] != 9))
                    {
                        return abbruch = 1;
                    }
                    else if (input == 100 && (starterArea[PlayerY][PlayerX - 1] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3 == 0]))
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
            else if (input != 100 && lastNumberPressed == 4)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (input == 119 && (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9))
                    {

                        return abbruch = 1;
                    }
                    // sword in no wall
                    else if (input == 119 && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        return abbruch = 0;
                    }
                    else if (input == 97 && (starterArea[PlayerY][PlayerX - 1 - i] >= 1 && starterArea[PlayerY][PlayerX - 1 - i] != 9))
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
                    else if (input == 115 && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9 || starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9))
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
                    else if (input == 115 && (starterArea[PlayerY + 1][PlayerX + i] == 1))
                    {

                        return abbruch = 1;
                    }
                }

                sword = 1;
            }
            else if (input == 119 && lastNumberPressed == 1)
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
            else if (input == 97 && (lastNumberPressed == 2))
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (input == 97 && (starterArea[PlayerY][PlayerX - 1 - i] >= 1 && starterArea[PlayerY][PlayerX - 1 - i] != 9))
                    {
                        sword = 2;
                        return abbruch = 0;
                    }
                }
                sword = 1;

            }
            else if (input == 115 && lastNumberPressed == 3)
            {
                for (int i = 0; i <= 4; i++)
                {
                    if (input == 115 && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                    {
                        sword = 2;
                        
                        return abbruch = 0;
                    }
                }
                sword = 1;
            }
            else if (input == 100 && (lastNumberPressed == 4))
            {
                for (int i = 0; i <= 7; i++)
                {
                    if (input == 100 && (starterArea[PlayerY][PlayerX + i] >= 1 && starterArea[PlayerY][PlayerX + i] != 9))
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
        else if (((starterArea[PlayerY - 1][PlayerX] >= 2 && starterArea[PlayerY - 1][PlayerX] != 9) || (starterArea[PlayerY - 1][PlayerX + 1] >= 2 && starterArea[PlayerY - 1][PlayerX + 1] != 9) || (starterArea[PlayerY - 1][PlayerX + 2] >= 2 && starterArea[PlayerY - 1][PlayerX + 2] != 9) || (starterArea[PlayerY - 1][PlayerX + 3] >= 2 && starterArea[PlayerY - 1][PlayerX + 3] != 9) || (starterArea[PlayerY - 1][PlayerX + 4] >= 2 && starterArea[PlayerY - 1][PlayerX + 4] != 9)) && input == 119)
        {

            return abbruch = 2;

        }
        //unten
        else if (((starterArea[PlayerY + 1][PlayerX] >= 2 && starterArea[PlayerY + 1][PlayerX] != 9) || (starterArea[PlayerY + 1][PlayerX + 1] >= 2 && starterArea[PlayerY + 1][PlayerX + 1] != 9) || (starterArea[PlayerY + 1][PlayerX + 2] >= 2 && starterArea[PlayerY + 1][PlayerX + 2] != 9) || (starterArea[PlayerY + 1][PlayerX + 3] >= 2 && starterArea[PlayerY + 1][PlayerX + 3] != 9) || (starterArea[PlayerY + 1][PlayerX + 4] >= 2 && starterArea[PlayerY + 1][PlayerX + 4] != 9)) && input == 115)
        {
            return abbruch = 2;

        }
        //rechts
        else if (((starterArea[PlayerY][PlayerX + 1] >= 2 && starterArea[PlayerY][PlayerX + 1] != 9) || (starterArea[PlayerY][PlayerX + 1 + 1] >= 2 && starterArea[PlayerY][PlayerX + 1 + 1] != 9) || (starterArea[PlayerY][PlayerX + 2 + 1] >= 2 && starterArea[PlayerY][PlayerX + 2 + 1] != 9) || (starterArea[PlayerY][PlayerX + 3 + 1] >= 2 && starterArea[PlayerY][PlayerX + 3 + 1] != 9) || (starterArea[PlayerY][PlayerX + 4 + 1] >= 2 && starterArea[PlayerY][PlayerX + 4 + 1] != 9)) && input == 100)
        {
            return abbruch = 2;

        }
        //links
        else if (((starterArea[PlayerY][PlayerX - 1] >= 2 && starterArea[PlayerY][PlayerX - 1] != 9) || (starterArea[PlayerY][PlayerX + 1 - 1] >= 2 && starterArea[PlayerY][PlayerX + 1 - 1] != 9) || (starterArea[PlayerY][PlayerX + 2 - 1] >= 2 && starterArea[PlayerY][PlayerX + 2 - 1] != 9) || (starterArea[PlayerY][PlayerX + 3 - 1] >= 2 && starterArea[PlayerY][PlayerX + 3 - 1] != 9) || (starterArea[PlayerY][PlayerX + 4 - 1] >= 2 && starterArea[PlayerY][PlayerX + 4 - 1] != 9)) && input == 97)
        {
            return abbruch = 2;

        }

        else
        {

            return abbruch = 0;
        }

    
}

void PlayersMovement(int& input, int abbruch, int& area, int& sword, int starterArea[][COLS], int& lastNumberPressed, int& swordAnimationPhase, int keys[], int& swordCooldown)
{
    int i;
    setlocale(LC_ALL, "");

    //ECheck(area, playerX, playerY, starterArea, sword, waitForECheck, lastNumberPressed);

    //Borders(Area, playerX, playerY, abbruch, starterArea);
    //fürs nach oben scrollen
    gotoxy(140, 1);
    printf(" ");
    //input = _getch();

    if (input == 119)
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
            printf("[°-°]");
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
            lastNumberPressed = 1;

            //playerY++;
        }
    }
    else if (input == 97)
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
            printf("[°-°]");
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
            lastNumberPressed = 2;

            //playerX += 2;

        }
    }
    else if (input == 115)
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
            printf("[°-°]");
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
            lastNumberPressed = 3;

            // playerY--;

        }
    }
    else if (input == 100)
    {

        //playerX += 2;
        Borders(area, abbruch, starterArea, input, sword, lastNumberPressed);

        if (abbruch == 0)
        {
            PlayerX += 2;
            for (int i = 0; i < 2; i++)
            {
                if (starterArea[PlayerY][PlayerX + 4 + 1] == 0 || starterArea[PlayerY][PlayerX + 4 + 2] == 0)
                {
                    starterArea[PlayerY][PlayerX + 3 + i] = 9;
                    starterArea[PlayerY][PlayerX - i - 1] = 0;
                }
            }


            gotoxy(PlayerX, PlayerY);
            printf("[°-°]");
            /*
            gotoxy(playerX - 2, playerY);
            printf("%d%d%d%d%d%d%d%d%d",starterArea[playerY][playerX - 2], starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
            */

            Sword(sword, lastNumberPressed, input, starterArea);
            lastNumberPressed = 4;

            gotoxy(PlayerX - 2, PlayerY);
            printf("  ");
        }
        else
        {
            lastNumberPressed = 4;

            //playerX -= 2;

        }
    }
    else if (input == 101)
    {
        if (area == 1)
        {
            //für 2
            if ((starterArea[PlayerY][PlayerX] == 2 || starterArea[PlayerY][PlayerX + 1] == 2 || starterArea[PlayerY][PlayerX + 2] == 2 || starterArea[PlayerY][PlayerX + 3] == 2 || starterArea[PlayerY][PlayerX + 4] == 2) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 2 || starterArea[PlayerY - 1][PlayerX + 1] == 2 || starterArea[PlayerY - 1][PlayerX + 2] == 2 || starterArea[PlayerY - 1][PlayerX + 3] == 2 || starterArea[PlayerY - 1][PlayerX + 4] == 2) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 2 || starterArea[PlayerY + 1][PlayerX + 1] == 2 || starterArea[PlayerY + 1][PlayerX + 2] == 2 || starterArea[PlayerY + 1][PlayerX + 3] == 2 || starterArea[PlayerY + 1][PlayerX + 4] == 2) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 2 || starterArea[PlayerY][PlayerX + 1 + 1] == 2 || starterArea[PlayerY][PlayerX + 2 + 1] == 2 || starterArea[PlayerY][PlayerX + 3 + 1] == 2 || starterArea[PlayerY][PlayerX + 4 + 1] == 2) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 2 || starterArea[PlayerY][PlayerX + 1 - 1] == 2 || starterArea[PlayerY][PlayerX + 2 - 1] == 2 || starterArea[PlayerY][PlayerX + 3 - 1] == 2 || starterArea[PlayerY][PlayerX + 4 - 1] == 2))
            {
                
                    gotoxy(5, 46);
                    printf("                     ");
                    gotoxy(5, 46);
                    printf("stuff that you need for some science sht");
                    Sleep(2000);
                    gotoxy(5, 46);
                    printf("                                          ");
                    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));


                
            }

            //für 3
            else if ((starterArea[PlayerY][PlayerX] == 3 || starterArea[PlayerY][PlayerX + 1] == 3 || starterArea[PlayerY][PlayerX + 2] == 3 || starterArea[PlayerY][PlayerX + 3] == 3 || starterArea[PlayerY][PlayerX + 4] == 3) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 3 || starterArea[PlayerY - 1][PlayerX + 1] == 3 || starterArea[PlayerY - 1][PlayerX + 2] == 3 || starterArea[PlayerY - 1][PlayerX + 3] == 3 || starterArea[PlayerY - 1][PlayerX + 4] == 3) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 3 || starterArea[PlayerY + 1][PlayerX + 1] == 3 || starterArea[PlayerY + 1][PlayerX + 2] == 3 || starterArea[PlayerY + 1][PlayerX + 3] == 3 || starterArea[PlayerY + 1][PlayerX + 4] == 3) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 3 || starterArea[PlayerY][PlayerX + 1 + 1] == 3 || starterArea[PlayerY][PlayerX + 2 + 1] == 3 || starterArea[PlayerY][PlayerX + 3 + 1] == 3 || starterArea[PlayerY][PlayerX + 4 + 1] == 3) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 3 || starterArea[PlayerY][PlayerX + 1 - 1] == 3 || starterArea[PlayerY][PlayerX + 2 - 1] == 3 || starterArea[PlayerY][PlayerX + 3 - 1] == 3 || starterArea[PlayerY][PlayerX + 4 - 1] == 3))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("A Laptop...");
                Sleep(1000);
                gotoxy(17, 46);
                printf("but what is the passcode");
                Sleep(2000);
                gotoxy(5, 46);
                printf("                                               ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

            }

            //für 4
            else if ((starterArea[PlayerY][PlayerX] == 4 || starterArea[PlayerY][PlayerX + 1] == 4 || starterArea[PlayerY][PlayerX + 2] == 4 || starterArea[PlayerY][PlayerX + 3] == 4 || starterArea[PlayerY][PlayerX + 4] == 4) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 4 || starterArea[PlayerY - 1][PlayerX + 1] == 4 || starterArea[PlayerY - 1][PlayerX + 2] == 4 || starterArea[PlayerY - 1][PlayerX + 3] == 4 || starterArea[PlayerY - 1][PlayerX + 4] == 4) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 4 || starterArea[PlayerY + 1][PlayerX + 1] == 4 || starterArea[PlayerY + 1][PlayerX + 2] == 4 || starterArea[PlayerY + 1][PlayerX + 3] == 4 || starterArea[PlayerY + 1][PlayerX + 4] == 4) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 4 || starterArea[PlayerY][PlayerX + 1 + 1] == 4 || starterArea[PlayerY][PlayerX + 2 + 1] == 4 || starterArea[PlayerY][PlayerX + 3 + 1] == 4 || starterArea[PlayerY][PlayerX + 4 + 1] == 4) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 4 || starterArea[PlayerY][PlayerX + 1 - 1] == 4 || starterArea[PlayerY][PlayerX + 2 - 1] == 4 || starterArea[PlayerY][PlayerX + 3 - 1] == 4 || starterArea[PlayerY][PlayerX + 4 - 1] == 4))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("*A paper with lots of science, that you are to dumb for!*");
                Sleep(3000);
                gotoxy(5, 46);
                printf("                                                          ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

            }
            //für 5
            else if ((starterArea[PlayerY][PlayerX] == 5 || starterArea[PlayerY][PlayerX + 1] == 5 || starterArea[PlayerY][PlayerX + 2] == 5 || starterArea[PlayerY][PlayerX + 3] == 5 || starterArea[PlayerY][PlayerX + 4] == 5) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 5 || starterArea[PlayerY - 1][PlayerX + 1] == 5 || starterArea[PlayerY - 1][PlayerX + 2] == 5 || starterArea[PlayerY - 1][PlayerX + 3] == 5 || starterArea[PlayerY - 1][PlayerX + 4] == 5) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 5 || starterArea[PlayerY + 1][PlayerX + 1] == 5 || starterArea[PlayerY + 1][PlayerX + 2] == 5 || starterArea[PlayerY + 1][PlayerX + 3] == 5 || starterArea[PlayerY + 1][PlayerX + 4] == 5) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 5 || starterArea[PlayerY][PlayerX + 1 + 1] == 5 || starterArea[PlayerY][PlayerX + 2 + 1] == 5 || starterArea[PlayerY][PlayerX + 3 + 1] == 5 || starterArea[PlayerY][PlayerX + 4 + 1] == 5) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 5 || starterArea[PlayerY][PlayerX + 1 - 1] == 5 || starterArea[PlayerY][PlayerX + 2 - 1] == 5 || starterArea[PlayerY][PlayerX + 3 - 1] == 5 || starterArea[PlayerY][PlayerX + 4 - 1] == 5))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("*A microscope with blood on it.*");
                Sleep(2000);
                gotoxy(5, 46);
                printf("                                ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

            }
            //für 6 tools
            else if ((starterArea[PlayerY][PlayerX] == 6 || starterArea[PlayerY][PlayerX + 1] == 6 || starterArea[PlayerY][PlayerX + 2] == 6 || starterArea[PlayerY][PlayerX + 3] == 6 || starterArea[PlayerY][PlayerX + 4] == 6) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 6 || starterArea[PlayerY - 1][PlayerX + 1] == 6 || starterArea[PlayerY - 1][PlayerX + 2] == 6 || starterArea[PlayerY - 1][PlayerX + 3] == 6 || starterArea[PlayerY - 1][PlayerX + 4] == 6) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 6 || starterArea[PlayerY + 1][PlayerX + 1] == 6 || starterArea[PlayerY + 1][PlayerX + 2] == 6 || starterArea[PlayerY + 1][PlayerX + 3] == 6 || starterArea[PlayerY + 1][PlayerX + 4] == 6) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 4 + 1] == 6) || starterArea[PlayerY][PlayerX + 4 + 2] == 6 || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 6 || starterArea[PlayerY][PlayerX - 2] == 6))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("*A couple of tools* and no you cant pick them up because im to lazy");
                Sleep(5000);
                gotoxy(5, 46);
                printf("                                                                   ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

            }
            // für 7
            else if ((starterArea[PlayerY][PlayerX] == 7 || starterArea[PlayerY][PlayerX + 1] == 7 || starterArea[PlayerY][PlayerX + 2] == 7 || starterArea[PlayerY][PlayerX + 3] == 7 || starterArea[PlayerY][PlayerX + 4] == 7) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 7 || starterArea[PlayerY - 1][PlayerX + 1] == 7 || starterArea[PlayerY - 1][PlayerX + 2] == 7 || starterArea[PlayerY - 1][PlayerX + 3] == 7 || starterArea[PlayerY - 1][PlayerX + 4] == 7) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 7 || starterArea[PlayerY + 1][PlayerX + 1] == 7 || starterArea[PlayerY + 1][PlayerX + 2] == 7 || starterArea[PlayerY + 1][PlayerX + 3] == 7 || starterArea[PlayerY + 1][PlayerX + 4] == 7) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 7 || starterArea[PlayerY][PlayerX + 1 + 1] == 7 || starterArea[PlayerY][PlayerX + 2 + 1] == 7 || starterArea[PlayerY][PlayerX + 3 + 1] == 7 || starterArea[PlayerY][PlayerX + 4 + 1] == 7) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 7 || starterArea[PlayerY][PlayerX + 1 - 1] == 7 || starterArea[PlayerY][PlayerX + 2 - 1] == 7 || starterArea[PlayerY][PlayerX + 3 - 1] == 7 || starterArea[PlayerY][PlayerX + 4 - 1] == 7))
            {
               
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("*the door opens*");
                Sleep(1000);
                gotoxy(5, 46);
                printf("                    ");

                PlayerX = 22;
                PlayerY = 10;
                area = 2;
                ChangeArea(area, starterArea);

                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                

            }

            //für 8
            else if ((starterArea[PlayerY][PlayerX] == 8 || starterArea[PlayerY][PlayerX + 1] == 8 || starterArea[PlayerY][PlayerX + 2] == 8 || starterArea[PlayerY][PlayerX + 3] == 8 || starterArea[PlayerY][PlayerX + 4] == 8) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 8 || starterArea[PlayerY - 1][PlayerX + 1] == 8 || starterArea[PlayerY - 1][PlayerX + 2] == 8 || starterArea[PlayerY - 1][PlayerX + 3] == 8 || starterArea[PlayerY - 1][PlayerX + 4] == 8) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 8 || starterArea[PlayerY + 1][PlayerX + 1] == 8 || starterArea[PlayerY + 1][PlayerX + 2] == 8 || starterArea[PlayerY + 1][PlayerX + 3] == 8 || starterArea[PlayerY + 1][PlayerX + 4] == 8) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 8 || starterArea[PlayerY][PlayerX + 1 + 1] == 8 || starterArea[PlayerY][PlayerX + 2 + 1] == 8 || starterArea[PlayerY][PlayerX + 3 + 1] == 8 || starterArea[PlayerY][PlayerX + 4 + 1] == 8) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 8 || starterArea[PlayerY][PlayerX + 1 - 1] == 8 || starterArea[PlayerY][PlayerX + 2 - 1] == 8 || starterArea[PlayerY][PlayerX + 3 - 1] == 8 || starterArea[PlayerY][PlayerX + 4 - 1] == 8))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("A sickbed");
                Sleep(1000);
                gotoxy(5, 46);
                printf("         ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
            //für 10 standard Zombie(kein loot)
            else if ((starterArea[PlayerY][PlayerX] == 10 || starterArea[PlayerY][PlayerX + 1] == 10 || starterArea[PlayerY][PlayerX + 2] == 10 || starterArea[PlayerY][PlayerX + 3] == 10 || starterArea[PlayerY][PlayerX + 4] == 10) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 10 || starterArea[PlayerY - 1][PlayerX + 1] == 10 || starterArea[PlayerY - 1][PlayerX + 2] == 10 || starterArea[PlayerY - 1][PlayerX + 3] == 10 || starterArea[PlayerY - 1][PlayerX + 4] == 10) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 10 || starterArea[PlayerY + 1][PlayerX + 1] == 10 || starterArea[PlayerY + 1][PlayerX + 2] == 10 || starterArea[PlayerY + 1][PlayerX + 3] == 10 || starterArea[PlayerY + 1][PlayerX + 4] == 10) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 10 || starterArea[PlayerY][PlayerX + 1 + 1] == 10 || starterArea[PlayerY][PlayerX + 2 + 1] == 10 || starterArea[PlayerY][PlayerX + 3 + 1] == 10 || starterArea[PlayerY][PlayerX + 4 + 1] == 10) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 10 || starterArea[PlayerY][PlayerX + 1 - 1] == 10 || starterArea[PlayerY][PlayerX + 2 - 1] == 10 || starterArea[PlayerY][PlayerX + 3 - 1] == 10 || starterArea[PlayerY][PlayerX + 4 - 1] == 10))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("Hes a btch with no loot");
                Sleep(2000);
                gotoxy(5, 46);
                printf("                       ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
            //für 11 (some random stuff)
            else if ((starterArea[PlayerY][PlayerX] == 11 || starterArea[PlayerY][PlayerX + 1] == 11 || starterArea[PlayerY][PlayerX + 2] == 11 || starterArea[PlayerY][PlayerX + 3] == 11 || starterArea[PlayerY][PlayerX + 4] == 11) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 11 || starterArea[PlayerY - 1][PlayerX + 1] == 11 || starterArea[PlayerY - 1][PlayerX + 2] == 11 || starterArea[PlayerY - 1][PlayerX + 3] == 11 || starterArea[PlayerY - 1][PlayerX + 4] == 11) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 11 || starterArea[PlayerY + 1][PlayerX + 1] == 11 || starterArea[PlayerY + 1][PlayerX + 2] == 11 || starterArea[PlayerY + 1][PlayerX + 3] == 11 || starterArea[PlayerY + 1][PlayerX + 4] == 11) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 11 || starterArea[PlayerY][PlayerX + 1 + 1] == 11 || starterArea[PlayerY][PlayerX + 2 + 1] == 11 || starterArea[PlayerY][PlayerX + 3 + 1] == 11 || starterArea[PlayerY][PlayerX + 4 + 1] == 11) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 11 || starterArea[PlayerY][PlayerX + 1 - 1] == 11 || starterArea[PlayerY][PlayerX + 2 - 1] == 11 || starterArea[PlayerY][PlayerX + 3 - 1] == 11 || starterArea[PlayerY][PlayerX + 4 - 1] == 11))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("Im to stupid to think of other stuff");
                Sleep(4000);
                gotoxy(5, 46);
                printf("                                                 ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }    
            //für 20 DoctorsZombie
            else if ((starterArea[PlayerY][PlayerX] == 20 || starterArea[PlayerY][PlayerX + 1] == 20 || starterArea[PlayerY][PlayerX + 2] == 20 || starterArea[PlayerY][PlayerX + 3] == 20 || starterArea[PlayerY][PlayerX + 4] == 20) ||/*für oben*/ (starterArea[PlayerY - 1][PlayerX] == 20 || starterArea[PlayerY - 1][PlayerX + 1] == 20 || starterArea[PlayerY - 1][PlayerX + 2] == 20 || starterArea[PlayerY - 1][PlayerX + 3] == 20 || starterArea[PlayerY - 1][PlayerX + 4] == 20) || /*für unten*/ (starterArea[PlayerY + 1][PlayerX] == 20 || starterArea[PlayerY + 1][PlayerX + 1] == 20 || starterArea[PlayerY + 1][PlayerX + 2] == 20 || starterArea[PlayerY + 1][PlayerX + 3] == 20 || starterArea[PlayerY + 1][PlayerX + 4] == 20) || /*für rechts*/ (starterArea[PlayerY][PlayerX + 1] == 20 || starterArea[PlayerY][PlayerX + 1 + 1] == 20 || starterArea[PlayerY][PlayerX + 2 + 1] == 20 || starterArea[PlayerY][PlayerX + 3 + 1] == 20 || starterArea[PlayerY][PlayerX + 4 + 1] == 20) || /*für links*/ (starterArea[PlayerY][PlayerX - 1] == 20 || starterArea[PlayerY][PlayerX + 1 - 1] == 20 || starterArea[PlayerY][PlayerX + 2 - 1] == 20 || starterArea[PlayerY][PlayerX + 3 - 1] == 20 || starterArea[PlayerY][PlayerX + 4 - 1] == 20))
            {
                gotoxy(5, 46);
                printf("                     ");
                gotoxy(5, 46);
                printf("He seemed to be a scientist...");
                Sleep(2000);
                if (keys[0] == 0)
                {
                    printf(" *you acquired a key*");
                    Sleep(2000);
                    keys[0] = 1;
                }
                gotoxy(5, 46);
                printf("                                                      ");
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
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