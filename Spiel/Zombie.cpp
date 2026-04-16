#include <stdio.h>
#include <assert.h>
#include <set>
#include <cfloat>
#include <stack>
#include "Zombie.h"
#include "Map_Array.h"
#include "GameFunctions.h"


Zombie::Zombie(int posX, int posY, int lives, int armor, int damage, int startspeed, int speed, int waitfornextzombiemove, int size, int zombieDeathValue, int zombieAreaSpawn)
{
    Zombielives = lives;
    ZombieArmor = armor;
    Zombiedamage = damage;
    ZombieStartSpeed = startspeed;
    Zombiespeed = speed;
    ZombieposX = posX;
    ZombieposY = posY;
    ZombieSize = size;
    ZombieDeathValue = zombieDeathValue;
    waitForNextZombieMove = waitfornextzombiemove;
    ZombieArea = zombieAreaSpawn;

    src = make_pair(ZombieposY, ZombieposX);
}
// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) &&
        (row < ROWS) &&
        (col >= 0) &&
        (col < COLS);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(char starterArea[][COLS], int row, int col, Pair src, int directionX, int directionY)
{
    bool result = true;
    if (row == src.first + directionY && col == src.second + directionX) {
        result = ((starterArea[row][col] == 0 || starterArea[row][col] == 9) &&
            (starterArea[row][col + 1] == 0 || starterArea[row][col + 1] == 9) &&
            (starterArea[row][col + 2] == 0 || starterArea[row][col + 2] == 9) &&
            (starterArea[row][col + 3] == 0 || starterArea[row][col + 3] == 9) &&
            (starterArea[row][col + 4] == 0 || starterArea[row][col + 4] == 9) &&
            (starterArea[row][col + 5] == 0 || starterArea[row][col + 5] == 9) &&
            (starterArea[row][col + 6] == 0 || starterArea[row][col + 6] == 9));
    }
    else {
        result = ((starterArea[row][col] == 0 || starterArea[row][col] == 9) &&
            (starterArea[row][col + 1] == 0 || starterArea[row][col + 1] == 9) &&
            (starterArea[row][col + 2] == 0 || starterArea[row][col + 2] == 9) &&
            (starterArea[row][col + 3] == 0 || starterArea[row][col + 3] == 9) &&
            (starterArea[row][col + 4] == 0 || starterArea[row][col + 4] == 9) &&
            (starterArea[row][col + 5] == 0 || starterArea[row][col + 5] == 9));
    }

    //printf("Checking Cell (%d, %d) -> %s\n", row, col, result ? "Open" : "Blocked");
    return result;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, int destY, int destX) {
    int i;
    //for ( i = 0; i < 5; i++)
    //{

    if (row == destY && col == destX)
    {
        //printf("Checking: row=%d, col=%d, dest=(%d, %d)\n", row, col, dest.first, dest.second);
        //printf("Destination reached!\n");
        return true;
    }
    //}
    //printf("Checking: row=%d, col=%d, i = %d dest=(%d, %d)\n", row, col, i, dest.first, dest.second);
    //printf("Not a destination.\n");
    return false;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}

// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COLS], int row, int col, int& ZombieposX, int& ZombieposY, int& Zombiespeed, int& waitForNextZombieMove, bool& ZombieXMove)
{
    //int row = destY;
    //int col = destX;
    int XChange = 0;
    int YChange = 0;
    stack<Pair> Path;

    if (cellDetails[row][col].parent_i == -1 && cellDetails[row][col].parent_j == -1) {
        //printf("Processing Cell: (%d, %d) -> f: %.2f, g: %.2f, h: %.2f\n", row, col, cellDetails[row][col].f, cellDetails[row][col].g, cellDetails[row][col].h);

        //return;
    }
    // Reconstruct the path
    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
        //printf("z");
    }
    Path.push(make_pair(row, col)); // Push the starting position

    // Find the first move after the start position
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();

        // If this is the first move after the start, update Zombie position
        if (!(p.first == ZombieposY && p.second == ZombieposX))
        {
            if (ZombieposX - p.second < -1)
            {
                XChange--;
                ZombieposX++;

            }
            else
            {
                XChange = ZombieposX - p.second;
                ZombieposX = p.second;
            }
            YChange = ZombieposY - p.first;
            ZombieposY = p.first;
            break;  // Exit loop after finding the first move

        }
    }
    if (XChange != 0)
        ZombieXMove = true;
    else
        ZombieXMove = false;
    // Move the zombie to the new position

    gotoxy(ZombieposX + XChange, ZombieposY + YChange);
    printf("       ");
    gotoxy(ZombieposX, ZombieposY);
    if (XChange <= 0)
    {
        // rechtsschauend
        printf("\033[0;32m[-\xC2\xB0_\xC2\xB0]-\033[0m");
    }
    else
    {
        printf("\033[0;32m-[\xC2\xB0_\xC2\xB0-]\033[0m");
    }
    waitForNextZombieMove = Zombiespeed / (1 + ZombieXMove);
}


