#include <stdio.h>
#include "Map_Array.h"
#include "Sword.h"
#include "GameFunctions.h"
#include "MapCreation.h"
#include "Player.h"
#include "ZombieBoss.h"
#include "ZombieBossHolo.h"

void PrintSwordAnimation(int posX, int posY, string str, Player& player, Zombie& zombie, ZombieBoss& zombieBoss)
{
    gotoxy(posX, posY);
    if (starterArea[posY][posX] == 0)
    {
        printf("%s", str.c_str());
        HitCheck(posX, posY, player, zombie, 1, zombieBoss);
    }
    else if (!NotOnDeadBody(posX, posY))
    {
        printf("\033[7;31m%s\033[0m", str.c_str());
        HitCheck(posX, posY, player, zombie, 1, zombieBoss);
    }
    else
        player.swordCancel = true;
}

void PrintSword(Player& player, int input)
{
    int i;
    if (player.sword == 1)
    {
        if (input == 119 || input == 72)
        {
            if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY - 1);
                printf("|");
            }
            else if (!NotOnDeadBody(PlayerX + 3, PlayerY - 1))
            {
                gotoxy(PlayerX + 3, PlayerY - 1);
                printf("\033[7;31m|\033[0m");
            }
        }
        else if (input == 97 || input == 75)
        {
            if ((starterArea[PlayerY][PlayerX - 3] == 0 || !NotOnDeadBody(PlayerX - 3, PlayerY))
                && (starterArea[PlayerY][PlayerX - 2] == 0 || !NotOnDeadBody(PlayerX - 2, PlayerY))
                && (starterArea[PlayerY][PlayerX - 1] == 0 || !NotOnDeadBody(PlayerX - 1, PlayerY)))
            {
                string swordToLeft = "<--";
                for (int i = 3; i > 0; i--)
                {
                    gotoxy(PlayerX - i, PlayerY);
                    if (!NotOnDeadBody(PlayerX - i, PlayerY))
                    {
                        printf("\033[7;31m%c\033[0m", swordToLeft[i - 1]);
                    }
                    else
                        printf("%c", swordToLeft[i - 1]);
                }
            }
        }
        else if (input == 115 || input == 80)
        {
            if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY + 1);
                printf("|");
            }
            else if (!NotOnDeadBody(PlayerX + 1, PlayerY + 1))
            {
                gotoxy(PlayerX + 1, PlayerY + 1);
                printf("\033[7;31m|\033[0m");
            }
        }
        else if (input == 100 || input == 77)
        {
            if ((starterArea[PlayerY][PlayerX + 5] == 0 || !NotOnDeadBody(PlayerX + 5, PlayerY))
                && (starterArea[PlayerY][PlayerX + 6] == 0 || !NotOnDeadBody(PlayerX + 6, PlayerY))
                && (starterArea[PlayerY][PlayerX + 7] == 0 || !NotOnDeadBody(PlayerX + 7, PlayerY)))
            {
                string swordToRight = ">--";
                for (int i = 0; i < 3; i++)
                {
                    gotoxy(PlayerX + i + 5, PlayerY);
                    if (!NotOnDeadBody(PlayerX + i + 5, PlayerY))
                    {
                        printf("\033[7;31m%c\033[0m", swordToRight[i]);
                    }
                    else
                        printf("%c", swordToRight[i]);
                }
            }
        }
        // für w
        if (player.lastNumberPressed == 1 && (input == 97 || input == 75))
        {
            if (starterArea[PlayerY - 1][PlayerX + 5] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY - 1);
                printf(" ");
            }
        }
        else if (player.lastNumberPressed == 1 && (input == 115 || input == 80))
        {
            if (starterArea[PlayerY - 2][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY - 2);
                printf(" ");
            }
        }
        else if (player.lastNumberPressed == 1 && (input == 100 || input == 77))
        {
            if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY - 1);
                printf(" ");
            }
        }
        // für a
        else if (player.lastNumberPressed == 2 && (input == 119 || input == 72))
        {
            for (i = 1; i <= 3; i++)
            {
                if (starterArea[PlayerY + 1][PlayerX - i] == 0)
                {
                    gotoxy(PlayerX - i, PlayerY + 1);
                    printf(" ");
                }
            }
        }
        else if (player.lastNumberPressed == 2 && (input == 115 || input == 80))
        {
            for (i = 1; i <= 3; i++)
            {
                if (starterArea[PlayerY - 1][PlayerX - i] == 0)
                {
                    gotoxy(PlayerX - i, PlayerY - 1);
                    printf(" ");
                }
            }
        }
        else if (player.lastNumberPressed == 2 && (input == 100 || input == 77))
        {
            for (i = 3; i <= 5; i++)
            {
                if (starterArea[PlayerY][PlayerX - i] == 0)
                {
                    gotoxy(PlayerX - i, PlayerY);
                    printf(" ");
                }
            }
        }
        // für s
        else if (player.lastNumberPressed == 3 && (input == 119 || input == 72))
        {
            if (starterArea[PlayerY + 2][PlayerX + 1] == 0)
            {
                gotoxy(PlayerX + 1, PlayerY + 2);
                printf(" ");
            }
        }
        else if (player.lastNumberPressed == 3 && (input == 97 || input == 75))
        {
            if (starterArea[PlayerY + 1][PlayerX + 3] == 0)
            {
                gotoxy(PlayerX + 3, PlayerY + 1);
                printf(" ");
            }
        }
        else if (player.lastNumberPressed == 3 && (input == 100 || input == 77))
        {
            if (starterArea[PlayerY + 1][PlayerX - 1] == 0)
            {
                gotoxy(PlayerX - 1, PlayerY + 1);
                printf(" ");
            }
        }
        // für d
        else if (player.lastNumberPressed == 4 && (input == 119 || input == 72))
        {
            for (i = 5; i <= 7; i++)
            {
                if (starterArea[PlayerY + 1][PlayerX + i] == 0)
                {
                    gotoxy(PlayerX + i, PlayerY + 1);
                    printf(" ");
                }
            }
        }
        else if (player.lastNumberPressed == 4 && (input == 97 || input == 75))
        {
            for (i = 7; i <= 9; i++)
            {
                if (starterArea[PlayerY][PlayerX + i] == 0)
                {
                    gotoxy(PlayerX + i, PlayerY);
                    printf(" ");
                }
            }
        }
        else if (player.lastNumberPressed == 4 && (input == 115 || input == 80))
        {
            for (i = 5; i <= 7; i++)
            {
                if (starterArea[PlayerY - 1][PlayerX + i] == 0)
                {
                    gotoxy(PlayerX + i, PlayerY - 1);
                    printf(" ");
                }
            }
        }
    }
}

