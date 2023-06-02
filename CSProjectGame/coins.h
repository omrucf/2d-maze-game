#ifndef COINS_H
#define COINS_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <time.h>
#include <QtCore>
#include <QTimer>


class coins:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    bool C = true;
public:
    coins(int, int);
    QTimer *Coins;
public slots:
    void COINS();
};

#endif // HEART_H
