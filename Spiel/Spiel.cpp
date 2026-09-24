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
#include "GameFunctions.h"
#include "Zombie.h"
#include "ZombieBoss.h"
#include "Sword.h"
#include "MapCreation.h"
#include "DeadBody.h"
#include "Player.h"
#include "ZombieBossHolo.h"

using namespace std;

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
int PlayerX = 10;//62 //42 //115 // 55 // 10
int PlayerY = 29;//17 // 12 //16 // 29 // 29

// posX, posY, size, normalPart, redPart, area, Value
DeadBody deadBodies[HowManyDeadBodies] =
{

    DeadBody(8, 10, 8,"[X-X\033[0;31m\\~~~\033[0m", 2, 70),
    DeadBody(150, 10, 5,"[X-X\033[0;31m]\033[0m", 2, 71),
    DeadBody(126, 4, 5, "[X-X\033[0;31m]\033[0m", 2, 72),
    DeadBody(21, 29, 5, "[xO\033[0;31mx]\033[0m", 6, 70),
    DeadBody(51, 5, 6, "[\033[0;31mQ\033[0m-Q\033[0;31m~~\033[0m", 6,71),
    DeadBody(16, 14, 4, "\033[0;31m/o\033[0mX]", 7, 70),
    DeadBody(93, 18, 4, "[Xo\033[0;31m~\033[0m", 7, 71),
    DeadBody(101, 21, 4, "\033[0;31m~~\033[0mX]", 7, 72),
    DeadBody(26, 28, 4, "\033[0;31m[\033[0mx-\033[0;31m\\\033[0m", 7, 73)
};


void ECheck(Player& player, int input);
void WaitingTime(Player& player, Zombie zombies[], ZombieBoss& zombieBoss, DeadBody deadBodies[], ZombieBossHolo zombieBossHolo[]);
void EntityMoves(Zombie zombies[], Player& player, ZombieBoss& zombieBoss, DeadBody deadBodies[], ZombieBossHolo zombieBossHolo[]);


