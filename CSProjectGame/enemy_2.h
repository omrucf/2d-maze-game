#ifndef ENEMY_2_H
#define ENEMY_2_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <time.h>
#include <QtCore>
#include <QTimer>
#include "bullet.h"
#include "coins.h"

class enemy_2:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    int health = 100;
    int data[26][40];
    char wasd[4]={'w','a','s','d'};
    char direction;
    bool right=false,left=false,up=false,down=false;
public:
    int deduction = 20;

    bool alive = true;
    enemy_2(int [26][40], int , int);
    void MyTimer();
    void move();
    int getHealth();
    void setHealt(int);
    QTimer *timer;
    QTimer *shootT;
    QTimer *col;
    int row;
    int column;
    coins *c;
public slots:
    void MySlot();
    void shoot();
    void collision();
};

#endif // ENEMY_H




