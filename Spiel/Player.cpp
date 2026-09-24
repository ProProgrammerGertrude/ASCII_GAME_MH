
#include <stdio.h>
#include <string>
#include "GameFunctions.h"
#include "Player.h"
#include "Zombie.h"
#include "DeadBody.h"
#include "Sword.h"
#include "MapCreation.h"

Player::Player()
{
    body[0] = "[";
    body[1] = "\xC2\xB0";
    body[2] = "-";
    body[3] = "\xC2\xB0";
    body[4] = "]";
    outputBody = "[\xC2\xB0-\xC2\xB0]";
}




int Player::Borders(int& abbruch, int input)
{
    // 0 = nichts
    // 1 = wand
    // 2 = junk table
    // 3 = laptop
    // 4 = sketches
    // 5 = microscope
    // 6 = bottles
    // 7 = Door
    // 8 = Bed
    // 9 = player


    if (sword == 0 || sword == 2)
    {
        if (input == 119 || input == 72)
        {
            for (int i = 0; i <= 4; i++)
            {
                if (starterArea[PlayerY - 1][PlayerX + i] >= 1 && NotOnDeadBody(PlayerX + i, PlayerY - 1))
                {
                    return abbruch = 1;
                }
            }
        }
        else if (input == 97 || input == 75)
        {
            if (starterArea[PlayerY][PlayerX - 1] >= 1 && starterArea[PlayerY][PlayerX - 1] != 9 && NotOnDeadBody(PlayerX -1, PlayerY))
            {
                return abbruch = 1;
            }
        }
        else if (input == 115 || input == 80)
        {
            for (int i = 0; i <= 4; i++)
            {
                if (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9 && NotOnDeadBody(PlayerX + i, PlayerY + 1))
                {
                    return abbruch = 1;
                }
            }
        }
        else if (input == 100 || input == 77)
        {
            if (starterArea[PlayerY][PlayerX + 5] >= 1 && starterArea[PlayerY][PlayerX + 5] != 9 && NotOnDeadBody(PlayerX + 5, PlayerY))
            {
                if (starterArea[PlayerY][PlayerX + 7] == 0)
                {
                    gotoxy(PlayerX + 7, PlayerY);
                    printf(" ");
                }
                return abbruch = 1;
            }
        }
    }
    // sword == 1
    else if (sword == 1)
    {
        if (input == 119 || input == 72)
        {
            for (int i = 0; i <= 4; i++)
            {
                if (starterArea[PlayerY - 2][PlayerX + 3] >= 1 && starterArea[PlayerY - 2][PlayerX + 3] != 9 && NotOnDeadBody(PlayerX + 3, PlayerY - 2))
                {
                    sword = 2;
                }
                if (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9 && NotOnDeadBody(PlayerX + i, PlayerY - 1))
                {
                    sword = 2;
                    return abbruch = 1;
                }
            }
        }
        else if (input == 97 || input == 75)
        {
            for (int i = 0; i <= 5; i++)
            {
                if (starterArea[PlayerY][PlayerX - i] >= 1 && starterArea[PlayerY][PlayerX - i] != 9 && NotOnDeadBody(PlayerX - i, PlayerY))
                {
                    if (starterArea[PlayerY][PlayerX - 3] == 0)
                    {
                        gotoxy(PlayerX - 3, PlayerY);
                        printf(" ");
                    }
                    if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                    {
                        gotoxy(PlayerX + 5, PlayerY);
                        printf("   ");
                    }
                    if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
                    {
                        gotoxy(PlayerX + 1, PlayerY + 1);
                        printf(" ");
                    }
                    if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                    {
                        gotoxy(PlayerX + 1, PlayerY - 1);
                        printf(" ");
                    }
                    if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                    {
                        gotoxy(PlayerX + 3, PlayerY - 1);
                        printf(" ");
                    }
                    if (starterArea[PlayerY + 1][PlayerX + 3] == 0)
                    {
                        gotoxy(PlayerX + 3, PlayerY + 1);
                        printf(" ");
                    }
                    sword = 2;
                    if (starterArea[PlayerY][PlayerX - 1] >= 1 && starterArea[PlayerY][PlayerX - 1] != 9 && NotOnDeadBody(PlayerX - 1, PlayerY))
                    {
                        return abbruch = 1;
                    }
                    else
                    {
                        return abbruch = 0;
                    }
                }
            }
        }
        else  if (input == 115 || input == 80)
        {
            for (int i = 0; i <= 4; i++)
            {

                if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                {
                    gotoxy(PlayerX + 3, PlayerY - 1);
                    printf(" ");
                }
                if (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9 && NotOnDeadBody(PlayerX + i, PlayerY + 2))
                {
                    sword = 2;
                }
                if (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9 && NotOnDeadBody(PlayerX + i, PlayerY + 1))
                {
                    sword = 2;
                    return abbruch = 1;
                }
            }
        }
        else  if (input == 100 || input == 77)
        {
            for (int i = 0; i <= 5; i++)
            {
                if (starterArea[PlayerY][PlayerX + 5 + i] >= 1 && starterArea[PlayerY][PlayerX + 5 + i] != 9 && NotOnDeadBody(PlayerX + 5 + i, PlayerY))
                {
                    if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                    {
                        gotoxy(PlayerX + 5, PlayerY);
                        printf("   ");
                    }
                    if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
                    {
                        gotoxy(PlayerX + 1, PlayerY + 1);
                        printf(" ");
                    }
                    if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                    {
                        gotoxy(PlayerX - 3, PlayerY);
                        printf("   ");
                    }
                    if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                    {
                        gotoxy(PlayerX + 1, PlayerY - 1);
                        printf(" ");
                    }
                    if (starterArea[PlayerY - 1][PlayerX + 3] == 0)
                    {
                        gotoxy(PlayerX + 3, PlayerY - 1);
                        printf(" ");
                    }
                    sword = 2;
                    if (starterArea[PlayerY][PlayerX + 5] >= 1 && starterArea[PlayerY][PlayerX + 5] != 9 && NotOnDeadBody(PlayerX + 5, PlayerY))
                    {
                        return abbruch = 1;
                    }
                    else {
                        return abbruch = 0;
                    }
                }

            }
        }
    }

    //sword = 2
    if (sword == 2)
    {
        if ((input != 119 && input != 72) && lastNumberPressed == 1)
        {
            for (int i = 0; i <= 4; i++)
            {

                if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX + 1] == 1 || starterArea[PlayerY][PlayerX] == 1))
                {
                    return abbruch = 1;
                }
                else if ((input == 115 || input == 80) && (starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9 && NotOnDeadBody(PlayerX + i, PlayerY + 1)))
                {
                    return abbruch = 1;
                }
                // sword in no wall
                else if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9 ))
                {
                    if (NotOnDeadBody(PlayerX + i, PlayerY + 2))
                    {
                        sword = 2;
                        if (starterArea[PlayerY - 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY - 1);
                            printf(" ");
                        }
                    }
                    return abbruch = 0;
                }
                else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + 5 + 1] == 1 || starterArea[PlayerY][PlayerX + 5 + 2] == 1))
                {
                    return abbruch = 1;
                }


            }
            if (starterArea[PlayerY][PlayerX - 1] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3] == 0)
            {
                gotoxy(PlayerX - 3, PlayerY);
                printf("   ");
            }
            if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY);
                printf("   ");
            }
            sword = 1;
        }
        else if ((input != 97 && input != 75) && lastNumberPressed == 2)
        {

            for (int i = 0; i <= 4; i++)
            {
                if ((input == 119 || input == 72) && (starterArea[PlayerY - 1][PlayerX + i] == 1))
                {

                    return abbruch = 0;
                }
                // sword in no wall
                else if ((input == 119 || input == 72) && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                {
                    if (NotOnDeadBody(PlayerX + i, PlayerY - 2))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf("   ");
                        }
                    }
                    return abbruch = 0;
                }
                else if ((input == 115 || input == 80) && (starterArea[PlayerY + 1][PlayerX + i] == 1))
                {
                    return abbruch = 1;
                }
                else if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9 && NotOnDeadBody(PlayerX + i, PlayerY + 2)))
                {
                    sword = 2;
                    if (starterArea[PlayerY][PlayerX - 3] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 1] == 0)
                    {
                        gotoxy(PlayerX - 3, PlayerY);
                        printf("   ");
                    }
                    
                    return abbruch = 0;
                }
                else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + 4 + i] >= 1 && starterArea[PlayerY][PlayerX + 4 + i] != 9))
                {
                    if (NotOnDeadBody(PlayerX + 4 + i, PlayerY))
                    {
                        if (starterArea[PlayerY][PlayerX - 3] == 0)
                        {
                            gotoxy(PlayerX - 3, PlayerY);
                            printf(" ");
                        }
                    }
                    sword = 2;
                    return abbruch = 0;
                }
            }
            sword = 1;
        }
        else if ((input != 115 && input != 80) && lastNumberPressed == 3)
        {
            for (int i = 0; i <= 4; i++)
            {
                if ((input == 119 || input == 72) && (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9) && NotOnDeadBody(PlayerX + i, PlayerY - 1)
                    )
                {
                    return abbruch = 1;
                }
                // sword in no wall
                else if ((input == 119 || input == 72) && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                {
                    if (NotOnDeadBody(PlayerX + i, PlayerY - 2))
                    {
                        sword = 2;
                        if (starterArea[PlayerY + 1][PlayerX + 1] == 0)
                        {
                            gotoxy(PlayerX + 1, PlayerY + 1);
                            printf(" ");
                        }
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                    }
                    return abbruch = 0;
                }
                else if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX - i] >= 1 || starterArea[PlayerY][PlayerX - i] != 9))
                {
                    if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                    {
                        gotoxy(PlayerX + 5, PlayerY);
                        printf("   ");
                    }
                    sword = 1;
                    
                    return abbruch = 0;
                }
                else if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + 5] >= 1 && starterArea[PlayerY][PlayerX + 5] != 9) && NotOnDeadBody(PlayerX + 5, PlayerY))
                {
                    return abbruch = 1;
                }
            }
            if (starterArea[PlayerY][PlayerX - 1] == 0 && starterArea[PlayerY][PlayerX - 2] == 0 && starterArea[PlayerY][PlayerX - 3] == 0)
            {
                gotoxy(PlayerX - 3, PlayerY);
                printf("   ");
            }
            if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
            {
                gotoxy(PlayerX + 5, PlayerY);
                printf("   ");
            }

            sword = 1;
        }
        else if ((input != 100 && input != 77) && lastNumberPressed == 4)
        {
            for (int i = 0; i <= 4; i++)
            {
                if ((input == 119 || input == 72) && (starterArea[PlayerY - 1][PlayerX + i] >= 1 && starterArea[PlayerY - 1][PlayerX + i] != 9) && NotOnDeadBody(PlayerX + i, PlayerY - 1))
                {
                    return abbruch = 1;
                }
                // sword in no wall
                else if ((input == 119 || input == 72) && (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9))
                {
                    if (NotOnDeadBody(PlayerX + i, PlayerY - 2))
                    {
                        sword = 2;
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                    }
                    return abbruch = 0;
                }
                else if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX - 1 - i] >= 1 && starterArea[PlayerY][PlayerX - 1 - i] != 9))
                {
                    if (NotOnDeadBody(PlayerX - 1 - i, PlayerY))
                    {
                        if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                        {
                            gotoxy(PlayerX + 5, PlayerY);
                            printf("   ");
                        }
                        sword = 2;
                    }
                    if (starterArea[PlayerY][PlayerX - 1] >= 1 && starterArea[PlayerY][PlayerX - 1] != 9 && NotOnDeadBody(PlayerX - 1, PlayerY))
                    {
                        return abbruch = 1;
                    }
                    else {
                        return abbruch = 0;
                    }
                }
                else if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9 || starterArea[PlayerY + 1][PlayerX + i] >= 1 && starterArea[PlayerY + 1][PlayerX + i] != 9))
                {
                    if (starterArea[PlayerY][PlayerX + 5] == 0 && starterArea[PlayerY][PlayerX + 6] == 0 && starterArea[PlayerY][PlayerX + 7] == 0)
                    {
                        gotoxy(PlayerX + 5, PlayerY);
                        printf("   ");
                    }

                    if (starterArea[PlayerY + 1][PlayerX + i] >= 1 && NotOnDeadBody(PlayerX + i, PlayerY + 1))
                    {
                        return abbruch = 1;
                    }
                    else {
                        return abbruch = 0;
                    }
                }
                else if ((input == 115 || input == 80) && (starterArea[PlayerY + 1][PlayerX + i] == 1 && NotOnDeadBody(PlayerX + i, PlayerY + 1)))
                {

                    return abbruch = 1;
                }
            }

            sword = 1;
        }
        else if ((input == 119 || input == 72) && lastNumberPressed == 1)
        {
            for (int i = 0; i <= 4; i++)
            {
                if (starterArea[PlayerY - 2][PlayerX + i] >= 1 && starterArea[PlayerY - 2][PlayerX + i] != 9)
                {
                    if(NotOnDeadBody(PlayerX + i, PlayerY - 2))
                        sword = 2;
                    return abbruch = 0;
                }
            }

            sword = 1;
        }
        else if ((input == 97 || input == 75) && (lastNumberPressed == 2))
        {
            for (int i = 0; i <= 4; i++)
            {
                if ((input == 97 || input == 75) && (starterArea[PlayerY][PlayerX - 1 - i] >= 1 && starterArea[PlayerY][PlayerX - 1 - i] != 9))
                {
                    if(NotOnDeadBody(PlayerX - 1 - i, PlayerY))
                        sword = 2;
                    return abbruch = 0;
                }
            }
            sword = 1;
        }
        else if ((input == 115 || input == 80) && lastNumberPressed == 3)
        {
            for (int i = 0; i <= 4; i++)
            {
                if ((input == 115 || input == 80) && (starterArea[PlayerY + 2][PlayerX + i] >= 1 && starterArea[PlayerY + 2][PlayerX + i] != 9))
                {
                    if(NotOnDeadBody(PlayerX + i, PlayerY + 2))
                        sword = 2;
                    return abbruch = 0;
                }
            }
            sword = 1;
        }
        else if ((input == 100 || input == 77) && (lastNumberPressed == 4))
        {
            for (int i = 0; i <= 7; i++)
            {
                if ((input == 100 || input == 77) && (starterArea[PlayerY][PlayerX + i] >= 1 && starterArea[PlayerY][PlayerX + i] != 9))
                {
                    if(NotOnDeadBody(PlayerX + i, PlayerY))
                        sword = 2;
                    return abbruch = 0;
                }
            }
            sword = 1;
        }
    }
}