int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int input = 0;
    int abbruch = 0;
    

    cursoroff();

    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    Sleep(500);

    srand((unsigned)time(NULL));
    
    gotoxy(PlayerX, PlayerY);
    printf("[\xC2\xB0-\xC2\xB0]");

    // X, Y, life, armor, damage, startspeed, speed, waitingtime, size, zombieDeathValue, area,  (0 is pawn, 1 Boss, 2 Holo), switchMood, switchCount
    Zombie zombies[HowManyZombiesExist] = 
    {
         Zombie( 54, 27, 3, 1, 2, 20, 20,  7, 7, 20, 1, 0, 0, 0), // zombie0 //Doctor
         Zombie(120, 29, 3, 1, 2, 15, 15,  5, 7, 10, 1, 0, 0, 0), // zombie1
         Zombie(125,  7, 1, 1, 2, 10, 10,  0, 7, 10, 2, 0, 0, 0), // zombie2 (Hallway)
         Zombie(  2,  4, 2, 1, 2, 20, 20,  2, 7, 10, 3, 0, 0, 0), // zombie3 (storage)
         Zombie( 55, 15, 2, 1, 2, 20, 20,  5, 7, 10, 3, 0, 0, 0), // zombie4 (storage)
         Zombie( 59,  7, 2, 1, 2, 15, 15,  0, 7, 10, 6, 0, 0, 0), // zombie5 (locker)
         Zombie( 82, 28, 1, 1, 2, 50, 50, 30, 7, 10, 6, 0, 0, 0), // zombie6 (locker)
         Zombie( 50,  4, 5, 1, 2, 30, 30, 20, 7, 11, 6, 0, 0, 0)  // zombie7 (locker)
    };

    ZombieBoss zombieBoss(27, 27, 10, 1, 2, 15, 15, 0, 7, 10, 7, 1, 0, 0);

    ZombieBossHolo zombieBossHolo[HowManyZombieBossHolos] =
    {
        ZombieBossHolo( 40,  27, 1, 1, 2, 15, 15,  3, 7, 0, 7, 2, 100, 40),
        ZombieBossHolo(100,  30, 1, 1, 2, 15, 15,  7, 7, 0, 7, 2, 350, 150),
        ZombieBossHolo( 15,  18, 1, 1, 2, 15, 15, 10, 7, 0, 7, 2, 300, 57),
        ZombieBossHolo( 60,   5, 1, 1, 2, 15, 15, 14, 7, 0, 7, 2, 500, 100),
    };

    Player player;

    player.area = 7;
    
    if (player.area == 1)
    {
        PlayerX = 62;
        PlayerY = 17;
    }
    else if (player.area == 2)
    {
        PlayerX = 42;
        PlayerY = 12;
    }
    else if (player.area == 3)
    {
        PlayerX = 115;
        PlayerY = 16;
    }
    else if (player.area == 4)
    {
        PlayerX = 55;
        PlayerY = 29;
    }
    else if (player.area == 5)
    {
        PlayerX = 10;
        PlayerY = 29;
    }
    else if (player.area == 6)
    {
        PlayerX = 47;
        PlayerY = 29;
    }
    else if (player.area == 7)
    {
        PlayerX = 92;
        PlayerY = 3;
    }

    ChangeArea(player, zombies, deadBodies);
    cursoroff();

    while (player.win == 0)
    {
        EntityMoves(zombies, player, zombieBoss, deadBodies, zombieBossHolo);
        
        if (_kbhit()) {
            if (player.waitForNextMove == 0 && player.swordAnimationPhase == -1)
            {
                input = _getch();
                player.PlayersMovement(input, abbruch, zombies, deadBodies);
                ECheck(player, input);
                player.waitForNextMove = 6;
            }
        }

        AttackCheck(zombies, player, zombieBoss, zombieBossHolo);


        Sleep(1);
        WaitingTime(player, zombies, zombieBoss, deadBodies, zombieBossHolo);
        player.win = 0;

    }
    // game lost/won
    printf("You Lose");
    Sleep(5000);
}
void RandomPlacement(int modX, int plusX, int modY, int plusY, int& randX, int& randY, int size, int lengthFromPlayer)
{
    randX = rand() % modX + plusX;
    randY = rand() % modY + plusY;
    while (true)
    {
        bool empty = true;
        for (int j = 0; j < size; j++)
        {
            if (starterArea[randY][randX + j] != 0)
            {
                empty = false;
            }
        }

        if (!empty)
        {
            randX = rand() % modX + plusX;
            randY = rand() % modY + plusY;
            while (abs(randX - PlayerX) + abs(randY - PlayerY) < lengthFromPlayer)
            {
                randX = rand() % modX + plusX;
                randY = rand() % modY + plusY;
            }
        }
        else
        {
            break;
        }
    }
}

bool NotOnDeadBody(int posX, int posY)
{
    return !(starterArea[posY][posX] >= 70 && starterArea[posY][posX] < 80);
}