void swordAnimations(Zombie& zombie, Player& player, ZombieBoss& zombieBoss)
{
    if (player.lastNumberPressed == 1)
    {
        if (player.swordAnimationPhase == 1 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 5, PlayerY - 1, "/", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 3, PlayerY - 1);
                PrintRemover(PlayerX + 4, PlayerY - 1);
            }

        }
        else if (player.swordAnimationPhase == 2 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 4, PlayerY - 1, "/", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 5, PlayerY - 1);
                PrintRemover(PlayerX + 3, PlayerY - 1);
            }
        }
        else if (player.swordAnimationPhase == 3 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 3, PlayerY - 1, "|", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 2, PlayerY - 1);
                PrintRemover(PlayerX + 4, PlayerY - 1);
            }
        }
        else if (player.swordAnimationPhase == 4 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 2, PlayerY - 1, "\\", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 3, PlayerY - 1);
            }
        }
        else if (player.swordAnimationPhase == 5 || player.swordAnimationPhase == 0)
        {
            if (starterArea[PlayerY - 1][PlayerX + 3] == 0 || !NotOnDeadBody(PlayerX + 3, PlayerY - 1))
            {
                PrintSwordAnimation(PlayerX + 3, PlayerY - 1, "|", player, zombie, zombieBoss);

                PrintRemover(PlayerX + 2, PlayerY - 1);
                PrintRemover(PlayerX + 4, PlayerY - 1);
                PrintRemover(PlayerX + 5, PlayerY - 1);
                player.swordCancel = false;
            }
        }
    }
    else if (player.lastNumberPressed == 2)
    {
        if (player.swordAnimationPhase == 1 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX - 2, PlayerY - 1, "\\", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX - 3, PlayerY);
                PrintRemover(PlayerX - 2, PlayerY);
                PrintRemover(PlayerX - 1, PlayerY);
            }
        }
        else if (player.swordAnimationPhase == 2 && !player.swordCancel)
        {
            if ((starterArea[PlayerY][PlayerX - 3] == 0 || !NotOnDeadBody(PlayerX - 3, PlayerY))
                && (starterArea[PlayerY][PlayerX - 2] == 0 || !NotOnDeadBody(PlayerX - 2, PlayerY))
                && (starterArea[PlayerY][PlayerX - 1] == 0 || !NotOnDeadBody(PlayerX-1, PlayerY)))
            {
                PrintSwordAnimation(PlayerX - 3, PlayerY, "-", player, zombie, zombieBoss);
                PrintSwordAnimation(PlayerX - 2, PlayerY, "-", player, zombie, zombieBoss);
                PrintSwordAnimation(PlayerX - 1, PlayerY, "<", player, zombie, zombieBoss);

                PrintRemover(PlayerX - 2, PlayerY - 1);
                PrintRemover(PlayerX - 2, PlayerY + 1);
            }
            else
                player.swordCancel = true;
        }
        else if (player.swordAnimationPhase == 3 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX - 2, PlayerY + 1, "/", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX - 3, PlayerY);
                PrintRemover(PlayerX - 2, PlayerY);
                PrintRemover(PlayerX - 1, PlayerY);
            }
        }
        else if (player.swordAnimationPhase == 4 || player.swordAnimationPhase == 0)
        {
            PrintSwordAnimation(PlayerX - 3, PlayerY, "-", player, zombie, zombieBoss);
            PrintSwordAnimation(PlayerX - 2, PlayerY, "-", player, zombie, zombieBoss);
            PrintSwordAnimation(PlayerX - 1, PlayerY, "<", player, zombie, zombieBoss);

            PrintRemover(PlayerX - 2, PlayerY - 1);
            PrintRemover(PlayerX - 2, PlayerY + 1);

            player.swordCancel = false;
        }
    }
    else if (player.lastNumberPressed == 3)
    {
        if (player.swordAnimationPhase == 1 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX - 1, PlayerY + 1, "/", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX, PlayerY + 1);
            }
        }
        else if (player.swordAnimationPhase == 2 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX, PlayerY + 1, "/", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX - 1, PlayerY + 1);
                PrintRemover(PlayerX + 1, PlayerY + 1);
            }
        }
        else if (player.swordAnimationPhase == 3 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 1, PlayerY + 1, "|", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX, PlayerY + 1);
                PrintRemover(PlayerX + 2, PlayerY + 1);
            }
        }
        else if (player.swordAnimationPhase == 4 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 2, PlayerY + 1, "\\", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 1, PlayerY + 1);
            }
        }
        else if (player.swordAnimationPhase == 5 || player.swordAnimationPhase == 0)
        {
            PrintSwordAnimation(PlayerX + 1, PlayerY + 1, "|", player, zombie, zombieBoss);

            PrintRemover(PlayerX - 1, PlayerY + 1);
            PrintRemover(PlayerX, PlayerY + 1);
            PrintRemover(PlayerX + 2, PlayerY + 1);
            PrintRemover(PlayerX + 2, PlayerY + 1);

            player.swordCancel = false;
        }
    }
    else if (player.lastNumberPressed == 4)
    {
        if (player.swordAnimationPhase == 1 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 6, PlayerY - 1, "/", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 5, PlayerY);
                PrintRemover(PlayerX + 6, PlayerY);
                PrintRemover(PlayerX + 7, PlayerY);
            }
        }
        else if (player.swordAnimationPhase == 2 && !player.swordCancel)
        {
            if ((starterArea[PlayerY][PlayerX + 5] == 0 || !NotOnDeadBody(PlayerX + 5, PlayerY))
                && (starterArea[PlayerY][PlayerX + 6] == 0 || !NotOnDeadBody(PlayerX + 6, PlayerY))
                && (starterArea[PlayerY][PlayerX + 7] == 0 || !NotOnDeadBody(PlayerX + 7, PlayerY)))
            {
                PrintSwordAnimation(PlayerX + 5, PlayerY, ">", player, zombie, zombieBoss);
                PrintSwordAnimation(PlayerX + 6, PlayerY, "-", player, zombie, zombieBoss);
                PrintSwordAnimation(PlayerX + 7, PlayerY, "-", player, zombie, zombieBoss);

                PrintRemover(PlayerX + 6, PlayerY - 1);
                PrintRemover(PlayerX + 6, PlayerY + 1);
            }
        }
        else if (player.swordAnimationPhase == 3 && !player.swordCancel)
        {
            PrintSwordAnimation(PlayerX + 6, PlayerY + 1, "\\", player, zombie, zombieBoss);
            if (!player.swordCancel)
            {
                PrintRemover(PlayerX + 5, PlayerY);
                PrintRemover(PlayerX + 6, PlayerY);
                PrintRemover(PlayerX + 7, PlayerY);
            }
        }
        else if (player.swordAnimationPhase == 4 || player.swordAnimationPhase == 0)
        {
            PrintSwordAnimation(PlayerX + 5, PlayerY, ">", player, zombie, zombieBoss);
            PrintSwordAnimation(PlayerX + 6, PlayerY, "-", player, zombie, zombieBoss);
            PrintSwordAnimation(PlayerX + 7, PlayerY, "-", player, zombie, zombieBoss);

            PrintRemover(PlayerX + 6, PlayerY - 1);
            PrintRemover(PlayerX + 6, PlayerY + 1);

            player.swordCancel = false;
        }
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void HitCheck(int SwordX, int SwordY, Player& player, Zombie& zombie, int howFar, ZombieBoss& zombieBoss)
{
    for (int j = 0; j < howFar; j++)
    {
        for (int i = 0; i < zombie.ZombieSize; i++)
        {
            if (SwordX + j == zombie.ZombieposX + i && SwordY == zombie.ZombieposY)
            {
                zombie.Zombielife--; 
                gotoxy(zombie.ZombieposX, zombie.ZombieposY);
                printf("       ");
                if (zombie.BossOrPawn == 0)
                {
                    // normal zombie/pawn
                    if (player.lastNumberPressed == 1)
                    {
                        zombie.ZombieposY -= 2;
                    }
                    else if (player.lastNumberPressed == 2)
                    {
                        zombie.ZombieposX -= 3;
                    }
                    else if (player.lastNumberPressed == 3)
                    {
                        zombie.ZombieposY += 2;
                    }
                    else if (player.lastNumberPressed == 4)
                    {
                        zombie.ZombieposX += 3;
                    }
                }
                else if (zombie.BossOrPawn == 1)
                {
                    // bosszombie
                    

                    if (zombieBoss.zombieAbility == 1)
                        zombieBoss.ZombieStartSpeed *= 2;
                    else if (zombieBoss.zombieAbility == 2)
                        zombieBoss.invisible = false;
                    else if (zombieBoss.zombieAbility == 3)
                        zombieBoss.target = 0;

                    zombieBoss.abilityTimer = 50;
                    zombieBoss.zombieAbility = 0;
                    RandomPlacement(83, 22, 18, 12, zombieBoss.ZombieposX, zombieBoss.ZombieposY, zombieBoss.ZombieSize, 15);
                }
                else if (zombie.BossOrPawn == 2)
                {
                    RandomPlacement(83, 22, 18, 12, zombie.ZombieposX, zombie.ZombieposY, zombie.ZombieSize, 15);
                }
            }
        }
    }
}

