#ifndef BULLET_H
#define BULLET_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <time.h>
#include <QtCore>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>
#include "player.h"
#include <QList>
#include "enemy.h"
#include "enemy_2.h"


class bullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    bool right, left,up,down;
    int board[26][40];

public:

    bullet(bool, bool, bool, bool, int [26][40]);

public slots:
    void move();
    void col();
};

#endif // BULLET_H
