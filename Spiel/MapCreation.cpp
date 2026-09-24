#include <stdio.h>
#include <vector>
#include <conio.h>
#include "HTL_Konsole.h"
#include <string>
#include "MapCreation.h"
#include "GameFunctions.h"
#include "Player.h"
#include "Zombie.h"

bool SteppedOnBodyCheck(int posX, int posY, DeadBody deadBodies[], Player& player)
{
    for (int j = 0; j < HowManyDeadBodies; j++)
    {
        if (deadBodies[j].area == player.area)
        {
            for (int k = 0; k < deadBodies[j].size; k++)
            {
                if (posX == (deadBodies[j].posX + k) && posY == deadBodies[j].posY)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void PrintBodies(DeadBody deadBodies[], int area) 
{
    for (int i = 0; i < HowManyDeadBodies; i++)
    {
        if (deadBodies[i].area == area)
        {
            for (int j = 0; j < deadBodies[i].size; j++)
            {
                starterArea[deadBodies[i].posY][deadBodies[i].posX + j] = deadBodies[i].value;
            }
            gotoxy(deadBodies[i].posX, deadBodies[i].posY);
            printf("%s", deadBodies[i].bodyPart.c_str());
        }
    }
}

void PrintRemover(int x, int y)
{
    if (starterArea[y][x] == 0)
    {
        gotoxy(x, y);
        printf(" ");
    }
}

void interactObj(int seenValue, Zombie zombies[], DeadBody deadBodies[], Player& player)
{
    // 0 empty
    // 1 non interactable
    // 9 player
    // 10 - 19 zombies
    // 2 - 8, 20 - 69 interactable objects
    // 70 - 80 dead bodies

    if (player.area == 1)
    {
        //für 2
        if (seenValue == 2)
        {
            TextPrinter(5, 46, "stuff that you need for some science shit", 2000);
        }

        //für 3
        else if (seenValue == 3)
        {
            gotoxy(5, 46);
            printf("                     ");
            gotoxy(5, 46);
            printf("A Laptop...");
            Sleep(1000);
            gotoxy(17, 46);
            printf("on the screen is a indian guy giving a tutorial on how to make a dissolvant acid *you finish the video*");
            Sleep(6000);
            gotoxy(5, 46);
            printf("                                                                                                                      ");

            player.inventory[1] = 1;

            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

        }

        //für 4
        else if (seenValue == 4)
        {
            TextPrinter(5, 46, "*A paper with lots of science, that you are to dumb for!*", 3000);
        }
        //für 5
        else if (seenValue == 5)
        {
            TextPrinter(5, 46, "*A microscope with blood on it.*", 2000);
        }
        //für 6 tools
        else if (seenValue == 6)
        {
            TextPrinter(5, 46, "*A couple of tools* and no you cant pick them up because im to lazy*", 5000);
        }
        // für 7
        else if (seenValue == 7)
        {
            TextPrinter(5, 46, "*the door opens*", 1000);

            PlayerX = 42;
            PlayerY = 12;
            player.area = 2;
            ChangeArea(player, zombies, deadBodies);
        }

        //für 8 sickbed
        else if (seenValue == 8)
        {
            TextPrinter(5, 46, "*A sickbed*", 1000);
        }
        //für 10 standard Zombie(kein loot)
        else if (seenValue == 10)
        {
            TextPrinter(5, 46, "Hes a btch with no loot", 2000);
        }
        //für 11 (some random stuff)
        else if (seenValue == 11)
        {
            TextPrinter(5, 46, "Im to stupid to think of other stuff", 4000);
        }
        //für 20 DoctorsZombie
        else if (seenValue == 20)
        {
            gotoxy(5, 46);
            printf("                     ");
            gotoxy(5, 46);
            printf("He seemed to be a lab supervisor...");
            Sleep(2000);
            if (player.inventory[0] == 0)
            {
                printf(" *you took his ID Badge*");
                Sleep(2000);
                player.inventory[0] = 1;
            }
            gotoxy(5, 46);
            printf("                                                      ");
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        }
    }
    else if (player.area == 2)
    {
        // door to the lagerraum
        if (seenValue == 2)
        {

            TextPrinter(5, 46, "*the door opens*", 1000);

            PlayerX = 115;
            PlayerY = 16;
            player.area = 3;
            ChangeArea(player, zombies, deadBodies);


        }
        //door to the exit
        else if (seenValue == 3)
        {
            if (player.inventory[9] == 1)
            {
                TextPrinter(5, 46, "*the door opens*", 1000);
            }
            else
            {
                TextPrinter(5, 46, "*the door needs electricity to open*", 3000);
            }
        }
        // door to the lab
        else if (seenValue == 4)
        {
            TextPrinter(5, 46, "*the door opens*", 1000);
            PlayerX = 69;
            PlayerY = 2;
            player.area = 1;
            ChangeArea(player, zombies, deadBodies);
        }
        // door to the closet
        else if (seenValue == 5)
        {
            TextPrinter(5, 46, "*the door opens*", 1000);
            PlayerX = 47;
            PlayerY = 29;
            player.area = 6;
            ChangeArea(player, zombies, deadBodies);
        }
        // the open door
        else if (seenValue == 6)
        {
            TextPrinter(5, 46, "*the door opens*", 1000);
            PlayerX = 10;
            PlayerY = 29;
            player.area = 5;
            ChangeArea(player, zombies, deadBodies);
        }
        // left dead person
        else if (seenValue == 70)
        {
            TextPrinter(5, 46, "This person died a terrifying death", 3000);
        }
        // the rolling bed
        else if (seenValue == 8)
        {
            TextPrinter(5, 46, "what happend to the person on that bed?", 4000);
        }
        // the fast Zombie
        else if (seenValue == 10)
        {
            TextPrinter(5, 46, "Is he like a mutation or what was that", 3000);
        }
        // the eaten up person
        else if (seenValue == 72)
        {
            gotoxy(5, 46);
            printf("Hey are you still alive?");
            Sleep(2000);
            gotoxy(5, 46);
            printf("                        ");
            gotoxy(5, 46);
            printf("*silence*");
            Sleep(1000);
            gotoxy(5, 46);
            printf("         ");

            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        }
        // dead body
        else if (seenValue == 71)
        {
            TextPrinter(5, 46, "yeah I dont think hes alive!", 2000);
        }
    }
    else if (player.area == 3)
    {
        // chem bottles
        if (seenValue == 2)
        {
            TextPrinter(5, 46, "*Assorted chemical bottles. Labels are faded.*", 3000);
        }
        // drums
        else if (seenValue == 3)
        {
            TextPrinter(5, 46, "*Heavy chemical drums. Too large to move.*", 3000);
        }
        // reagents
        else if (seenValue == 4)
        {
            TextPrinter(5, 46, "*Various lab reagents. Some look unstable.*", 3000);
        }
        // acids
        else if (seenValue == 5)
        {
            TextPrinter(5, 46, "*Strong acids. The container is still intact.*", 3000);
            if (player.inventory[1] == 1 && player.inventory[2] != 1)
            {
                TextPrinter(5, 46, "Always nice *You grab the container*", 3000);
                player.inventory[2] = 1;
            }
        }
        // boxes
        else if (seenValue == 6)
        {
            TextPrinter(5, 46, "*Cardboard boxes filled with paperwork.*", 3000);
        }
        // kits
        else if (seenValue == 7)
        {
            TextPrinter(5, 46, "*Emergency kits. Most are empty.*", 2000);
        }
        // PPE
        else if (seenValue == 8)
        {
            TextPrinter(5, 46, "*Protective gear. Some pieces are missing.*", 3000);
        }
        else if (seenValue == 10)
        {
            TextPrinter(5, 46, "Hes a btch with no loot", 2000);
        }
        // sterile goods
        else if (seenValue == 51)
        {
            TextPrinter(5, 46, "*Sterile supplies sealed in plastic.*", 3000);
        }
        // screwdrivers
        else if (seenValue == 52)
        {
            TextPrinter(5, 46, "*A set of screwdrivers. Still usable.*", 3000);
            if (player.inventory[1] != 1 && player.inventory[6] != 1)
            {
                TextPrinter(5, 46, "Always usefull *You grab it*", 3000);
                player.inventory[6] = 1;
            }
        }
        // wires
        else if (seenValue == 53)
        {
            TextPrinter(5, 46, "*Loose wiring. Insulation is damaged.*", 3000);
        }
        // spare parts
        else if (seenValue == 54)
        {
            TextPrinter(5, 46, "*Mechanical spare parts. Mostly rusted.*", 3000);
        }
        // bio bags
        else if (seenValue == 55)
        {
            TextPrinter(5, 46, "*Biohazard bags. Some are leaking.*", 3000);
        }
        // clamps
        else if (seenValue == 56)
        {
            TextPrinter(5, 46, "*Metal clamps. Some covered in corrosion.*", 3000);
            if (player.inventory[1] != 1 && player.inventory[7] != 1)
            {
                TextPrinter(5, 46, "They look handy *You grab them*", 3000);
                player.inventory[7] = 1;
            }
        }
        // tubes
        else if (seenValue == 57)
        {
            TextPrinter(5, 46, "*Flexible tubing. Brittle with age.*", 2000);
        }
        // masks
        else if (seenValue == 58)
        {
            TextPrinter(5, 46, "*Disposable masks. Most are expired.*", 3000);
        }
        // gloves
        else if (seenValue == 59)
        {
            TextPrinter(5, 46, "*Protective gloves. Still intact.*", 2000);
            if (player.inventory[1] != 1 && player.inventory[5] != 1)
            {
                TextPrinter(5, 46, "Dont want to hurt myself! right? *You equip them*", 4000);
                player.inventory[5] = 1;
            }
        }
        // cold packs
        else if (seenValue == 60)
        {
            TextPrinter(5, 46, "*Cold packs. No longer cold.*", 2000);
        }
        // meds
        else if (seenValue == 61)
        {
            TextPrinter(5, 46, "*Medication. Labels scratched off.*", 2000);
        }
        // vials
        else if (seenValue == 62)
        {
            TextPrinter(5, 46, "*Glass vials filled with unknown liquids.*", 3000);
        }
        // syringes
        else if (seenValue == 63)
        {
            TextPrinter(5, 46, "*Used syringes. Better not touch.*", 3000);
        }
        // sample jar
        else if (seenValue == 64)
        {
            TextPrinter(5, 46, "*A sample jar containing organic residue.*", 3000);
            if (player.inventory[1] == 1 && player.inventory[4] != 1)
            {
                TextPrinter(5, 46, "great for mixing and maybe usefull *You grab it*", 4000);
                player.inventory[4] = 1;
            }
        }
        // cleaning fluids
        else if (seenValue == 65)
        {
            TextPrinter(5, 46, "*Industrial cleaning fluids. Strong smell.*", 3000);
            if (player.inventory[1] == 1 && player.inventory[3] != 1)
            {
                TextPrinter(5, 46, "*You pick it up*", 2000);
                player.inventory[3] = 1;
            }
        }
        // door to the machine room
        else if (seenValue == 66)
        {
            TextPrinter(5, 46, "*You open the door*", 2000);
            PlayerX = 55;
            PlayerY = 29;
            player.area = 4;
            ChangeArea(player, zombies, deadBodies);
        }
        // door to the hallway
        else if (seenValue == 68)
        {
            TextPrinter(5, 46, "*You open the door*", 2000);
            PlayerX = 2;
            PlayerY = 8;
            player.area = 2;
            ChangeArea(player, zombies, deadBodies);
        }
        // breakable pipe
        else if (seenValue == 69)
        {
            if (!(player.inventory[2] == 1 && player.inventory[3] == 1 && player.inventory[4] == 1) 
                || !(player.inventory[5] == 1 && player.inventory[6] == 1 && player.inventory[7] == 1))
            {
                TextPrinter(5, 46, "*A damaged pipe fixed to the wall. Maybe its good as a weapon.*", 4000);
            }

            if (player.inventory[1] == 1)
            {
                if (player.inventory[2] != 1)
                {
                    gotoxy(27, 10);
                    printf("\033[33macids\033[0m");
                }
                if (player.inventory[3] != 1)
                {
                    gotoxy(90, 24);
                    printf("\033[33mcleaning fluids\033[0m");
                }
                if (player.inventory[4] != 1)
                {
                    gotoxy(93, 22);
                    printf("\033[33msample jars\033[0m");
                }
            }
            else
            {
                if (player.inventory[7] != 1)
                {
                    gotoxy(16, 22);
                    printf("\033[33mclamps\033[0m");
                }
                if (player.inventory[5] != 1)
                {
                    gotoxy(28, 24);
                    printf("\033[33mgloves\033[0m");
                }
                if (player.inventory[6] != 1)
                {
                    gotoxy(86, 8);
                    printf("\033[33mscrewdrivers\033[0m");
                }
            }
            if (player.inventory[2] == 1 && player.inventory[3] == 1 && player.inventory[4] == 1)
            {
                TextPrinter(5, 46, "*You broke down the pipe using chemicals*", 3000);
                TextPrinter(5, 46, "*You equiped the pipe*", 2000);
                player.sword = 1;
            }
            if (player.inventory[2] != 1 && player.inventory[5] == 1 && player.inventory[6] == 1 && player.inventory[7] == 1)
            {
                TextPrinter(5, 46, "*You broke down the pipe*", 3000);
                TextPrinter(5, 46, "*You equiped the pipe*", 2000);
                player.sword = 1;
            }
        }

    }
    else if (player.area == 4)
    {
        if (seenValue == 2)
        {
            TextPrinter(5, 46, "Please Hargassner I need this!!!", 3000);
        }
        else if (seenValue == 3)
        {
            if (player.inventory[8] == 1)
            {
                TextPrinter(5, 46, "*The generator starts running*", 3000);
                player.inventory[9] = 1;
                gotoxy(89, 9);
                printf("\033[5;32mo\033[0m");
            }
            else
            {
                TextPrinter(5, 46, "*Generator not running, missing key*", 3000);
            }
        }
        else if (seenValue == 4)
        {
            if (player.inventory[9] == 1)
                TextPrinter(5, 46, "*Control systems are active under emergency power.*", 3000);
            else
                TextPrinter(5, 46, "*The control server appear to be offline.*", 3000);
        }
        else if (seenValue == 5)
        {
            TextPrinter(5, 46, "*You notice this server is used for backups and data storage.*", 3000);
        }
        else if (seenValue == 6)
        {
            TextPrinter(5, 46, "*You open the door*", 2000);
            PlayerX = 55;
            PlayerY = 3;
            player.area = 3;
            ChangeArea(player, zombies, deadBodies);
        }
        else if (seenValue == 7)
        {
            TextPrinter(5, 46, "*VOLVO i need a GOLD GOLD GOLD*", 2000);
        }
    }
    else if (player.area == 5)
    {
        // Woman room
        if (seenValue == 2)
        {
            TextPrinter(5, 46, "DLC needed to unlock the woman's bathroom", 4000);
        }
        //door to the hallway
        else if (seenValue == 3)
        {
            TextPrinter(5, 46, "*You walk through the door*", 2000);
            PlayerX = 35;
            PlayerY = 3;
            player.area = 2;
            ChangeArea(player, zombies, deadBodies);
        }
        // shower
        else if (seenValue == 4)
        {
            TextPrinter(5, 46, "The floor is still a bit Wet", 2000);
        }
        // stalls
        else if (seenValue == 5)
        {
            TextPrinter(5, 46, "Holy SHIT", 2000);
        }
        else if (seenValue == 6)
        {
            TextPrinter(5, 46, "wow almost completly full of piss!", 3000);
        }
        else if (seenValue == 7)
        {
            if (player.inventory[9] == 0)
                TextPrinter(5, 46, "* 3 sinks, water won't come out *", 3000);
            else
                TextPrinter(5, 46, "* 3 sinks, water flows normally", 1000);
        }
    }
    else if (player.area == 6)
    {
        // closed lockers
        if (seenValue == 2)
        {
            TextPrinter(5, 46, "*You can't open this locker*", 2000);
        }
        // bench
        else if (seenValue == 3)
        {
            TextPrinter(5, 46, "*Just a ordinary bench*", 2000);
        }
        // key holder
        else if (seenValue == 4)
        {
            if (player.inventory[8] == 0)
            {
                char input2;
                vector<char> code;
                vector<char> actChar(4);
                actChar[0] = '1';
                actChar[1] = '3';
                actChar[2] = '5';
                actChar[3] = '3';
                gotoxy(5, 46);
                printf("Press esc to exit, Enter Code (numbers only):");
                while (true)
                {
                    if (_kbhit()) {
                        input2 = _getch();

                        if (input2 == 27)
                        {
                            gotoxy(5, 46);
                            printf("                                                  ");
                            break;
                        }
                        code.push_back(input2);

                        gotoxy(50 + code.size(), 46);
                        printf("*");

                        if (code.size() == 4)
                        {
                            if (code == actChar)
                            {
                                gotoxy(5, 46);
                                printf("                                                  ");
                                TextPrinter(5, 46, "*it opens and you acquire a key*", 2000);
                                player.inventory[8] = 1;
                                break;
                            }
                            else
                            {
                                gotoxy(5, 46);
                                printf("                                                  ");
                                TextPrinter(5, 46, "*wrong code buddy*", 1000);
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                TextPrinter(5, 46, "*You already took what was inside*", 2000);
            }
        }
        // sink
        else if (seenValue == 5)
        {
            if (player.inventory[9] == 0)
                TextPrinter(5, 46, "*Water isn't flowing from this sink*", 2000);
            else
                TextPrinter(5, 46, "*Water is flowing from this sink*", 2000);
        }
        // bin
        else if (seenValue == 6)
        {
            TextPrinter(5, 46, "*A bin with a couple of paper towels inside*", 3000);
        }
        // door
        else if (seenValue == 7)
        {
            TextPrinter(5, 46, "*You walk through the door*", 2000);
            PlayerX = 115;
            PlayerY = 3;
            player.area = 2;
            ChangeArea(player, zombies, deadBodies);
        }
        // bottom body
        else if (seenValue == 70)
        {
            TextPrinter(5, 46, "*Well he's dead*", 1000);
        }
        // normal zombie
        else if (seenValue == 10)
        {
            TextPrinter(5, 46, "Hes a btch with no loot", 2000);
        }
        // philips zombie
        else if (seenValue == 11)
        {
            if (player.inventory[11] == 0)
            {
                TextPrinter(5, 46, "*You get the key to philip's locker*", 2000);
                player.inventory[11] = 1;
            }
            else
                TextPrinter(5, 46, "*He had nothing else of value*", 2000);
        }
        // top body
        else if (seenValue == 71)
        {
            TextPrinter(5, 46, "*Don't wish to be him!*", 2000);
        }
        // code locker
        else if (seenValue == 22)
        {
            if (player.inventory[10] == 0)
            {
                TextPrinter(5, 46, "*In the locker are a couple of postit's, on them are numbers*", 4000);
                player.inventory[10] = 1;
            }
            TextPrinter(5, 46, "*c:5; a:1; d:3; b:3*", 4000);
        }
        // phillips secret locker
        else if (seenValue == 23)
        {
            if (player.inventory[11] == 1)
                TextPrinter(5, 46, "*In this locker is: 1 Bottle of lube, 69 different Dildos and an invitation letter from sir mister Epstein*", 5000);
            else
                TextPrinter(5, 46, "*philips locker (key needed)*", 2000);
        }

    }
}

void ChangeArea(Player& player, Zombie zombies[], DeadBody deadBodies[])
{
    int value = 1;
    system("cls");
    gotoxy(PlayerX, PlayerY);
    printf("[\xC2\xB0-\xC2\xB0]");
    int i = 0;
    int k = 0;
    int j = 0;
    // set everything to 0

    for (k = 0; k < ROWS; k++)
    {
        for (i = 0; i < COLS; i++)
        {
            starterArea[k][i] = 0;
        }
    }

    // DeadZombie print
    for (i = 0; i < HowManyZombiesExist; i++)
    {
        if (zombies[i].ZombieArea == player.area)
        {
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

    PrintBodies(deadBodies, player.area);
    


    if (player.area == 1)
    {

        
        //Boarder
        BoxMaker(4, 1, 136, 45, 1, '_');

        gotoxy(12, 4);
        printf("|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|");
        gotoxy(12, 5);
        printf("| [Shelf]         |");
        gotoxy(12, 6);
        printf("| CH4  NH3  O2    |");
        gotoxy(12, 7);
        printf("| HNO3 KOH AcO    |");
        gotoxy(12, 8);
        printf("|-----------------|");
        gotoxy(12, 9);
        printf("| [Cabinet]       |");
        gotoxy(12, 10);
        printf("| Toxins Solvent  |");
        gotoxy(12, 11);
        printf("| EtOH   MeOH     |");
        gotoxy(12, 12);
        printf("|-----------------|");
        gotoxy(12, 13);
        printf("|[Safety Box]     |");
        gotoxy(12, 14);
        printf("| Gloves  Mask    |");
        gotoxy(12, 15);
        printf("|_________________|");

        for (k = 0; k < 12; k++)
        {
            for (i = 0; i < 19; i++)
            {
                starterArea[4 + k][12 + i] = 2;
            }
        }



        //Bed
        gotoxy(49, 19);
        printf("|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯|");
        for (i = 0; i < 27; i++) starterArea[19][49 + i] = 8;

        gotoxy(50, 24);
        printf("_________________________");
        for (i = 0; i < 26; i++) starterArea[24][50 + i] = 8;

        for (int i = 0; i < 5; i++) {
            gotoxy(49, i + 20);
            printf("|");
            starterArea[20 + i][49] = 8;
            gotoxy(75, i + 20);
            printf("|");
            starterArea[20 + i][75] = 8;
            gotoxy(67, i + 20);
            printf("|");
        }
        gotoxy(60, 22);
        printf("BED");


        gotoxy(20, 33);
        printf("|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|");
        for (i = 0; i < 97; i++)
        {
            if ((i + 20) >= 25 && (i + 20) < 33)
            {
                starterArea[33][20 + i] = 5;
            }
            else if ((i + 20) >= 38 && (i + 20) < 45)
            {
                starterArea[33][20 + i] = 3;
            }
            else if ((i + 20) >= 53 && (i + 20) < 65)
            {
                starterArea[33][20 + i] = 4;
            }
            else if ((i + 20) >= 71 && (i + 20) < 83)
            {
                starterArea[33][20 + i] = 6;
            }
            else if ((i + 20) >= 91 && (i + 20) < 100)
            {
                starterArea[33][20 + i] = 11;
            }
            else
            {
                starterArea[33][20 + i] = 1;
            }
        }
        for (int i = 0; i < 8; i++)
        {
            gotoxy(20, 34 + i);
            printf("|");
            starterArea[34 + i][20] = 1;
            gotoxy(116, 34 + i);
            printf("|");
            starterArea[34 + i][116] = 1;
        }
        gotoxy(20, 41);
        printf("|_______________________________________________________________________________________________|");
        for (i = 0; i < 97; i++)
        {
            starterArea[41][20 + i] = 1;
        }

        // Microscope
        gotoxy(26, 34);
        printf("__________");
        gotoxy(25, 35);
        printf("|Microscope|");
        gotoxy(25, 36);
        printf("|__________|");
        gotoxy(25, 37);
        printf("|     /    |");
        gotoxy(25, 38);
        printf("|    / )   |");
        gotoxy(25, 39);
        printf("|  _\033[0;31m_\033[0m_|_   |");
        gotoxy(25, 40);
        printf("|__________|");

        //Laptop
        gotoxy(39, 35);
        printf("|\\_      0~");
        gotoxy(39, 36);
        printf("|  \\______");
        gotoxy(39, 37);
        printf("|    |++++|");
        gotoxy(40, 38);
        printf("\\_  |++++|");
        gotoxy(42, 39);
        printf("\\_|____|");
        gotoxy(42, 40);
        printf("Laptop");

        // Sketches
        gotoxy(54, 35);
        printf("_____________");
        gotoxy(53, 36);
        printf("| #§|&|§&!§~} |");
        gotoxy(53, 37);
        printf("| ||§|&~&§³$/ |");
        gotoxy(53, 38);
        printf("| $|§||~{²§&! |");
        gotoxy(53, 39);
        printf("|_____________|");
        gotoxy(57, 40);
        printf("Sketches");

        //¯

        gotoxy(72, 35);
        printf(",");
        gotoxy(71, 36);
        printf("/(_____________");
        gotoxy(70, 37);
        printf("|  >:===========`");
        gotoxy(71, 38);
        printf(")(     Tools");
        gotoxy(71, 39);
        printf("\"\"");



        gotoxy(90, 37);
        printf("Some other sht");


        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 18; i++) {
            gotoxy(69 + i, 1);
            printf("_");
            starterArea[1][69 + i] = 7;

        }
        setcolor(CONSOLE_WHITE);

    }
    else if (player.area == 2)
    {
        if (player.firstTimeInArea[1] == 0)
        {
            gotoxy(deadBodies[2].posX, deadBodies[2].posY);
            printf("     ");
        }
        // second row changed to 1

        for (i = 1; i < COLS - 1; i++)
        {
            starterArea[2][i] = 1;
            gotoxy(i, 2);
            printf("_");
        }

        // 11the row changed to 1
        for (i = 1; i < COLS - 41; i++)
        {
            starterArea[13][i] = 1;
            gotoxy(i, 13);
            printf("¯");
        }
        // Left Row down 
        for (i = 0; i < 10; i++)
        {
            starterArea[i + 3][1] = 1;
            // door to the lagerraum
            if (i >= 3 && i < 7)
            {
                setcolor(CONSOLE_BROWN);
                starterArea[i + 3][1] = 2;
            }
            else
            {
                setcolor(CONSOLE_WHITE);
            }
            gotoxy(1, i + 3);
            printf("|");
        }
        // Right Row all the way down 
        for (i = 0; i < 29; i++)
        {
            starterArea[i + 3][COLS - 1] = 1;
            gotoxy(COLS - 1, i + 3);
            printf("|");
        }
        // the Row for the Right corner
        for (i = 0; i < 19; i++)
        {
            starterArea[i + 13][COLS - 41] = 1;
            gotoxy(COLS - 41, i + 13);
            printf("|");
        }
        //The door to the exit
        for (i = 0; i < 39; i++)
        {
            if (i > 10 && i < 30)
            {
                setcolor(CONSOLE_BROWN);
                value = 3;
            }
            else
            {
                setcolor(CONSOLE_WHITE);
                value = 1;
            }
            starterArea[32][COLS - 40 + i] = value;
            gotoxy(COLS - 40 + i, 32);
            printf("¯");

        }
        // Door to the lab
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 13; i++) {
            gotoxy(40 + i, 13);
            printf("¯");
            starterArea[13][40 + i] = 4;
        }
        setcolor(CONSOLE_WHITE);
        // Door to the closet

        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 10; i++) {
            gotoxy(112 + i, 2);
            printf("_");
            starterArea[2][112 + i] = 5;

        }
        setcolor(CONSOLE_WHITE);

        // open door
        gotoxy(32, 2);
        printf("          ");
        for (i = 0; i < 10; i++)
        {
            starterArea[2][32 + i] = 6;
        }
        gotoxy(42, 3);
        printf("\\");
        starterArea[3][42] = 1;
        gotoxy(43, 4);
        printf("\\__ ");
        for (i = 0; i < 3; i++)
        {
            starterArea[4][43 + i] = 1;
        }
        gotoxy(46, 5);
        printf("\\");
        starterArea[5][46] = 1;

        // Transporting Bed
        gotoxy(152, 13);
        printf("[\033[0;31m=\033[0m=\033[0;31m=\033[0m=]");
        gotoxy(152, 14);
        printf("| \033[0;31m~~~\033[0m|");
        gotoxy(152, 15);
        printf("\033[0;31m|   ~\033[0m|");
        gotoxy(152, 16);
        printf("o----o");
        for (k = 0; k < 4; k++)
        {
            for (i = 0; i < 6; i++)
            {
                starterArea[13 + k][152 + i] = 8;
            }
        }

        if (player.firstTimeInArea[1] == 1)
        {
            // change the look of the other dead body for next time
            deadBodies[1].bodyPart = "\033[0;31m~/\033[0m-X\033[0;31m]\033[0m";
        }
        
        if (player.firstTimeInArea[1] == 1 && zombies[2].Zombielife > 0)
        {
            gotoxy(126, 4);
            printf("[X-\033[0;31m~~\033[0m");
            for (i = 0; i < 5; i++)
            {
                starterArea[4][126 + i] = 11;
            }

            gotoxy(150, 10);
            printf("[X-X\033[0;31m]\033[0m");
            gotoxy(150, 10);
            setcolor(CONSOLE_RED);
            printf("~/");
            setcolor(CONSOLE_WHITE);
            for (i = 0; i < 5; i++)
            {
                starterArea[10][150] = 12;
            }
            player.firstTimeInArea[1] = 2;

            gotoxy(148, 9);
            printf("\033[0;32m[-\xC2\xB0O\xC2\xB0]-\033[0m");
            Sleep(1000);
            gotoxy(148, 9);
            printf("\033[0;32m[-\xC2\xB0_\xC2\xB0]-\033[0m");
            Sleep(1000);
            zombies[2].ZombieposX = 148;
            zombies[2].ZombieposY = 9;
            zombies[2].Zombiespeed = 5;
            zombies[2].ZombieStartSpeed = 5;
        }

        if (player.firstTimeInArea[1] == 0)
        {

            gotoxy(130, 5);
            printf("Oh my god Help!!!");
            gotoxy(130, 6);
            printf("[\xC2\xB0o\xC2\xB0]");
            gotoxy(131, 9);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");

            Sleep(2000);

            gotoxy(130, 5);
            printf("                 ");
            gotoxy(128, 5);
            printf("[\xC2\xB0-\xC2\xB0]");
            gotoxy(130, 8);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");

            gotoxy(130, 6);
            printf("     ");
            gotoxy(131, 9);
            printf("       ");

            Sleep(500);

            gotoxy(129, 7);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(130, 8);
            printf("       ");

            Sleep(500);

            gotoxy(126, 4);
            printf("[\xC2\xB0-\xC2\xB0]");
            for (i = 0; i < 5; i++)
            {
                starterArea[4][126 + i] = 11;
            }
            gotoxy(128, 6);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(128, 5);
            printf("     ");
            gotoxy(129, 7);
            printf("       ");

            Sleep(500);

            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(128, 6);
            printf("       ");
            gotoxy(126, 3);
            printf("Ahhhhhhhh");
            Sleep(1000);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0O\xC2\xB0-]\033[0m");
            gotoxy(130, 4);
            setcolor(CONSOLE_RED);
            printf("~");
            setcolor(CONSOLE_WHITE);
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0-\xC2\xB0-]\033[0m");
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0O\xC2\xB0-]\033[0m");
            gotoxy(129, 4);
            setcolor(CONSOLE_RED);
            printf("~");
            setcolor(CONSOLE_WHITE);
            gotoxy(126, 4);
            printf("[X-");
            gotoxy(126, 3);
            printf("         ");
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            Sleep(500);
            gotoxy(127, 5);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            Sleep(500);
            gotoxy(126, 6);
            printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
            gotoxy(127, 5);
            printf("       ");
            Sleep(100);
            gotoxy(126, 6);
            printf("       ");
            player.firstTimeInArea[1] = 1;

            deadBodies[2].bodyPart = "[X-\033[0;31m~~\033[0m";

            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        }
    }
    else if (player.area == 3)
    {
        // äußere box
        BoxMaker(1, 2, 120, 30, 1, '_');

        BoxMaker(12, 7, 37, 11, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // chem bottles
                if (i < 16 && k < 2) value = 2;
                // drums
                else if (i > 16 && k < 2) value = 3;
                // reagents
                else if (i < 13 && k > 2) value = 4;
                // acids
                else if (i > 13 && k > 2) value = 5;
                else value = 1;

                starterArea[k + 7][i + 12] = value;
            }
        }
        BoxMaker(49, 7, 71, 11, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 23; i++)
            {
                // boxes
                if (i < 9 && k < 2) value = 6;
                // Kits
                else if (i > 9 && i < 16 && k < 2) value = 7;
                // PPE
                else if (i > 16 && k > 2) value = 8;
                // sterile goods
                else if (k > 2) value = 51;
                else value = 1;
                starterArea[k + 7][i + 49] = value;
            }
        }
        BoxMaker(83, 7, 108, 11, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // screwdrivers
                if (i < 17 && k < 2) value = 52;
                // Wires
                else if (i > 17 && k < 2) value = 53;
                // spare parts
                else if (i < 14 && k > 2) value = 54;
                // bio bags
                else if (i > 14 && k > 2) value = 55;
                else value = 1;
                starterArea[k + 7][i + 83] = value;
            }
        }
        BoxMaker(12, 21, 37, 25, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // clamps
                if (i < 13 && k < 2) value = 56;
                // tubes
                else if (i > 13 && k < 2) value = 57;
                // masks
                else if (i < 12 && k > 2) value = 58;
                // gloves
                else if (i > 12 && k > 2) value = 59;
                else value = 1;
                starterArea[k + 21][i + 12] = value;
            }
        }
        BoxMaker(49, 21, 74, 25, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 26; i++)
            {
                // cold packs
                if (i < 15 && k < 2) value = 60;
                // meds
                else if (i > 15 && k < 2) value = 61;
                // vials
                else if (i < 10 && k > 2) value = 62;
                // syringes
                else if (i > 10 && k > 2) value = 63;
                else value = 1;
                starterArea[k + 21][i + 49] = value;
            }
        }
        BoxMaker(86, 21, 109, 25, 1, '#');
        for (k = 0; k < 5; k++)
        {
            for (i = 0; i < 24; i++)
            {
                // sample jar
                if (k < 2) value = 64;
                // cleaning fluids
                else if (k > 2) value = 65;
                else value = 1;
                starterArea[k + 21][i + 86] = value;
            }
        }
        i < 10 ? i : -1;

        //box 1:
        gotoxy(13, 8);
        printf("  chem bottles | drums  ");
        gotoxy(13, 9);
        printf("------------------------");
        gotoxy(13, 10);
        printf("   reagents | acids     ");

        // box 2:
        gotoxy(50, 8);
        printf("  boxes | kits | PPE ");
        gotoxy(50, 9);
        printf("---------------------");
        gotoxy(50, 10);
        printf("   sterile goods     ");

        // box 3:
        gotoxy(84, 8);
        printf("  screwdrivers  | wires ");
        gotoxy(84, 9);
        printf("------------------------");
        gotoxy(84, 10);
        printf(" spare parts | bio bags ");

        // box 4:
        gotoxy(13, 22);
        printf("   clamps   |   tubes   ");
        gotoxy(13, 23);
        printf("------------------------");
        gotoxy(13, 24);
        printf("   masks   |   gloves   ");

        // box 5:
        gotoxy(50, 22);
        printf("   cold packs |  meds   ");
        gotoxy(50, 23);
        printf("------------------------");
        gotoxy(50, 24);
        printf("  vials  |   syringes   ");

        // box 6:
        gotoxy(87, 22);
        printf("      sample jars     ");
        gotoxy(87, 23);
        printf("----------------------");
        gotoxy(87, 24);
        printf("   cleaning fluids    ");


        //door to the mashine room
        for (i = 0; i < 10; i++)
        {
            gotoxy(52 + i, 2);
            printf(" ");
            starterArea[2][52 + i] = 66;
        }

        // door to the hallway
        for (i = 0; i < 5; i++)
        {
            gotoxy(120, 14 + i);
            printf(" ");
            starterArea[14 + i][120] = 68;
        }

        // breakable pipe
        for (i = 0; i < 23; i++)
        {

            gotoxy(2 + i, 30);
            printf("\033[33m=\033[0m");
            starterArea[30][2 + i] = 69;
        }
    }
    else if (player.area == 4)
    {
        // Äußere box
        BoxMaker(12, 2, 102, 30, 1, '_');

        // boiler  2  // Volvo 7
        gotoxy(23, 5);
        printf("  |¯¯¯¯¯¯¯¯|     |¯¯¯¯¯¯¯¯| ");
        for (i = 0; i < 10; i++)
        {
            starterArea[5][25 + i] = 7;
            starterArea[5][40 + i] = 2;
        }
        gotoxy(23, 6);
        printf("  |        |     |        | ");
        for (i = 0; i < 10; i++)
        {
            starterArea[6][25 + i] = 7;
            starterArea[6][40 + i] = 2;
        }
        gotoxy(23, 7);
        printf("  |  VALVE |=====| GAUGE  | ");
        for (i = 0; i < 25; i++)
        {
            if (i < 15)
                starterArea[7][25 + i] = 7;
            else
                starterArea[7][25 + i] = 2;
        }
        gotoxy(23, 8);
        printf("  |________|     |________| ");
        for (i = 0; i < 10; i++)
        {
            starterArea[8][25 + i] = 7;
            starterArea[8][40 + i] = 2;
        }
        gotoxy(23, 9);
        printf("    |||||  BOILER   |||||   ");
        for (i = 0; i < 21; i++)
        {
            starterArea[9][27 + i] = 2;
        }
        gotoxy(23, 10);
        printf("    |||||           |||||   ");
        for (i = 0; i < 21; i++)
        {
            starterArea[10][27 + i] = 2;
        }
        gotoxy(23, 11);
        printf("|¯¯¯|||||¯¯¯¯¯¯¯¯¯¯¯|||||¯¯¯|");
        for (i = 0; i < 29; i++)
        {
            starterArea[11][23 + i] = 2;
        }
        gotoxy(23, 12);
        printf("|         HEAT CORE         |");
        for (i = 0; i < 29; i++)
        {
            starterArea[12][23 + i] = 2;
        }
        gotoxy(23, 13);
        printf("|___________________________|");
        for (i = 0; i < 29; i++)
        {
            starterArea[13][23 + i] = 2;
        }


        // Emergency Generator 3
        gotoxy(64, 5);
        printf("|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|");
        gotoxy(64, 6);
        printf("|     EMERGENCY GENERATOR     |");
        gotoxy(64, 7);
        printf("|  _________      ________    |");
        gotoxy(64, 8);
        printf("|  |        |====| START  |   |");
        if (player.inventory[9] == 0)
        {
            gotoxy(64, 9);
            printf("|  | ENGINE |    | PANEL \033[5;31mo\033[0m|   |");
        }
        else
        {
            gotoxy(64, 9);
            printf("|  | ENGINE |    | PANEL \033[5;32mo\033[0m|   |");
        }
        gotoxy(64, 10);
        printf("|  |  ||||  |    |________|   |");
        gotoxy(64, 11);
        printf("|  |  ||||  |        ||       |");
        gotoxy(64, 12);
        printf("|__|________|________||_______|");
        for (k = 0; k < 8; k++)
        {
            for (i = 0; i < 31; i++)
            {
                starterArea[5 + k][64 + i] = 3;
            }
        }
        



        // Serverbox1 4
        gotoxy(20, 19);
        printf("/¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯/|");
        gotoxy(19, 20);
        printf("/_____________________/ |");
        gotoxy(18, 21);
        printf("|  [ UPS ]   ||||||   |  |");
        gotoxy(18, 22);
        printf("|============||||||===|  |");
        gotoxy(18, 23);
        printf("|  [ SBS ]   ||||||   |  |");
        gotoxy(18, 24);
        printf("|============||||||===|  |");
        gotoxy(18, 25);
        printf("|  [ CTRL ]  ||||||   |  |");
        gotoxy(18, 26);
        printf("|============||||||===|  |");
        gotoxy(18, 27);
        printf("|  [ NET ]   ||||||   | /");
        gotoxy(18, 28);
        printf("|_____________________|/");

        // Serverbox2 5
        gotoxy(74, 19);
        printf("/¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯/|");
        gotoxy(73, 20);
        printf("/_____________________/ |");
        gotoxy(72, 21);
        printf("|  [ UPS ]   ||||||   |  |");
        gotoxy(72, 22);
        printf("|============||||||===|  |");
        gotoxy(72, 23);
        printf("|  [ BACK ]  ||||||   |  |");
        gotoxy(72, 24);
        printf("|============||||||===|  |");
        gotoxy(72, 25);
        printf("|  [ HDD ]   [][][]   |  |");
        gotoxy(72, 26);
        printf("|============||||||===|  |");
        gotoxy(72, 27);
        printf("|  [ NET ]   ||||||   | /");
        gotoxy(72, 28);
        printf("|_____________________|/");

        for (k = 0; k < 10; k++)
        {
            for (i = 0; i < 26; i++)
            {
                starterArea[19 + k][18 + i] = 4;
                starterArea[19 + k][72 + i] = 5;
            }
        }
        starterArea[19][18] = 0;
        starterArea[19][19] = 0;
        starterArea[20][18] = 0;
        starterArea[27][43] = 0;
        starterArea[28][42] = 0;
        starterArea[28][43] = 0;



        starterArea[19][72] = 0;
        starterArea[19][73] = 0;
        starterArea[19][96] = 0;
        starterArea[20][72] = 0;
        starterArea[28][96] = 0;




        //door to the lagerraum 6
        gotoxy(52, 30);
        printf("          ");

        for (i = 0; i < 10; i++)
        {
            starterArea[30][52 + i] = 6;
        }






    }
    else if (player.area == 5)
    {
        

        // Box bottom left
        BoxMaker(5, 17, 21, 30, 1, '_');

        // fix one broken character
        gotoxy(5, 17);
        printf("|");

        // door for mens and womans room
        setcolor(CONSOLE_BROWN);
        for (i = 0; i < 5; i++)
        {
            // woman 2 
            gotoxy(5, 20 + i);
            printf("|");
            starterArea[20 + i][5] = 2;
            // men 3 
            gotoxy(21, 20 + i);
            printf(" ");
            starterArea[20 + i][21] = 0;
        }

        // door to the hallway 3
        for (i = 0; i < 9; i++)
        {
            gotoxy(9 + i, 30);
            printf(" ");
            starterArea[30][9 + i] = 3;
        }

        setcolor(CONSOLE_WHITE);

        // shower 4
        for (i = 0; i < 3; i++)
        {
            gotoxy(6, 2 + (5 * i));
            printf("---------------");
            for (k = 0; k < 15; k++)
            {
                starterArea[2 + (5 * i)][6 + k] = 1;
            }
            gotoxy(10, 3 + (5 * i));
            printf("shower");
            for (k = 0; k < 6; k++)
            {
                starterArea[3 + (5 * i)][10 + k] = 4;
            }
            gotoxy(7, 4 + (5 * i));
            printf("/'");
            starterArea[4 + (5 * i)][7] = 4;
            starterArea[4 + (5 * i)][8] = 4;
            gotoxy(6, 5 + (5 * i));
            printf("o ''");
            starterArea[5 + (5 * i)][7] = 4;
            starterArea[5 + (5 * i)][8] = 4;
            starterArea[5 + (5 * i)][9] = 4;
            gotoxy(8, 6 + (5 * i));
            printf("'~'");
            starterArea[6 + (5 * i)][8] = 4;
            starterArea[6 + (5 * i)][9] = 4;
            starterArea[6 + (5 * i)][10] = 4;
        }

        // outer box
        BoxMaker(5, 2, 70, 30, 1, '_');

        // stalls 5

        gotoxy(37, 3);
        printf("| /_____/  | /_____/  | /_____/");
        gotoxy(37, 4);
        printf("| |  O  |  | |  O  |  | |  O  |");
        gotoxy(37, 5);
        printf("| |     |  | |     |  | |     |");
        gotoxy(37, 6);
        printf("|  \\___/   |  \\___/   |  \\___/");
        gotoxy(37, 7);
        printf("|__________|__________|");

        for (i = 0; i < 4; i++)
        {
            for (k = 0; k < 31; k++)
                starterArea[3 + i][37 + k] = 5;
        }

        // small fixes
        for (i = 0; i < 23; i++)
            starterArea[7][37 + i] = 5;

        starterArea[6][67] = 0;

        gotoxy(60, 8);
        printf("\\");
        starterArea[8][60] = 1;
        gotoxy(61, 9);
        printf("|");
        starterArea[9][61] = 1;
        gotoxy(61, 10);
        printf("|");
        starterArea[10][61] = 1;


        // pissuars 6
        for (i = 0; i < 2; i++)
        {
            gotoxy(65, 13 + (4 * i));
            printf("-----");
            for (k = 0; k < 5; k++)
            {
                starterArea[13 + (4 * i)][65 + k] = 1;
            }
            gotoxy(67, 14 + (4 * i));
            printf("/¯¯");
            starterArea[14 + (4 * i)][67] = 6;
            starterArea[14 + (4 * i)][68] = 6;
            starterArea[14 + (4 * i)][69] = 6;

            gotoxy(67, 15 + (4 * i));
            printf("| O");
            starterArea[15 + (4 * i)][67] = 6;
            starterArea[15 + (4 * i)][68] = 6;
            starterArea[15 + (4 * i)][69] = 6;

            gotoxy(67, 16 + (4 * i));
            printf("\\__");
            starterArea[16 + (4 * i)][67] = 6;
            starterArea[16 + (4 * i)][68] = 6;
            starterArea[16 + (4 * i)][69] = 6;

            gotoxy(65, 17 + (4 * i));
            printf("-----");
            for (k = 0; k < 5; k++)
            {
                starterArea[17 + (4 * i)][65 + k] = 1;
            }
        }

        // sink 7
        gotoxy(34, 26);
        printf("|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|");
        gotoxy(34, 27);
        printf("|  ___     ___     ___  |");
        gotoxy(34, 28);
        printf("| |___|   |___|   |___| |");
        gotoxy(34, 29);
        printf("|   |       |       |   |");

        for (i = 0; i < 3; i++)
        {
            for (k = 0; k < 25; k++)
                starterArea[26 + i][34 + k] = 7;
        }

        
    }
    else if (player.area == 6)
    {
        // outer box
        BoxMaker(5, 2, 95, 30, 1, '_');

        //locker (empty 2)
        for (i = 0; i < 2; i++)
        {
            for (k = 0; k < 2; k++)
            {
                for (j = 0; j < 5; j++)
                {
                    gotoxy(i * 45 + k * 37 + 5, j * 3 + 6);
                    printf("|¯¯¯¯¯¯|");
                    gotoxy(i * 45 + k * 37 + 5, j * 3 + 6 + 1);
                    printf("|      |");
                    gotoxy(i * 45 + k * 37 + 5, j * 3 + 6 + 2);
                    printf("|      |");
                    for (int m = 0; m < 3; m++)
                        for (int n = 0; n < 8; n++)
                            starterArea[j * 3 + 6 + m][i * 45 + k * 37 + 5 + n] = 2;
                    gotoxy(i * 45 + k * 37 + 10 - ((k % 2) * 3), j * 3 + 6 + 2);
                    printf("o");
                }
                gotoxy(i * 45 + k * 37 + 6, (j - 1) * 3 + 6 + 3);
                printf("¯¯¯¯¯¯");
                for (int n = 0; n < 6; n++)
                    starterArea[(j - 1) * 3 + 6 + 3][i * 45 + k * 37 + 6 + n] = 2;
            }
        }


        //benches 3
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 14; j++)
            {
                gotoxy(i * 45 + 23, j + 7);
                printf("|   |   |");
                for (int m = 0; m < 9; m++)
                    starterArea[j + 7][i * 45 + 23 + m] = 3;
            }
            gotoxy(i * 45 + 23, 6);
            printf("|¯¯¯¯¯¯¯|");
            for (int m = 0; m < 9; m++)
                starterArea[6][i * 45 + 23 + m] = 3;
            gotoxy(i * 45 + 24, j + 7);
            printf("¯¯¯¯¯¯¯");
            for (int m = 0; m < 7; m++)
                starterArea[j + 7][i * 45 + 24 + m] = 3;
        }


        //keyholder 4
        setcolor(CONSOLE_BROWN);
        gotoxy(32, 29);
        printf("|¯¯|");
        setcolor(CONSOLE_WHITE);
        for (i = 0; i < 4; i++)
            starterArea[29][32 + i] = 4;


        // sink 5
        gotoxy(90, 27);
        printf("|¯¯¯¯");
        gotoxy(90, 28);
        printf("|  o ");
        gotoxy(90, 29);
        printf("|____");
        for (i = 0; i < 3; i++)
            for (j = 0; j < 5; j++)
                starterArea[i + 27][j + 90] = 5;

        // bin 6
        gotoxy(91, 24);
        printf("__");
        starterArea[24][91] = 6;
        starterArea[24][92] = 6;
        gotoxy(90, 25);
        printf("|  |");
        for (i = 0; i < 4; i++)
            starterArea[25][90 + i] = 6;
        gotoxy(91, 26);
        printf("¯¯");
        starterArea[26][91] = 6;
        starterArea[26][92] = 6;

        // door 7
        setcolor(CONSOLE_BROWN);
        gotoxy(44, 30);
        printf("¯¯¯¯¯¯¯¯¯¯");
        for (i = 0; i < 10; i++)
            starterArea[30][44 + i] = 7;
        setcolor(CONSOLE_WHITE);


        // special locker 22
        setcolor(CONSOLE_BROWN);
        gotoxy(50, 6);
        printf("|¯¯¯¯¯¯|");
        gotoxy(50, 7);
        printf("|      |");
        gotoxy(50, 8);
        printf("|    o |");
        gotoxy(51, 9);
        printf("¯¯¯¯¯¯");
        setcolor(CONSOLE_WHITE);
        for (int m = 0; m < 4; m++)
            for (int n = 0; n < 8; n++)
                starterArea[6 + m][50 + n] = 22;


        // secret locker 23
        for (int m = 0; m < 4; m++)
            for (int n = 0; n < 8; n++)
                starterArea[15 + m][5 + n] = 23;


        // special 

        // left locker
        gotoxy(12, 15);
        printf("\033[0;31m|\033[0m");
        gotoxy(12, 16);
        printf("\033[0;31m|\033[0m");

        // left bench
        gotoxy(29, 13);
        printf("\033[2;31;101m\033[7;31m  \033[0m\033[0;31m|~~\033[0m");
        starterArea[13][32] = 1;
        starterArea[13][33] = 1;
        gotoxy(29, 14);
        printf("\033[2;31;101m\033[7;31m  \033[0m\033[0;31m|~\033[0m");
        starterArea[14][32] = 1;
        gotoxy(30, 15);
        printf("\033[2;31;101m\033[7;31m \033[0m");
        gotoxy(31, 16);
        printf("\033[0;31m|\033[0m");


        // 2cond locker row
        gotoxy(42, 19);
        printf("\033[0;31m|\033[0m");
        gotoxy(41, 20);
        printf("\033[0;31m~|\033[0m\033[2;31;101m\033[7;31m \033[0m");
        starterArea[20][41] = 1;
        gotoxy(42, 21);
        printf("\033[0;31m~\033[0m¯\033[0;31m¯¯¯\033[0m");
        starterArea[21][42] = 1;

        // upper 3d locker row
        gotoxy(52, 6);
        printf("\033[0;31m¯¯¯\033[0m");
        gotoxy(57, 10);
        printf("\033[0;31m|\033[0m");
        gotoxy(57, 11);
        printf("\033[0;31m|~\033[0m");
        starterArea[11][58] = 1;


        // 2cond bench
        gotoxy(68, 17);
        printf("\033[2;31m|\033[7;31m   \033[0m");
        gotoxy(68, 18);
        printf("\033[2;31m| \033[7;31m \033[0m");
        gotoxy(69, 19);
        printf("\033[2;31m\033[7;31m  \033[0m");
    }
    else if (player.area == 7)
    {
        // outer box
        BoxMaker(5, 2, 113, 36, 1, '_');

        // table 2
        gotoxy(42, 6);
        printf("|¯¯¯¯¯¯¯¯|              |¯¯¯¯¯¯¯¯|");
        gotoxy(42, 7);
        printf("|        |              |        |");
        gotoxy(42, 8);
        printf("|         ¯¯¯¯¯¯¯¯¯¯¯¯¯¯         |");
        gotoxy(42, 9);
        printf("|                                |");
        gotoxy(42, 10);
        printf("|________________________________|");

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 34; j++)
            {
                if (!(i < 2 && j > 9 && j < 24))
                {
                    starterArea[i + 6][j + 42] = 2;
                }
            }
        }

        // couch 3

        for (int i = 0; i < 6; i++)
        {
            gotoxy(6, 26 + i);
            printf("|          |");
            for (int j = 0; j < 12; j++)
            {
                starterArea[26 + i][6 + j] = 3;
            }
        }
        gotoxy(7, 26);
        printf("¯¯¯¯¯¯¯¯¯¯");


        for (int i = 0; i < 4; i++)
        {
            gotoxy(6 + j, 32 + i);
            printf("|                                  |");
            for (int j = 0; j < 36; j++)
            {
                starterArea[32 + i][6 + j] = 3;
            }
        }
        gotoxy(17, 32);
        printf("¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
        gotoxy(7, 35);
        printf("__________________________________");



        // exit door 4
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 20; i++)
        {
            gotoxy(50 + i, 36);
            printf("¯");
            starterArea[36][50 + i] = 4;
        }
        setcolor(CONSOLE_WHITE);


        // door to the hallway 5
        setcolor(CONSOLE_BROWN);
        for (int i = 0; i < 20; i++)
        {
            gotoxy(85 + i, 2);
            printf("_");
            starterArea[2][85 + i] = 5;
        }
        setcolor(CONSOLE_WHITE);

        gotoxy(73, 10);
        printf("\033[2;31;101m\033[7;31m__|\033[0m\033[0;31m\033[0m");

        gotoxy(17, 29);
        printf("\033[7;31m|\033[0m\033[0;31m\033[0m");

        gotoxy(35, 32);
        printf("\033[2;31;101m\033[7;31m¯¯¯¯\033[0m\033[0;31m\033[0m");

    }
}

