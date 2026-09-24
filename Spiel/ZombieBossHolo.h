#pragma once
#include "Zombie.h"
#include "Deadbody.h"

class DeadBody;

class ZombieBossHolo : public Zombie
{
public:

    int targetXifNotPlayer = 0;
    int targetYifNotPlayer = 0;

    ZombieBossHolo::ZombieBossHolo(int posX, int posY, int lives, int armor, int damage, int startspeed, int speed, int waitfornextzombiemove, int size, int zombieDeathValue, int zombieAreaSpawn, int bossOrPawn, int switchMood, int switchCount)
        : Zombie(posX, posY, lives, armor, damage, startspeed, speed, waitfornextzombiemove, size, zombieDeathValue, zombieAreaSpawn, bossOrPawn, switchMood, switchCount)
    {
    }

    void CloseRangeMovement(Pair src, Pair dest, Player& player, ZombieBossHolo& zombieBossHolo);

};