void Zombie::CloseRangeMovement(char starterArea[][COLS], Pair src, Pair dest, int& waitForNextZombieMove, int& win, bool& ZombieXMove, int ZombieDeathValue)
{
    int randomNumber;


    bool hittingWall = false;

    //check if the Zombie hasnt got vision
    if (VisionCheck(ZombieposX, ZombieposY, PlayerX, PlayerY, starterArea, ZombieDeathValue, 9))
    {
        randomNumber = rand() % 4;

        if (randomNumber == 0)
        {
            for (int i = 0; i < ZombieSize; i++)
            {
                if (starterArea[ZombieposY - 1][ZombieposX + i] == 0 || starterArea[ZombieposY - 1][ZombieposX + i] == 9)
                {

                }
                else
                {
                    hittingWall = true;
                    break;
                }
            }
            if (!hittingWall)
            {
                ZombieposY--;
                gotoxy(ZombieposX, ZombieposY + 1);
                printf("       ");

            }
        }
        else if (randomNumber == 1)
        {
            for (int i = 0; i < ZombieSize; i++)
            {
                if (starterArea[ZombieposY][ZombieposX - 1 + i] == 0 || starterArea[ZombieposY][ZombieposX - 1 + i] == 9)
                {

                }
                else
                {
                    hittingWall = true;
                    break;
                }
            }
            if (!hittingWall)
            {
                ZombieposX--;
                gotoxy(ZombieposX + 7, ZombieposY);
                printf(" ");
            }
        }
        else if (randomNumber == 2)
        {
            for (int i = 0; i < ZombieSize; i++)
            {
                if (starterArea[ZombieposY + 1][ZombieposX + i] == 0 || starterArea[ZombieposY + 1][ZombieposX + i] == 9)
                {

                }
                else
                {
                    hittingWall = true;
                    break;
                }
            }
            if (!hittingWall)
            {
                ZombieposY++;
                gotoxy(ZombieposX, ZombieposY - 1);
                printf("       ");
            }
        }
        else
        {
            for (int i = 0; i < ZombieSize; i++)
            {
                if (starterArea[ZombieposY][ZombieposX + i + 1] == 0 || starterArea[ZombieposY][ZombieposX + i + 1] == 9)
                {

                }
                else
                {
                    hittingWall = true;
                    break;
                }
            }
            if (!hittingWall)
            {
                ZombieposX++;
                gotoxy(ZombieposX - 1, ZombieposY);
                printf(" ");
            }
        }
        gotoxy(ZombieposX, ZombieposY);
        printf("\033[0;32m[-\xC2\xB0_\xC2\xB0]-\033[0m");
        Zombiespeed = ZombieStartSpeed * 4;
        waitForNextZombieMove = Zombiespeed;
        return;
    }

    Zombiespeed = ZombieStartSpeed;
    // If the source is out of range
    if (!isValid(src.first, src.second)) {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == false) {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked so the point of dest and src is a blocking unit
    if (isUnBlocked(starterArea, src.first, src.second, src, 0, 0) == false || isUnBlocked(starterArea, dest.first, dest.second, src, 0, 0) == false) {
        //printf("Source or the destination is blocked\n");
        if (isUnBlocked(starterArea, src.first, src.second, src, 0, 0) == false || isUnBlocked(starterArea, dest.first, dest.second - 1, src, -1, 0) == false)
        {
            //printf("Source or the destination is blocked\n");
            return;
        }
    }

    // If the destination cell is the same as source cell

    for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
    {
        for (int g = 0; g <= PlayerSize; g++)
        {
            if (isDestination(src.first, src.second + c, dest.first, dest.second + g))
            {
                win = 2;
                return;
            }
        }
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[ROWS][COLS];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell
    cell cellDetails[ROWS][COLS];

    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
    set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();
        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/

         // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j)) {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i - 1, j + c, dest.first, dest.second + g)) {
                        // Set the Parent of the destination cell
                        //printf("f");
                        cellDetails[i - 1][j + c].parent_i = i;
                        cellDetails[i - 1][j + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i - 1][j] && isUnBlocked(starterArea, i - 1, j, src, 0, -1)) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j)) {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i + 1, j + c, dest.first, dest.second + g)) {
                        //printf("d");
                        // Set the Parent of the destination cell
                        cellDetails[i + 1][j + c].parent_i = i;
                        cellDetails[i + 1][j + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i + 1][j] && isUnBlocked(starterArea, i + 1, j, src, 0, 1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j + 1)) {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i, j + 1 + c, dest.first, dest.second + g)) {
                        // Set the Parent of the destination cell
                        //printf("s");
                        cellDetails[i][j + 1 + c].parent_i = i;
                        cellDetails[i][j + 1 + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i][j + 1] && isUnBlocked(starterArea, i, j + 1, src, 1, 0))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j + 1)));

                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j - 1)) {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i, j - 1 + c, dest.first, dest.second + g)) {
                        // Set the Parent of the destination cell
                        //printf("a");
                        cellDetails[i][j - 1 + c].parent_i = i;
                        cellDetails[i][j - 1 + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i][j - 1] && isUnBlocked(starterArea, i, j - 1, src, -1, 0))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        //----------- 5th Successor (North-East)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1)) {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i - 1, j + 1 + c, dest.first, dest.second))
                    {
                        // Set the Parent of the destination cell
                        //printf("q");
                        cellDetails[i - 1][j + 1 + c].parent_i = i;
                        cellDetails[i - 1][j + 1 + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i - 1][j + 1] && isUnBlocked(starterArea, i - 1, j + 1, src, 1, -1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j + 1].f == FLT_MAX
                    || cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 6th Successor (North-West)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1))
        {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i - 1, j - 1 + c, dest.first, dest.second + g)) {
                        // Set the Parent of the destination cell
                        //printf("w");
                        cellDetails[i - 1][j - 1 + c].parent_i = i;
                        cellDetails[i - 1][j - 1 + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i - 1][j - 1] && isUnBlocked(starterArea, i - 1, j - 1, src, -1, -1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j - 1].f == FLT_MAX
                    || cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j - 1)));
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }

        //----------- 7th Successor (South-East)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1))
        {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i + 1, j + 1 + c, dest.first, dest.second + g))
                    {
                        // Set the Parent of the destination cell
                        //printf("j = %d, c = %d", j, c);
                        //printf("e");

                        cellDetails[i + 1][j + 1 + c].parent_i = i;
                        cellDetails[i + 1][j + 1 + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i + 1][j + 1] && isUnBlocked(starterArea, i + 1, j + 1, src, 1, 1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j + 1].f == FLT_MAX
                    || cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j + 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }

        //----------- 8th Successor (South-West)
        //------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1))
        {
            // If the destination cell is the same as the
            // current successor
            for (int c = 0; c <= ZombieSize; c += (ZombieSize / 2))
            {
                for (int g = 0; g <= PlayerSize; g++)
                {
                    if (isDestination(i + 1, j - 1 + c, dest.first, dest.second + g))
                    {
                        // Set the Parent of the destination              
                        //printf("r");
                        cellDetails[i + 1][j - 1 + c].parent_i = i;
                        cellDetails[i + 1][j - 1 + c].parent_j = j;
                        //printf("The destination cell is found\n");
                        tracePath(cellDetails, dest.first, dest.second + g, ZombieposX, ZombieposY, Zombiespeed, waitForNextZombieMove, ZombieXMove);
                        foundDest = true;
                        return;
                    }
                }
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            if (!closedList[i + 1][j - 1] && isUnBlocked(starterArea, i + 1, j - 1, src, -1, 1))
            {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j - 1].f == FLT_MAX
                    || cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j - 1)));

                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}
