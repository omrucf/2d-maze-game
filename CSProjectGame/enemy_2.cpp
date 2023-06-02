#include "enemy_2.h"
#include <QtCore>
#include <QTimer>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "bullet.h"
#include "map.h"

extern map* m;

enemy_2::enemy_2(int dataitem [26][40], int r, int c)
{
   row=r;
   column=c;

//   health.
   QPixmap e(":/icons/enemy_2.png");
   e=e.scaledToWidth(35);
   e=e.scaledToHeight(35);
   setPixmap(e);
   setPos(35+35*column,35+35*row);
   for(int i=0;i<26;i++)
       for (int j=0;j<40;j++)
          data[i][j]=dataitem[i][j];
   MyTimer();
}



void enemy_2::MyTimer()
{
    timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));
if (health>0)
{
    timer->start(400);
}
    shootT = new QTimer (this);
    connect(shootT,SIGNAL(timeout()),this,SLOT(shoot()));
    if (health>0){
        shootT->start(3000);
    }

    col = new QTimer (this);
    connect(col,SIGNAL(timeout()),this,SLOT(collision()));
    if (health>0){
        col->start(100);
    }

}


void enemy_2::move()
{

      direction=wasd[rand()%4];
        if(direction=='w'&&data[row-1][column]!=-9&&data[row-1][column]!=-66&&data[row-1][column]!=-10&&data[row-1][column]!=-1&&!up)
        {
            row--;
            up=true;
            down=false;
            left=false;
            right=false;
        }
        if(direction=='s'&&data[row+1][column]!=-9&&data[row+1][column]!=-10&&data[row+1][column]!=-1&&!down)
        {
            row++;
            up=false;
            down=true;
            left=false;
            right=false;
        }
        if((direction=='a'&&data[row][column-1]!=-9&&data[row][column-1]!=-10&&data[row][column-1]!=-1&&data[row][column-1]!=-4&&data[row][column-1]!=-3)&&!left)
        {
            column--;
            up=false;
            down=false;
            left=true;
            right=false;
        }
        if((direction=='d'&&data[row][column+1]!=-9&&data[row][column+1]!=-10&&data[row][column+1]!=-1&&data[row][column+1]!=-4&&data[row][column+1]!=-3)&&!right)
        {
            column++;
            up=false;
            down=false;
            left=false;
            right=true;
        }
        setPos(35+35*column,35+35*row);
}

void enemy_2::MySlot()
{
    if(health>0)
    {
        move();
    }
}

void enemy_2::shoot()
{
   if(direction=='w'&&data[row-1][column]!=-1)
    {
        bullet* Bullet = new bullet(false,false,true,false,data);
        Bullet->setPos(35+35*column,0+35*row);
        scene()->addItem(Bullet);
    }
    if(direction=='s'&&data[row+1][column]!=-1)
    {
        bullet* Bullet = new bullet(false,false,false,true,data);
        Bullet->setPos(35+35*column,70+35*row);
        scene()->addItem(Bullet);
    }
    if(direction=='a'&&data[row][column-1]!=-1)
    {
        bullet* Bullet = new bullet(false,true,false,false,data);
        Bullet->setPos(0+35*column,35+35*row);
        scene()->addItem(Bullet);
    }
    if(direction=='d'&&data[row][column+1]!=-1&&data[row][column+1]!=-2)
    {
        bullet* Bullet = new bullet(true,false,false,false,data);
        Bullet->setPos(70+35*column,35+35*row);
        scene()->addItem(Bullet);
    }
}


int enemy_2::getHealth()
{
    return health;
}

void enemy_2::setHealt(int h)
{
    health = h;
}


void enemy_2::collision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size();i<n;++i)
    {
//            if(typeid(colliding_items[i])==typeid(bullet);
        if ((typeid(*(colliding_items[i])) ==  typeid(bullet)))

        {
            qDebug() << "bullet/enemy_2 collision ";
//            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            if (health!=0)
            {
            setHealt(health-deduction);
            qDebug() << "health: " << health ;
            }
            //if(health==0)
            else
            {
                 scene()->removeItem(this);
                 alive = false;
                 c = new coins(row,column);

                 m->scene->addItem(c);
//                 delete this;
            }
            return;
        }

    }
}
