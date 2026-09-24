#pragma once
#include <stdio.h>
#include <string>
#include "GameFunctions.h"
#include "Zombie.h"

class ZombieBoss;

class DeadBody
{
public:
	int posX;
	int posY;
	int size;
	int area;
	int value;
	bool moving;
	float movingX;
	float movingY;
	float roundingX;
	float roundingY;

	std::string bodyPart;
	int waitForNextBodyMove = 0;


public:
	DeadBody(int posX, int posY, int size, string FirstPart, int Area, int Value)
		: posX(posX), posY(posY), size(size), bodyPart(FirstPart), moving(false), movingX(0), movingY(0), roundingX(0), roundingY(0), area(Area), value(Value)
	{
	}

	void MovingBody(DeadBody& deadBodies, Zombie zombies[], Player& player, ZombieBoss& zombieBoss);
};

extern DeadBody deadBodies[HowManyDeadBodies];