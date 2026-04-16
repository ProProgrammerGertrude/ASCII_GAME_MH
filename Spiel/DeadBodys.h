#pragma once
#include <stdio.h>
#include <string>
#include "GameFunctions.h"
#include "Zombie.h"

class DeadBody
{
private:
	int posX;
	int posY;
	int size;
	bool moving;
	float movingX;
	float movingY;
	float roundingX;
	float roundingY;
	std::string normalPart;
	std::string redPart;


public:
	DeadBody(int posX, int posY, int size, string normalPart, string redPart)
		: posX(posX), posY(posY), size(size), normalPart(normalPart), redPart(redPart), moving(false), movingX(0), movingY(0), roundingX(0), roundingY(0)
	{
	}

	void MovingBody(int posX, int posY, int size, bool moving, float movingX, float movingY, float roundingX, float roundingY, string normalPart, string redPart, Zombie zombies[]);
};