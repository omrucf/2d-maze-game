#include "door.h"

door::door(int x, int y)
{
    QPixmap e(":/icons/door.png");
    e=e.scaledToWidth(35);
    e=e.scaledToHeight(35);
    setPixmap(e);
    setPos(35+35*x,35+35*y);
}
