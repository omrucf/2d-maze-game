#include "enemy.h"
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

extern map *m;


enemy::enemy(int dataitem [26][40], int r, int c)
{
   row=r;
   column=c;

   QPixmap e(":/icons/enemy.png");
   e=e.scaledToWidth(35);
   e=e.scaledToHeight(35);
   setPixmap(e);
   setPos(35+35*column,35+35*row);
   for(int i=0;i<26;i++)
       for (int j=0;j<40;j++)
          data[i][j]=dataitem[i][j];
   MyTimer();
}



void enemy::MyTimer()
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

void enemy::move()
{
    qDebug() << "up val: " << data[row-1][column];
    if(data[row-1][column]==-1||data[row-1][column]==-10||data[row-1][column]==-11)
    {up=false;}
    if(data[row+1][column]==-1||data[row+1][column]==-10||data[row+1][column]==-11)
    {down=false;}
    if(data[row][column-1]==-1||data[row][column-1]==-10||data[row][column-1]==-11)
    {left=false;}
    if(data[row][column+1]==-1||data[row][column+1]==-10||data[row][column+1]==-11)
    {right=false;}
    if(!right&&!left&&!up&&!down)
    {
        direction=wasd[rand()%4];
        if(((direction=='w'&&!(data[row-1][column]==-1||data[row-1][column]==-10||data[row-1][column]==-11))||(direction=='s'&&!(data[row+1][column]==-1||data[row+1][column]==-10||data[row+1][column]==-11))||(direction=='a'&&!(data[row][column-1]==-1||data[row][column-1]==-10||data[row][column-1]==-11))||(direction=='d'&&!((data[row][column+1]==-1||data[row][column+1]==-10||data[row][column+1]==-11)))))
        {
            switch (direction)
            {
            case 'w':
               up = true;
               break;
           case 'a':
               left = true;
               break;
           case 's':
               down=true;
               break;
           case 'd':
              right=true;
              break;
             }
         }

    }
    if(up)
        {

            row--;

        }
     if(down)
        {

            row++;

        }
     if(left)
        {
            column--;
        }
     if(right)
        {
            column++;
        }
        setPos(35+35*column,35+35*row);

}

void enemy::MySlot()
{

if(health>0){
  direction=wasd[rand()%4];
    if(direction=='w'&&data[row-1][column]!=-1&&data[row-1][column]!=-77&&data[row-1][column]!=-10&&data[row-1][column]!=-11&&data[row-1][column]!=-8&&data[row-1][column]!=-9)
    {
        row--;
    }
    if(direction=='s'&&data[row+1][column]!=-1&&data[row+1][column]!=-10&&data[row+1][column]!=-11&&data[row+1][column]!=-8&&data[row+1][column]!=-9)
    {
        row++;
    }
    if(direction=='a'&&data[row][column-1]!=-1&&data[row][column-1]!=-77&&data[row][column-1]!=-10&&data[row][column-1]!=-11&&data[row][column-1]!=-4&&data[row][column-1]!=-9&&data[row][column-1]!=-8)
    {
        column--;

    }
    if(direction=='d'&&data[row][column+1]!=-1&&data[row][column+1]!=-11&&data[row][column+1]!=-10&&data[row][column+1]!=-2&&data[row][column+1]!=-4&&data[row][column+1]!=-8&&data[row][column+1]!=-9)
    {
        column++;

    }
    setPos(35+35*column,35+35*row);
}
}

void enemy::shoot()
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


int enemy::getHealth()
{
    return health;
}

void enemy::setHealt(int h)
{
    health = h;
}


void enemy::collision()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size();i<n;++i)
    {
        //if(enemy position is colliding with the bullet position
        //if(this->)
        if ((typeid(*(colliding_items[i])) ==  typeid(bullet)) )
        {
            collide = true;
            qDebug() << "bullet/enemy_1 collision ";
            scene()->removeItem(colliding_items[i]);
//            delete colliding_items[i];
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
//                delete this;
            }
            return;
        }

    }
}