void Player::PlayersMovement(int& input, int abbruch, Zombie zombies[], DeadBody deadBodies[])
{
    int i;
    int k;
    outputBody.clear();

    //fürs nach oben scrollen
    gotoxy(140, 1);
    printf(" ");

    PrintBodies(deadBodies, area);

    if (input == 119 || input == 72)
    {
        Borders(abbruch, input);


        if (abbruch == 0)
        {
            
            PlayerY--;

            // printing the player red if over a body
            for (int i = 0; i < 5; i++)
            {
                if (SteppedOnBodyCheck(PlayerX + i, PlayerY, deadBodies, *this))
                    outputBody += "\033[7;31m" + body[i] + "\033[0m";
                else
                    outputBody += body[i];
            }

            // playersposition in the Area Array
            for (int i = 0; i <= 4; i++)
            {
                starterArea[PlayerY][PlayerX + i] = 9;
                starterArea[PlayerY + 1][PlayerX + i] = 0;
            }

            //print the player
            gotoxy(PlayerX, PlayerY);
            printf("%s", outputBody.c_str());
            /*
            gotoxy(playerX - 1, playerY);
            printf("%d%d%d%d%d%d%d%d", starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
            */


            PrintSword(*this, input);

            lastNumberPressed = 1;

            // remove the position of the players last position
            for (int i = 0; i < 5; i++)
            {
                if (!SteppedOnBodyCheck(PlayerX + i, PlayerY + 1, deadBodies, *this))
                {
                    gotoxy(PlayerX + i, PlayerY + 1);
                    printf(" ");
                }
            }
        }
    }
    else if (input == 97 || input == 75)
    {
        Borders(abbruch, input);


        if (abbruch == 0)
        {

            int HowManyMoves = 2;

            if (starterArea[PlayerY][PlayerX - 2] != 0 && starterArea[PlayerY][PlayerX - 2] != 9 && NotOnDeadBody(PlayerX - 2, PlayerY))
                HowManyMoves = 1;

            PlayerX -= HowManyMoves;

            for (int i = 0; i < 5; i++)
            {
                if (SteppedOnBodyCheck(PlayerX + i, PlayerY, deadBodies, *this))
                    outputBody += "\033[7;31m" + body[i] + "\033[0m";
                else
                    outputBody += body[i];
            }

            for (int i = 0; i < HowManyMoves; i++)
            {
                starterArea[PlayerY][PlayerX + i] = 9;

                starterArea[PlayerY][PlayerX + i + 5] = 0;
            }
            gotoxy(PlayerX, PlayerY);
            printf("%s", outputBody.c_str());
            /*
            gotoxy(playerX - 1, playerY);
            printf("%d%d%d%d%d%d%d%d", starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
            */

            PrintSword(*this, input);

            lastNumberPressed = 2;

            for (int i = 0; i < HowManyMoves; i++)
            {
                if (!SteppedOnBodyCheck(PlayerX + 5 + i, PlayerY, deadBodies, *this))
                {
                    gotoxy(PlayerX + 5 + i, PlayerY);
                    printf(" ");
                }
            }
        }
    }
    else if (input == 115 || input == 80)
    {

        Borders(abbruch, input);

        if (abbruch == 0)
        {
            PlayerY++;
            for (int i = 0; i < 5; i++)
            {
                if (SteppedOnBodyCheck(PlayerX + i, PlayerY, deadBodies, *this))
                    outputBody += "\033[7;31m" + body[i] + "\033[0m";
                else
                    outputBody += body[i];
            }

            for (int i = 0; i <= 4; i++)
            {
                starterArea[PlayerY][PlayerX + i] = 9;

                starterArea[PlayerY - 1][PlayerX + i] = 0;
            }

            gotoxy(PlayerX, PlayerY);
            printf("%s", outputBody.c_str());
            /*
             gotoxy(playerX - 1, playerY);
             printf("%d%d%d%d%d%d%d%d", starterArea[playerY][playerX - 1], starterArea[playerY][playerX], starterArea[playerY][playerX + 1], starterArea[playerY][playerX + 2], starterArea[playerY][playerX + 3], starterArea[playerY][playerX + 4], starterArea[playerY][playerX + 5], starterArea[playerY][playerX + 6]);
             */


            PrintSword(*this, input);

            lastNumberPressed = 3;

            // remove the position of the players last position
            for (int i = 0; i < 5; i++)
            {
                if (!SteppedOnBodyCheck(PlayerX + i, PlayerY - 1, deadBodies, *this))
                {
                    gotoxy(PlayerX + i, PlayerY - 1);
                    printf(" ");
                }
            }
        }
    }
    else if (input == 100 || input == 77)
    {

        Borders(abbruch, input);

        if (abbruch == 0)
        {
            int HowManyMoves = 2;

            if (starterArea[PlayerY][PlayerX + 6] != 0 && starterArea[PlayerY][PlayerX + 6] != 9 && NotOnDeadBody(PlayerX + 6, PlayerY))
                HowManyMoves = 1;
            PlayerX += HowManyMoves;

            for (int i = 0; i < 5; i++)
            {
                if (SteppedOnBodyCheck(PlayerX + i, PlayerY, deadBodies, *this))
                    outputBody += "\033[7;31m" + body[i] + "\033[0m";
                else
                    outputBody += body[i];
            }

            for (int i = 0; i < HowManyMoves; i++)
            {
                starterArea[PlayerY][PlayerX + 3 + i] = 9;
                starterArea[PlayerY][PlayerX - i - 1] = 0;
            }


            gotoxy(PlayerX, PlayerY);
            printf("%s", outputBody.c_str());

            //gotoxy(PlayerX - 2, PlayerY);
            //printf("%d%d%d%d%d%d%d%d%d",starterArea[PlayerY][PlayerX - 2], starterArea[PlayerY][PlayerX - 1], starterArea[PlayerY][PlayerX], starterArea[PlayerY][PlayerX + 1], starterArea[PlayerY][PlayerX + 2], starterArea[PlayerY][PlayerX + 3], starterArea[PlayerY][PlayerX + 4], starterArea[PlayerY][PlayerX + 5], starterArea[PlayerY][PlayerX + 6]);


            PrintSword(*this, input);
            lastNumberPressed = 4;

            for (int i = 0; i < HowManyMoves; i++)
            {
                if (!SteppedOnBodyCheck(PlayerX - i - 1, PlayerY, deadBodies, *this))
                {
                    gotoxy(PlayerX - i - 1, PlayerY);
                    printf(" ");
                }
            }
        }
    }
    else if (input == 101)
    {
        int seenValue = 0;
        for (i = 1; i <= 2; i++)
        {
            if (starterArea[PlayerY][PlayerX + 4 + i] > 1)
            {
                seenValue = starterArea[PlayerY][PlayerX + 4 + i];
                break;
            }
        }
        for (i = 1; i <= 2; i++)
        {
            if (starterArea[PlayerY][PlayerX - i] > 1)
            {
                seenValue = starterArea[PlayerY][PlayerX - i];
                break;
            }
        }
        for (i = 0; i < 5; i++)
        {
            if (starterArea[PlayerY + 1][PlayerX + i] > 1)
            {
                seenValue = starterArea[PlayerY + 1][PlayerX + i];
                break;
            }
        }
        for (i = 0; i < 5; i++)
        {
            if (starterArea[PlayerY - 1][PlayerX + i] > 1)
            {
                seenValue = starterArea[PlayerY - 1][PlayerX + i];
                break;
            }
        }


        interactObj(seenValue, zombies, deadBodies, *this);
    }
    else if (input == 32)
    {

        if (sword == 1 && swordCooldown == 0)
        {
            // all possible first sword moves
            if ((lastNumberPressed == 1 && (starterArea[PlayerY - 1][PlayerX + 5] != 0 || starterArea[PlayerY - 1][PlayerX + 4] != 0)) ||
                (lastNumberPressed == 2 && starterArea[PlayerY - 1][PlayerX - 2] != 0) ||
                (lastNumberPressed == 3 && (starterArea[PlayerY + 1][PlayerX - 1] != 0 || starterArea[PlayerY + 1][PlayerX] != 0)) ||
                (lastNumberPressed == 4 && starterArea[PlayerY - 1][PlayerX + 6] != 0))
            {
                if (lastNumberPressed == 1 || lastNumberPressed == 3)
                    swordAnimationPhase = 4;
                else
                    swordAnimationPhase = 3;

                swordSwingSide = true;
            }
            else
            {
                swordAnimationPhase = 1;
                swordSwingSide = false;
            }
        }
    }
}
