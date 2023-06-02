#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QList>
#include "enemy.h"
#include "enemy_2.h"
#include "heart.h"
#include "coins.h"
#include "door.h"
//#include "pausedscreen.h"
//#include "map.h"
//#include "lostscreen.h"
#include <QMediaPlayer>
#include <QtMultimedia>

class player :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString name;
    int row;
    int column;
    int data[26][40];
    bool lvl1=false,lvl2=false,lvl3=false,bosslvl=false;
    int health = 100;

    bool alive = true;
    bool up=false,down=false,right=false,left=false;
public:
    bool paused = false;
    int Coins = 0;
    player(int [26][40], QString/*, bool**/);
    player(bool);
    void setHealth(int);
    int getHealt();
    int getcol();
    int getrow();
    QTimer * col;
    QTimer* h;
    QMediaPlayer* footsteps;
    QAudioOutput* foot;
    QMediaPlayer* gunshot;
    QAudioOutput* gun;
    QMediaPlayer* health1;
    QAudioOutput* healthup;
    QMediaPlayer* coin1;
    QAudioOutput* coinup;
    void isiton();
    void runsound();
    void gunsounds();
    void powerup();
    void coinupsound();
    bool onoroff = false;
//    pausedScreen* ps;
public slots:
    void keyPressEvent(QKeyEvent* event);
    void collision();
   // void Health();
};
#endif // PLAYER_H
