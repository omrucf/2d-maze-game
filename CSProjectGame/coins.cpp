#include "coins.h"


coins::coins( int row, int col)
{
    QPixmap c(":/icons/coins.png");
    c=c.scaledToWidth(35);
    c=c.scaledToHeight(35);
    setPixmap(c);
    setPos(35+35*col,35+35*row);

    Coins = new QTimer(this);
    connect(Coins,SIGNAL(timeout()),this,SLOT(COINS()));

    Coins->start(30000);
}

void coins::COINS()
{
    if(C)
    {
        C = false;
        delete this;
    }
}
