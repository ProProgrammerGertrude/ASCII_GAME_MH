#pragma once
#include <string>
#include "HTL_Konsole.h"
#include "GameFunctions.h"
#include "Map_Array.h"
#include "DeadBody.h"

class Zombie;

class Player
{
public:

	int lastNumberPressed = 5;
	int area = 1;
	int sword = 1;
	int swordAnimationPhase = -1;
	int waitForSwordAnimation = 0;
	int waitForNextMove = 0;
	int win = 0;
	int swordCooldown = 0;
	//0: labdoor, 1: laptop looked at // 2: acids // 3: cleaning fluids // 4: Sample Jar // 5: Gloves // 6: screwdriver // 7: Clamps // 8: EG key 
	//9: generator, // 10 code4Key // 11: philips key
	int inventory[12] = { 0 };
	int firstTimeInArea[6] = { 0 };
	bool swordCancel = false;
	bool swordSwingSide = false;

	string body[5];
	string outputBody;

	Player();

	int Borders(int& abbruch, int input);
	void PlayersMovement(int& input, int abbruch, Zombie zombies[], DeadBody deadBodies[]);

};