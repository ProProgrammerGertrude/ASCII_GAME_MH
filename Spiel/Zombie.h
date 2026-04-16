#include "HTL_Konsole.h"
#include "Map_Array.h"
#include "GameFunctions.h"



class Zombie
{
public:
    int Zombielives;
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

    Pair src;

    // Constructor to initialize values
    Zombie(int posX, int posY, int lives, int armor, int damage, int startspeed, int speed, int waitfornextzombiemove, int size, int zombieDeathValue, int zombieAreaSpawn);
        
    void CloseRangeMovement(char starterArea[][COLS], Pair src, Pair dest, int& waitForNextZombieMove, int& win, bool& ZombieXMove, int ZombieDeathValue);
}; 
