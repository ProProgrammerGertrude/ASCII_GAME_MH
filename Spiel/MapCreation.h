#pragma once
#include "GameFunctions.h"
#include "Zombie.h"
#include "DeadBody.h"
#include "Player.h"


bool SteppedOnBodyCheck(int posX, int posY, DeadBody deadBodies[], Player& player);
void PrintBodies(DeadBody deadBodies[], int area);
void PrintRemover(int x, int y);
void ChangeArea(Player& player, Zombie zombies[], DeadBody deadBodies[]);
void BoxMaker(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int value, char zeichen);
void TextPrinter(int x, int y, char* text, int time);
void interactObj(int seenValue, Zombie zombies[], DeadBody deadBodies[], Player& player);
