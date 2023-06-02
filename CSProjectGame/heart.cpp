#include "heart.h"


heart::heart( int r, int c)
{
    QPixmap e(":/icons/heart.png");
    e=e.scaledToWidth(35);
    e=e.scaledToHeight(35);
    setPixmap(e);
    setPos(35+35*c,35+35*r);
}