void EntityMoves(Zombie zombies[], Player& player, ZombieBoss& zombieBoss, DeadBody deadBodies[], ZombieBossHolo zombieBossHolo[])
{
    for (int i = 0; i < HowManyZombiesExist; i++)
    {
        if (player.area == 7)
        {
            if (zombieBoss.waitForNextZombieMove == 0)
            {
                Pair dest = make_pair(PlayerY, PlayerX);
                if (zombieBoss.target != 0)
                    dest = make_pair(deadBodies[zombieBoss.target].posY, deadBodies[zombieBoss.target].posX);

                zombieBoss.src = make_pair(zombieBoss.ZombieposY, zombieBoss.ZombieposX);

                zombieBoss.CloseRangeMovement(zombieBoss.src, dest, player, zombieBoss, deadBodies);
            }
        }

        if (zombies[i].ZombieArea == player.area)
        {
            Pair dest = make_pair(PlayerY, PlayerX);

            if (zombies[i].waitForNextZombieMove == 0)
            {
                zombies[i].src = make_pair(zombies[i].ZombieposY, zombies[i].ZombieposX);

                if (zombies[i].Zombielife > 0)
                {
                    zombies[i].CloseRangeMovement(zombies[i].src, dest, player, zombies[i]);
                }
            }
        }
    }



    // for BodieMoves
    for (int i = 0; i < HowManyDeadBodies; i++)
    {
        if (deadBodies[i].area == player.area)
        {
            if (deadBodies[i].moving)
            {
                if (deadBodies[i].waitForNextBodyMove == 0)
                {
                    deadBodies[i].MovingBody(deadBodies[i], zombies, player, zombieBoss);
                }
            }
        }
    }

    // zombieBossHolo
    if (player.area == zombieBoss.ZombieArea && zombieBoss.phase == 2 && zombieBoss.Zombielife > 0)
    {

        for (int i = 0; i < HowManyZombieBossHolos; i++)
        {
            if (zombieBossHolo[i].SwitchCount == 0)
            {
                zombieBossHolo[i].SwitchCount = zombieBossHolo[i].SwitchMood;
                zombieBossHolo[i].RandomWalk = rand() % 4;
                zombieBossHolo[i].RandomWalk = !zombieBossHolo[i].RandomWalk;

                if(zombieBossHolo[i].RandomWalk)
                    RandomPlacement(98, 6, 33, 3, zombieBossHolo[i].targetXifNotPlayer, zombieBossHolo[i].targetYifNotPlayer, zombieBossHolo[i].ZombieSize, 5);

            }

            if (zombieBossHolo[i].waitForNextZombieMove == 0)
            {
                Pair dest = make_pair(PlayerY, PlayerX);

                if (zombieBossHolo[i].RandomWalk)
                {
                    dest = make_pair(zombieBossHolo[i].targetYifNotPlayer, zombieBossHolo[i].targetXifNotPlayer);
                }
                
                zombieBossHolo[i].src = make_pair(zombieBossHolo[i].ZombieposY, zombieBossHolo[i].ZombieposX);
                zombieBossHolo[i].CloseRangeMovement(zombieBossHolo[i].src, dest, player, zombieBossHolo[i]);
            }
        }
    }
}

bool VisionCheck(int starterX, int starterY, int targetX, int targetY, int starterArrayValue, int targetArrayValue)
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
        if (starterArea[y][x] != 0 && starterArea[y][x] != starterArrayValue && starterArea[y][x] != targetArrayValue && NotOnDeadBody(x, y))
        {
            return true;
        }
    }
    return false;
}

void WaitingTime(Player& player, Zombie zombies[], ZombieBoss& zombieBoss, DeadBody deadBodies[], ZombieBossHolo zombieBossHolo[])
{

    //deadBodies
    for (int i = 0; i < HowManyDeadBodies; i++)
    {
        if (deadBodies[i].waitForNextBodyMove > 0)
            deadBodies[i].waitForNextBodyMove--;
    }




    for (int i = 0; i < HowManyZombiesExist; i++)
    {
        if (zombies[i].waitForNextZombieMove > 0)
        {
            zombies[i].waitForNextZombieMove--;
        } 
    }

    // zombieBoss
    if (zombieBoss.waitForNextZombieMove > 0)
    {
        zombieBoss.waitForNextZombieMove--;
    }

    if (zombieBoss.abilityTimer > 0)
    {
        zombieBoss.abilityTimer--;
    }

    // zombieBossHolo
    for (int i = 0; i < HowManyZombieBossHolos; i++)
    {
        if (zombieBossHolo[i].waitForNextZombieMove > 0)
        {
            zombieBossHolo[i].waitForNextZombieMove--;
        }

        if (zombieBossHolo[i].SwitchCount > 0)
        {
            zombieBossHolo[i].SwitchCount--;
        }
    }

    

    if (player.waitForNextMove > 0)
    {
        player.waitForNextMove--;
    }

    //Sword
    if (player.waitForSwordAnimation > 0)
    {
        player.waitForSwordAnimation++;
    }
    if (player.swordCooldown > 0)
        player.swordCooldown--;

    if (player.waitForSwordAnimation >= 4 && (player.lastNumberPressed == 1 || player.lastNumberPressed == 3))
        player.waitForSwordAnimation = 0;
    if (player.waitForSwordAnimation >= 6 && (player.lastNumberPressed == 2 || player.lastNumberPressed == 4))
        player.waitForSwordAnimation = 0;
}

void ECheck(Player& player, int input)
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


