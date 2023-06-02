#ifndef LOGGEDINSCREEN_H
#define LOGGEDINSCREEN_H

#include <QWidget>
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
#include "bullet.h"
#include <QGraphicsScene>
#include <QtMultiMedia>
#include <QMediaPlayer>
#include <QMessageBox>
#define MAX 100
namespace Ui {
class loggedinScreen;
}

class loggedinScreen : public QWidget/*, QGraphicsScene*/
{
    Q_OBJECT

    QString username;
    QMessageBox* t;

public:
    explicit loggedinScreen(QString, QWidget *parent = nullptr);

    ~loggedinScreen();
    QMediaPlayer* misc;
    QAudioOutput* music;
    void runsound();
    void onoroff();
    QMediaPlayer* Clicker;
    QAudioOutput* Click;
    void runclicker();
    void clikconoroff();
    bool onoroffmusic = false;
    bool clickeronoff = false;

private slots:

    void on_quit_clicked();

    void on_logout_clicked();

    void on_startgame_clicked();

    void on_music_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::loggedinScreen *ui;
};

#endif // STARTINGSCREEN_H
