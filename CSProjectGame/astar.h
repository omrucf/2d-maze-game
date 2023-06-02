#ifndef ASTAR_H
#define ASTAR_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <player.h>
#include "/Users/omar/Desktop/programs/stdc++.h"
#include <QTimer>
#define ROW 26
#define COL 40

//using namespace std;

// Creating a shortcut for int, int pair type
typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef std::pair<double, std::pair<int, int> > pPair;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

class aStar: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
int row;
int column;
int data[26][40];
player *ptr;
std::stack<Pair> Pathfinal;
public:
    aStar(int [26][40], player *, int, int);
    bool isValid(int row, int col);
    bool isUnBlocked(int grid[][COL], int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void tracePath(cell cellDetails[][COL], Pair dest);
    void aStarSearch(int grid[][COL], Pair src, Pair dest);
public slots:
    void move();

};
#endif // PLAYER_H
