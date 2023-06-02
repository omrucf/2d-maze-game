#ifndef MAP_H
#define MAP_H
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "boss.h"
#include "player.h"
#include "enemy.h"
#include "enemy_2.h"
#include "heart.h"
#include "coins.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "door.h"
#include "health.h"
#include "winningscreen.h"
#include "lostscreen.h"
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QFont>


class map: public QGraphicsView
{
    Q_OBJECT
    bool lvl1 = false, lvl2 = false, lvl3 = false;
    QString name;
public:
    bool isE1 = true, isE2 = true, isE3 = true, isE4 = true, isE5 = true, isE6 = true , isE7 = false, isE8 = false;

    QGraphicsScene *scene;
    boss* b;
    player* p;
    enemy* e;
    enemy* e_1_2;
    enemy_2* e2;
    enemy_2* e2_2;
    enemy* e_1_3;
    enemy_2* e2_3;
    enemy* e_1_3_4;
    enemy_2* e2_3_4;
    heart* h;
    door* d1,*d2,*d3,*d4,*d5,*d6;
    int r=26, c=40;
    QGraphicsPixmapItem** dataimage;
    QPixmap* grass;
    QPixmap* bricks;
    QPixmap* floor;
    QPixmap* pisa;
    QPixmap* colosseum;
    QPixmap* lvl2Bricks;
    QPixmap* lvl2Grass;
    bool Switch = false;
    bool alive = true;
    int boarddata[26][40];
    QAudioOutput* music;
    QMediaPlayer* misc;

    void exit();

    QGraphicsView* panel;
    map(QString, QWidget* parent = 0);
    Health* health;
    void timer();
    bool D1 = true, D2 = true, D3 = true;
public slots:
   void check();

};

#endif // MAP_H
