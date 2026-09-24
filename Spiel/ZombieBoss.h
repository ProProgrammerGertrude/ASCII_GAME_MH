#pragma once
#include "Zombie.h"
#include "Deadbody.h"

class DeadBody;

class ZombieBoss : public Zombie
{
public:
    int phase = 2;
    int abilityTimer = 30;

    int zombieAbility = 0;

    ZombieBoss::ZombieBoss(int posX, int posY, int lives, int armor, int damage, int startspeed, int speed, int waitfornextzombiemove, int size, int zombieDeathValue, int zombieAreaSpawn, bool bossOrPawn, int switchMood, int switchCount )
        : Zombie(posX, posY, lives, armor, damage, startspeed, speed, waitfornextzombiemove, size, zombieDeathValue, zombieAreaSpawn, bossOrPawn, switchMood, switchCount)
    {
    }
    void CloseRangeMovement(Pair src, Pair dest, Player& player, ZombieBoss& zombieBoss, DeadBody deadBodies[]);
};