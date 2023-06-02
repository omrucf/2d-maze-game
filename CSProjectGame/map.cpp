#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "enemy.h"
#include "enemy_2.h"
#include <time.h>
#include <QTimer>
#include "map.h"

void map::exit()
{
    this->close();
}

map::map(QString name, QWidget* parent): QGraphicsView(parent)
{
    this->name = name;
    panel = new QGraphicsView;
    panel->setFixedSize(1400,910);
    panel->setWindowTitle("game");

//    QBrush brush(qRgb(250,214, 68));
    QBrush brush(qRgb(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    panel->setBackgroundBrush(brush);

    // creating a scene
    scene = new QGraphicsScene;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(0,0);
    scene->setSceneRect(35,35,1400,910);


      // creating a file object
        QFile file(":board/Board.txt");
        file.open(QIODevice::ReadOnly);

        // creating a text stream
        QTextStream stream(&file);

        // to read string from the file then convert it to int
        QString temp;

        // Reading from the file
        for (int i=0;i<26;i++)
            for (int j=0;j<40;j++)
            {
             stream>>temp;
             boarddata[i][j]=temp.toInt();
            }
        dataimage  = new QGraphicsPixmapItem *[r];
        for (int i = 0;i <r; i++)
        {
            dataimage[i] = new QGraphicsPixmapItem [c];
        }
        grass = new QPixmap(":/icons/Grass.jpeg");
        bricks = new QPixmap(":/icons/Bricks.jpeg");
        floor = new QPixmap(":/icons/floor.jpg");
        pisa = new QPixmap(":/icons/pisa.png");
        colosseum = new QPixmap(":/icons/colosseum.png");
        lvl2Bricks = new QPixmap(":/icons/lvl2Bricks.png");
        lvl2Grass = new QPixmap(":/icons/lvl2Grass.jpeg");


        QAudioOutput* music = new QAudioOutput();
        QMediaPlayer* misc = new QMediaPlayer;
        misc->setAudioOutput(music);
        misc->setSource(QUrl("qrc:/sound/Bully - Soundtrack Main Theme.mp3"));
        music->setVolume(0);
        misc->setLoops(QSoundEffect::Infinite);
        misc->play();




        *floor=floor->scaledToWidth(35);
        *floor=floor->scaledToHeight(35);

        *grass=grass->scaledToWidth(35);
        *grass=grass->scaledToHeight(35);

        *bricks=bricks->scaledToWidth(35);
        *bricks=bricks->scaledToHeight(35);

        *pisa=pisa->scaledToWidth(35);
        *pisa=pisa->scaledToHeight(35);

        *colosseum=colosseum->scaledToWidth(35);
        *colosseum=colosseum->scaledToHeight(35);

        *lvl2Bricks=lvl2Bricks->scaledToWidth(35);
        *lvl2Bricks=lvl2Bricks->scaledToHeight(35);

        *lvl2Grass=lvl2Grass->scaledToWidth(35);
        *lvl2Grass=lvl2Grass->scaledToHeight(35);



        for (int i=0;i<26;i++)
        {
            for (int j=0;j<40;j++)
            {
                if(boarddata[i][j]<=-1&&boarddata[i][j]!=-7&&boarddata[i][j]!=-16&&boarddata[i][j]!=-99&&boarddata[i][j]!=-66&&boarddata[i][j]!=-2&&boarddata[i][j]!=-3&&boarddata[i][j]!=-88&&boarddata[i][j]!=-4&&boarddata[i][j]!=-8&&boarddata[i][j]!=-9)
                {
                    dataimage[i][j].setPixmap(*bricks);
                }
                else if(boarddata[i][j]==-9||boarddata[i][j]==-8||boarddata[i][j]==-66)
                {
//                    if(Switch)
//                    {
                        dataimage[i][j].setPixmap(*lvl2Bricks);
//                        Switch = false;
//                    }
//                    else
//                    {
//                        dataimage[i][j].setPixmap(*pisa);
//                        Switch = true;
//                    }
                }
                else if(boarddata[i][j]>=00&&boarddata[i][j]>=0&&boarddata[i][j]!=151)
                {
                    if(boarddata[i][j]<68)
                    {
                        dataimage[i][j].setPixmap(*grass);
                    }
                    else
                    {
                        dataimage[i][j].setPixmap(*lvl2Grass);
                    }
                }
                else if(boarddata[i][j]==-7||boarddata[i][j]==-99)
                {
                    dataimage[i][j].setPixmap(*floor);
                }
                else if(boarddata[i][j]==-88)
                {

                    dataimage[i][j].setPixmap(*colosseum);
                }

                dataimage[i][j].setPos(35+35*j,35+35*i);
                scene->addItem(&dataimage[i][j]);
            }
        }

        p = new player(boarddata, name/*,lvl1*/);

        p->setFlag(QGraphicsItem::ItemIsFocusable);
        p->setFocus();


        scene->addItem(p);

        h = new class heart(12,34);

        scene->addItem(h);

        d1 = new class door(11,5);

        scene->addItem(d1);

        d2 = new class door(17,5);

        scene->addItem(d2);

        d3 = new class door(31,10);

        scene->addItem(d3);

        d4 = new class door(27,14);

        scene->addItem(d4);

        d5 = new class door(33,14);

        scene->addItem(d5);

        d6 = new class door(5,22);

        scene->addItem(d6);

        e = new enemy(boarddata,1,1/*,lvl_1*/);

        scene->addItem(e);

         e_1_2 = new enemy(boarddata,9,7/*,lvl_1*/);

        scene->addItem(e_1_2);

         e2 = new enemy_2(boarddata,1,18);

        scene->addItem(e2);

         e2_2 = new enemy_2(boarddata,10,30);

         health = new Health();
         health->setPos(35*35,35);
         scene->addItem(health);

         scene->addItem(e2_2);

         e_1_3_4 = new enemy(boarddata,14,7/*,lvl_1*/);

        scene->addItem(e_1_3_4);

         e2_3 = new enemy_2(boarddata,19,7);

        scene->addItem(e2_3);

        e_1_3 = new enemy(boarddata,18,25/*,lvl_1*/);

        scene->addItem(e_1_3);

         e2_3_4 = new enemy_2(boarddata,21,25);

        scene->addItem(e2_3_4);

//        b = new boss(boarddata, p, 1,1);


          panel->setScene(scene);
          panel->show();


timer();
}

void map::timer()
{
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(check()));
    timer->start(1000);
}


void map::check()
{


//    if(!e->alive && isE1)
//    {
////        coins *c = new coins(e->row,e->column);

////        scene->addItem(c);

//        isE1 = false;
//    }

//    if(!e_1_2->alive && isE2)
//    {
//        coins *c = new coins(e_1_2->row,e_1_2->column);

//        scene->addItem(c);

//        isE2 = false;
//    }


//    if(!e2->alive && isE3)
//    {
//        coins *c = new coins(e2->row,e2->column);

//        scene->addItem(c);

//        isE3 = false;
//    }

//    if(!e2_2->alive && isE4)
//    {
//        coins *c = new coins(e2_2->row,e2_2->column);

//        scene->addItem(c);

//        isE4 = false;
//    }

//    if(!e2_3_4->alive && isE5)
//    {
//        coins *c = new coins(e2_3_4->row,e2_3_4->column);

//        scene->addItem(c);

//        isE5 =false;
//    }

//    if(!e2_3->alive && isE6)
//    {
//        coins *c = new coins(e2_3->row,e2_3->column);

//        scene->addItem(c);

//        isE6 = false;
//    }

//    if(!e_1_3->alive && isE7)
//    {
//        coins *c = new coins(e_1_3->row,e_1_3->column);

//        scene->addItem(c);

//        isE7 = false;
//    }

//    if(!e_1_3_4->alive && isE8)
//    {
//        coins *c = new coins(e_1_3_4->row,e_1_3_4->column);

//        scene->addItem(c);

//        isE8 = false;
//    }


    if(health->getHealth()==0 && alive)
    {
        lostscreen* l = new lostscreen(name);
         l->show();
         alive = false;
//         panel->close();
      }
       else
        p->setFocus();

    if(!e->alive && !e_1_2->alive && D1)
    {
//        lvl1=true;
        qDebug() << "enemy 1,2 died";
        scene->removeItem(d1);

        delete d1;



        D1 = false;
    }


    if(!e2->alive && !e2_2->alive && D2)
    {
        scene->removeItem(d2);
        scene->removeItem(d3);
        scene->removeItem(d5);

        delete d2;
        delete d3;
        delete d5;



        D2 = false;
    }

    if(!e2_3->alive &&!e2_3_4->alive &&!e_1_3_4->alive &&!e_1_3->alive  && D3)
    {
        scene->removeItem(d4);
        scene->removeItem(d6);

        delete d4;
        delete d6;

        D3 = false;

        b = new boss(boarddata, p, 1,1, name);

        scene->addItem(b);

//        b->timer->start();
//        b->shootT->start();
//        b->col->start();

//        b = new boss(boarddata,p);

//        scene->addItem(b);
    }

//    if(he==0)
//    {
//        lostscreen* l = new lostscreen;

//        l->show();
//    }

//    QGraphicsTextItem m;
//    m.setPlainText(QString("Health: ") + QString::number(p->getHealt()));
//    m.set
//    m.setPos(100,100);
//    scene->addItem(&m);

//if(!e2_3->isActive()&&!e2_3_4->isActive() &&!e_1_3_4->isActive()&&!e_1_3->isActive() && !e2->isActive()&&!e2_2->isActive() && !e->isActive() && !e_1_2->isActive())
//{

//    panel->close();
//    delete panel;
//    winningScreen* w = new winningScreen;
//    w->show();
//}

//    if(!D3)
//    {
//        if(!b->alive)
//        {
//            lostscreen *ls = new lostscreen(name);
//            panel->close();
//            ls->show();
//        }
//    }



    if(!panel->isVisible())
    {
        this->close();
    }
}



