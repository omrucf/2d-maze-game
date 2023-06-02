#ifndef DOOR_H
#define DOOR_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <time.h>
#include <QtCore>
#include <QTimer>


class door:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    door(int,int);
};

#endif // DOOR_H
