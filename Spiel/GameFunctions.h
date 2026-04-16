#pragma once
#include <utility>

#define ROWS 47
#define COLS 162
#define PlayerSize 4

using namespace std;

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> pPair;

extern int PlayerX;
extern int PlayerY;

struct cell {
    int parent_i, parent_j;
    double f, g, h;
};

bool VisionCheck(int zx, int zy, int px, int py, char area[][COLS], int zombieDeathValue, int emptyChar);
bool isValid(int row, int col);
bool isUnBlocked(char grid[][COLS], int row, int col, Pair src, int dx, int dy);
bool isDestination(int row, int col, int destRow, int destCol);
double calculateHValue(int row, int col, Pair dest);