//____________________________________________________________________________________________________________
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                    |¯¯¯¯¯¯¯¯|              |¯¯¯¯¯¯¯¯|                                     |
//|                                    |        |              |        |                                     |
//|                                    |         ¯¯¯¯¯¯¯¯¯¯¯¯¯¯         |                                     |
//|                                    |                                |                                     |
//|                                    |________________________________|                                     |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|          /oX]                                                                                             |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                       [Xo~                |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                               ~~X]        |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//|                                                                                                           |
//| |¯¯¯¯¯¯¯¯¯¯|                                                                                              |
//| |          |        Boss                                                                                  |
//| |          |       [x-\                                                                                   |
//| |          |                                                                                              |
//| |          |                                                                                              |
//| |          |                                                                                              |
//| |          ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|                                                                      |
//| |                                  |                                                                      |
//| |                                  |                                                                      |
//| |__________________________________|                                                                      |
//|____________________________________________                    ___________________________________________|


void BoxMaker( int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int value, char zeichen)
{
    int i;
    char forY = ' ';

    if (zeichen == '_')
    {
        forY = '|';
    }
    else if (zeichen == '#')
    {
        forY = '#';
    }

    for (i = topLeftX; i <= bottomRightX; i++)
    {
        if (zeichen == '_')
        {
            gotoxy(i, topLeftY);
            printf("_");
            starterArea[topLeftY][i] = value;


            gotoxy(i, bottomRightY);
            printf("¯");
            starterArea[bottomRightY][i] = value;
        }
        else
        {
            gotoxy(i, topLeftY);
            printf("#");
            starterArea[topLeftY][i] = value;


            gotoxy(i, bottomRightY);
            printf("#");
            starterArea[bottomRightY][i] = value;
        }
    }

    for (i = topLeftY + 1; i < bottomRightY; i++)
    {

        gotoxy(topLeftX, i);
        printf("%c", forY);
        starterArea[i][topLeftX] = value;

        gotoxy(bottomRightX, i);
        printf("%c", forY);
        starterArea[i][bottomRightX] = value;
    }
}

void TextPrinter(int x, int y, char* text, int time)
{
    int i;
    gotoxy(5, 46);
    printf("                     ");
    gotoxy(x, y);
    printf("%s", text);
    Sleep(time);
    for (i = 0; text[i] != NULL; i++)
    {
        gotoxy(x + i, y);
        printf(" ");
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
