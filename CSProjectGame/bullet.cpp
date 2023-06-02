#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "map.h"

extern map* m;

bullet::bullet(bool r, bool l, bool u, bool d, int b[26][40])
{
    setRect(16,16,5,5);
    for(int i=0;i<26;i++)
    {
        for (int j=0;j<40;j++)
        {
            board[i][j]=b[i][j];
        }
    }
    right=r, left=l,up=u,down=d;
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}

void bullet::move()
{
int i=(pos().y()/35)-1,j=(pos().x()/35)-1;
qDebug() << "i: " << i << " j: " << j << " [i][j]: " << board[i][j];
if(board[i][j]>-1)
{
    if(up)
    {
        setPos(x(),y()-35);
    }
    if (down)
    {
        setPos(x(),y()+35);
    }
    if(left)
    {
        setPos(x()-35,y());
    }
    if (right)
    {
        setPos(x()+35,y());
    }
    col();
}
else
{
//    scene()->removeItem(this);
    delete this;
}
}

void bullet::col()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size() ;i<n;++i)
    {
        if((typeid(*(colliding_items[i])) == typeid(player)))
        {
            qDebug() << "bullet/player collision";
            m->health->decrease();
            delete this;
            return;
        }
}
}
