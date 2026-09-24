#include <stdio.h>
#include <vector>
#include "Map_Array.h"
#include "DeadBody.h"
#include <math.h>
#include "Player.h"
#include "Zombie.h"
#include "ZombieBoss.h"
#include "MapCreation.h"

void DeadBody::MovingBody(DeadBody& deadBodies, Zombie zombies[], Player& player, ZombieBoss& zombieBoss)
{

	int bonusX = 0;
	int bonusY = 0;

	if (abs(deadBodies.movingY) >= 1)
	{
		if (deadBodies.movingY >= 1)
			bonusY++;
		else
			bonusY--;
	}
	else
		deadBodies.roundingY += deadBodies.movingY;

	if (abs(deadBodies.movingX) >= 1)
	{
		if (deadBodies.movingX >= 1)
			bonusX++;
		else
			bonusX--;
	}
	else
		deadBodies.roundingX += deadBodies.movingX;


	if (abs(deadBodies.roundingY) >= 1)
	{
		if (deadBodies.roundingY >= 1)
		{
			deadBodies.roundingY--;
			bonusY++;
		}
		else
		{
			deadBodies.roundingY++;
			bonusY--;
		}
	}
	if (abs(deadBodies.roundingX) >= 1)
	{
		if (deadBodies.roundingX >= 1)
		{
			deadBodies.roundingX--;
			bonusX++;
		}
		else
		{
			deadBodies.roundingX++;
			bonusX--;
		}
	}
	
	bool movable = true;
	int posValue = 0;

	for (int i = 0; i < deadBodies.size; i++)
	{
		for (int j = 0; j < zombieBoss.ZombieSize; j++)
		{
			if (deadBodies.posY + bonusY == zombieBoss.ZombieposY && deadBodies.posX + bonusX + i == zombieBoss.ZombieposX)
			{
				posValue = zombieBoss.ZombieDeathValue;
			}
		}
		if (starterArea[deadBodies.posY + bonusY][deadBodies.posX + bonusX + i] == 0 || (starterArea[deadBodies.posY + bonusY][deadBodies.posX + bonusX + i] >= 9 
			&& starterArea[deadBodies.posY + bonusY][deadBodies.posX + bonusX + i] <= 20) || !NotOnDeadBody(deadBodies.posX + bonusX + i, deadBodies.posY + bonusY))
		{
			// if it would hit the player and something else, then it prios the player
			if(posValue == 0 || (posValue != 9 && posValue != 0 && posValue != zombieBoss.ZombieDeathValue))
				posValue = starterArea[deadBodies.posY + bonusY][deadBodies.posX + bonusX + i];
		}
		else
		{
			movable = false;
		}
	}

	if (movable)
	{
		if (posValue == 9)
		{
			player.waitForNextMove = 100;
			deadBodies.moving = false;
		}
		else if (posValue > 9 && posValue <= 20)
		{
			// can only be the boss zombie, because only he can through and hes the only zombie in the room
			zombieBoss.waitForNextZombieMove = zombieBoss.ZombieStartSpeed * 4;

			zombieBoss.outputRightBody.clear();
			// reprint zombieBoss
			if (!zombieBoss.invisible)
			{
				for (int i = 0; i < 7; i++)
				{
					zombieBoss.outputRightBody += zombieBoss.bodyToRight[i];
				}
			}
			// rechtsschauend
			gotoxy(zombieBoss.ZombieposX, zombieBoss.ZombieposY);
			printf("\033[0;32m%s\033[0m", zombieBoss.outputRightBody.c_str());


		}
		else
		{
			deadBodies.posY += bonusY;
			deadBodies.posX += bonusX;

			for (int i = 0; i < deadBodies.size; i++)
			{
				bool same = false;

				for (int j = 0; j < zombieBoss.ZombieSize; j++)
				{
					if (deadBodies.posX - bonusX + i == zombieBoss.ZombieposX + j && deadBodies.posY - bonusY == zombieBoss.ZombieposY)
					{
						same = true;
					}
				}
				if (!same && (starterArea[deadBodies.posY - bonusY][deadBodies.posX - bonusX + i] != 0 || !NotOnDeadBody(deadBodies.posX - bonusX + i, deadBodies.posY - bonusY)))
				{
					gotoxy(deadBodies.posX - bonusX + i, deadBodies.posY - bonusY);
					printf(" ");
				}
				starterArea[deadBodies.posY - bonusY][deadBodies.posX - bonusX + i] = 0;
			}

			gotoxy(deadBodies.posX, deadBodies.posY);
			printf("%s", deadBodies.bodyPart.c_str());
			for (int i = 0; i < deadBodies.size; i++)
			{
				starterArea[deadBodies.posY][deadBodies.posX + i] = deadBodies.value;
			}
			// hitting its own body or nothing
		}

		deadBodies.waitForNextBodyMove = 2;
	}
	else
	{
		deadBodies.movingY = 0;
		deadBodies.movingX = 0;
		deadBodies.roundingX = 0;
		deadBodies.roundingY = 0;
		deadBodies.moving = false;
	}
}
