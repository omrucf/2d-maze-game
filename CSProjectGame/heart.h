#ifndef HEART_H
#define HEART_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <time.h>
#include <QtCore>
#include <QTimer>


class heart:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    heart(int, int);
};

#endif // HEART_H