void AttackCheck(Zombie zombies[], Player& player, ZombieBoss& zombieBoss, ZombieBossHolo zombieBossHolo[])
{
    if (player.swordAnimationPhase >= 0 && player.waitForSwordAnimation == 0)
    {
        if ((player.lastNumberPressed == 1 || player.lastNumberPressed == 3) && (player.swordAnimationPhase < 6 && player.swordAnimationPhase >= 0))
        {
            swordAnimations(zombies[0], player, zombieBoss);

            for (int i = 0; i < HowManyZombiesExist; i++)
            {
                if (player.area == zombies[i].ZombieArea)
                {
                    swordAnimations(zombies[i], player, zombieBoss);
                    if (zombies[i].Zombielife <= 0)
                    {
                        for (int j = 0; j < zombies[i].ZombieSize; j++)
                        {
                            starterArea[zombies[i].ZombieposY][zombies[i].ZombieposX + j] = zombies[i].ZombieDeathValue;
                        }
                        gotoxy(zombies[i].ZombieposX, zombies[i].ZombieposY);
                        printf("\033[0;32m[-X_X]-\033[0m");
                    }
                }
            }
            if (player.area == zombieBoss.ZombieArea)
            {
                swordAnimations(zombieBoss, player, zombieBoss);
                if (zombieBoss.Zombielife <= 0)
                {
                    if (zombieBoss.phase == 1)
                    {
                        zombieBoss.phase = 2;
                    }
                    else
                    {
                        for (int j = 0; j < zombieBoss.ZombieSize; j++)
                        {
                            starterArea[zombieBoss.ZombieposY][zombieBoss.ZombieposX + j] = zombieBoss.ZombieDeathValue;
                        }
                        gotoxy(zombieBoss.ZombieposX, zombieBoss.ZombieposY);
                        printf("\033[0;32m[-X_X]-\033[0m");
                    }
                }
                swordAnimations(zombieBossHolo[0], player, zombieBoss);
                for (int i = 0; i < HowManyZombieBossHolos; i++)
                {
                    swordAnimations(zombieBossHolo[i], player, zombieBoss);
                }
            }
            player.swordAnimationPhase += 1 + (-2 * player.swordSwingSide);
            player.waitForSwordAnimation++;
        }
        else if ((player.lastNumberPressed == 2 || player.lastNumberPressed == 4) && (player.swordAnimationPhase < 5 && player.swordAnimationPhase >= 0))
        {
            for (int i = 0; i < HowManyZombiesExist; i++)
            {
                swordAnimations(zombies[0], player, zombieBoss);

                if (player.area == zombies[i].ZombieArea)
                {
                    swordAnimations(zombies[i], player, zombieBoss);
                    if (zombies[i].Zombielife <= 0)
                    {

                        for (int j = 0; j < zombies[i].ZombieSize; j++)
                        {
                            starterArea[zombies[i].ZombieposY][zombies[i].ZombieposX + j] = zombies[i].ZombieDeathValue;
                        }
                        gotoxy(zombies[i].ZombieposX, zombies[i].ZombieposY);
                        printf("\033[0;32m[-X_X]-\033[0m");
                    }
                }
            }
            if (player.area == zombieBoss.ZombieArea)
            {
                swordAnimations(zombieBoss, player, zombieBoss);
                if (zombieBoss.Zombielife <= 0)
                {
                    if (zombieBoss.phase == 1)
                    {
                        zombieBoss.phase = 2;
                    }
                    else
                    {
                        for (int j = 0; j < zombieBoss.ZombieSize; j++)
                        {
                            starterArea[zombieBoss.ZombieposY][zombieBoss.ZombieposX + j] = zombieBoss.ZombieDeathValue;
                        }
                        gotoxy(zombieBoss.ZombieposX, zombieBoss.ZombieposY);
                        printf("\033[0;32m[-X_X]-\033[0m");
                    }
                }
                for (int i = 0; i < HowManyZombieBossHolos; i++)
                {
                    swordAnimations(zombieBossHolo[0], player, zombieBoss);

                    if (player.area == zombieBossHolo[i].ZombieArea)
                    {
                        swordAnimations(zombieBossHolo[i], player, zombieBoss);
                    }
                }
            }
            player.swordAnimationPhase += 1 + (-2 * player.swordSwingSide);
            player.waitForSwordAnimation++;
        }
        else
        {
            player.swordAnimationPhase = -1;
            player.waitForSwordAnimation = 0;
            player.swordCooldown = 30;
            player.swordSwingSide = false;
        }
    }
}