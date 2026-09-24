#include "GameFunctions.h"
#include "Zombie.h"
#include "Player.h"
#include "ZombieBossHolo.h"

void PrintSwordAnimation(int posX, int posY, string str, Player& player, Zombie& zombie, ZombieBoss& zombieBoss);
void PrintSword(Player& player, int input);
void swordAnimations(Zombie& zombie, Player& player, ZombieBoss& zombieBoss);
void HitCheck(int SwordX, int SwordY,Player& player, Zombie& zombie, int howFar, ZombieBoss& zombieBoss);
void AttackCheck(Zombie zombies[], Player& player, ZombieBoss& zombieBoss, ZombieBossHolo zombieBossHolo[]);
