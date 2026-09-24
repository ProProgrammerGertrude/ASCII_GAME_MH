#pragma once
#include "HTL_Konsole.h"
#include "Map_Array.h"
#include "GameFunctions.h"

class Player;

class Zombie
{
public:
    int Zombielife;
    int ZombieArmor;
    int Zombiedamage;
    int ZombieStartSpeed;
    int Zombiespeed;
    int ZombieposX;
    int ZombieposY;
    int waitForNextZombieMove;
    int ZombieSize;
    int ZombieDeathValue;
    int ZombieArea;
    bool ZombieXMove;
    int BossOrPawn;
    // only needed for the zombieBoss, but closeRangeMovement needs the variable
    bool invisible = false;
    // 0 is the player after that its the bodys count
    int target = 0;

    // for the holos
    int SwitchCount;
    int SwitchMood;
    // 0 for player 1 for random walk enabled
    bool RandomWalk = 0;

    string bodyToRight[7];
    string bodyToLeft[7];
    string outputRightBody;
    string outputLeftBody;


    Pair src;

    // Constructor to initialize values
    Zombie(int posX, int posY, int lifes, int armor, int damage, int startspeed, int speed, int waitfornextzombiemove, int size, int zombieDeathValue, int zombieAreaSpawn, int bossOrPawn, int switchMood, int switchCount);
        
    void tracePath(cell cellDetails[][COLS], int row, int col, Player& player, Pair dest, Zombie& zombie);
    void CloseRangeMovement(Pair src, Pair dest, Player& player, Zombie& zombie);
}; 
