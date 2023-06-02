#include "health.h"

#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    health = 100;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::green);
    setFont(QFont("Chalkboard",25));
}

void Health::decrease(){
    health-=10;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
    if(health<50&&health>20)
    {
        setDefaultTextColor(Qt::yellow);
    }
    else if(health<=20)
    {
        setDefaultTextColor(Qt::red);
    }

}

void Health::setHealth(int h)
{
    health = h;
    setPlainText(QString("Health: ") + QString::number(health));
    if(health>=50)
    {
        setDefaultTextColor(Qt::green);
    }
}

int Health::getHealth(){
    return health;
}
