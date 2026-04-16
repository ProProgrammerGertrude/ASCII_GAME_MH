#include <stdio.h>
#include "GameFunctions.h"
#include "Map_Array.h"
#include "DeadBodys.h"
#include <math.h>




void DeadBody::MovingBody(int posX, int posY, int size, bool moving, float movingX, float movingY, float roundingX, float roundingY, string normalPart, string redPart, Zombie zombies[])
{
	int bonusX = 0;
	int bonusY = 0;

	if (abs(movingY) >= 1)
	{
		if (movingY >= 1)
			bonusY++;
		else
			bonusY--;
	}
	else
		roundingY += movingY;

	if (abs(movingX) > 1)
	{
		if (movingX >= 1)
			bonusX++;
		else
			bonusX--;
	}
	else
		roundingX += movingX;


	if (abs(roundingY) >= 1)
	{
		if (roundingY >= 1)
		{
			roundingY--;
			bonusY++;
		}
		else
		{
			roundingY++;
			bonusY--;
		}
	}
	if (abs(roundingX) >= 1)
	{
		if (roundingX >= 1)
		{
			roundingX--;
			bonusX++;
		}
		else
		{
			roundingX++;
			bonusX--;
		}
	}
	
	

	if (starterArea[posY + bonusY][posX + bonusX] == 0 || (starterArea[posY + bonusY][posX + bonusX] >= 9 && starterArea[posY + bonusY][posX + bonusX] <= 20))
	{
		if (starterArea[posY + bonusY][posX + bonusX] == 0)
		{

		}
		else if (starterArea[posY + bonusY][posX + bonusX] == 0)
		{

		}
		else
		{

		}


		posY += bonusY;
	}
	else
	{
		movingY = 0;
		movingX = 0;
		roundingX = 0;
		roundingY = 0;
	}
}
