#include <stdio.h>
#include <math.h>
#include "Gamefunctions.h"
#include "ZombieBoss.h"
#include "Zombie.h"
#include "Player.h"


//void ZombieBoss::CloseRangeMovement(Pair src, Pair dest, int& waitForNextZombieMove, int& win, bool& ZombieXMove, int ZombieDeathValue, Player& player, int& phase, int& abilityTimer, int& target)
void ZombieBoss::CloseRangeMovement(Pair src, Pair dest, Player& player, ZombieBoss& zombieBoss, DeadBody deadBodies[])
{
    // Boss-spezifische Logik zuerst
    // != 3 because it wont have a abilityTimer if he chases a deadBody
    if (zombieBoss.abilityTimer == 0 && zombieBoss.zombieAbility != 3)
    {
        if (zombieBoss.zombieAbility == 0)
        {
            int abilityNumber = 0;
            // give him a ability
            if (phase == 1)
                abilityNumber = rand() % 3 + 1;
            else
                abilityNumber = rand() % 6 + 1;
            //ability 1 speed
            //abilityNumber = 2;

            zombieBoss.zombieAbility = abilityNumber;

            if (zombieBoss.zombieAbility == 1)
            {
                zombieBoss.ZombieStartSpeed /= 2;
                zombieBoss.abilityTimer = 300;
            }
            else if (zombieBoss.zombieAbility == 2)
            {
                zombieBoss.invisible = true;
                zombieBoss.abilityTimer = 300;
            }
            else if (zombieBoss.zombieAbility == 3)
            {
                int closestBody = 5;
                int minMoves = INT_MAX;

                for (int i = 5; i < 9; i++)
                {
                    if (minMoves > abs(zombieBoss.ZombieposX - deadBodies[i].posX) + abs(zombieBoss.ZombieposY - deadBodies[i].posY))
                    {
                        minMoves = abs(zombieBoss.ZombieposX - deadBodies[i].posX) + abs(zombieBoss.ZombieposY - deadBodies[i].posY);
                        closestBody = i;
                    }
                }
                // + 5 so that if its close from distance the boss goes to the body
                if ((abs(zombieBoss.ZombieposX - PlayerX) + abs(zombieBoss.ZombieposY - PlayerY) + 10) > minMoves)
                {
                    zombieBoss.target = closestBody;
                }
                else
                {
                    zombieBoss.abilityTimer = 300;
                }
            }
            else
            {

                // only in phase 2 holos switch
                zombieBoss.abilityTimer = 200;
            }
        }
        else
        {
            // remove ability
            if (zombieBoss.zombieAbility == 1)
                 zombieBoss.ZombieStartSpeed *= 2;
            else if (zombieBoss.zombieAbility == 2)
                zombieBoss.invisible = false;
            else if (zombieBoss.zombieAbility == 3)
                zombieBoss.target = 0;

            zombieBoss.zombieAbility = 0;
            zombieBoss.abilityTimer = 500;
        }


    }
    Zombie::CloseRangeMovement(src, dest, player, zombieBoss);


    for (int c = 0; c < zombieBoss.ZombieSize; c++)
    {
        for (int g = 0; g <= PlayerSize; g++)
        {
            if (isDestination(src.first, src.second + c, dest.first, dest.second + g))
            {
                if (zombieBoss.target == 0)
                    player.win = 2;
                else
                {
                    deadBodies[zombieBoss.target].moving = true;
                    if (abs(PlayerX - deadBodies[zombieBoss.target].posX) > abs(PlayerY - deadBodies[zombieBoss.target].posY))
                    {
                        // X is further away than Y
                        deadBodies[zombieBoss.target].movingX = 1;
                        deadBodies[zombieBoss.target].movingY = (float)abs(PlayerY - deadBodies[zombieBoss.target].posY) / abs(PlayerX - deadBodies[zombieBoss.target].posX);
                        
                        if (deadBodies[zombieBoss.target].posX > PlayerX)
                            deadBodies[zombieBoss.target].movingX *= -1;
                        if (deadBodies[zombieBoss.target].posY > PlayerY)
                            deadBodies[zombieBoss.target].movingY *= -1;
                    }
                    else
                    {
                        deadBodies[zombieBoss.target].movingY = 1;
                        deadBodies[zombieBoss.target].movingX = (float)abs(PlayerX - deadBodies[zombieBoss.target].posX) / abs(PlayerY - deadBodies[zombieBoss.target].posY);
                    
                        if (deadBodies[zombieBoss.target].posX > PlayerX)
                            deadBodies[zombieBoss.target].movingX *= -1;
                        if (deadBodies[zombieBoss.target].posY > PlayerY)
                            deadBodies[zombieBoss.target].movingY *= -1;
                    }
                    zombieBoss.target = 0;
                    // after throughing he gains speed
                    zombieBoss.zombieAbility = 1;
                    zombieBoss.ZombieStartSpeed /= 2;
                    zombieBoss.abilityTimer = 300;

                    // setback because it actualy just moved to a body
                    player.win = 0;
                    zombieBoss.waitForNextZombieMove = zombieBoss.ZombieStartSpeed * 8;
                }
                return;
            }
        }
    }
}