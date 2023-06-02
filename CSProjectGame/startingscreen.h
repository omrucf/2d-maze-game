#ifndef STARTINGSCREEN_H
#define STARTINGSCREEN_H

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
#include <QMessageBox>
#include <QMediaPlayer>
#include <QtMultiMedia>
#define MAX 100
namespace Ui {
class StartingScreen;
}

class StartingScreen : public QWidget/*, QGraphicsScene*/
{
    Q_OBJECT
    bool start = false;

public:
    explicit StartingScreen(QWidget *parent = nullptr);

    QMessageBox* m;

    ~StartingScreen();
    QMediaPlayer* Clicker;
    QAudioOutput* Click;
    void runclicker();

private slots:

    void on_quit_clicked();

    void on_signup_clicked();

    void on_login_clicked();

    void on_pushButton_clicked();

private:
    Ui::StartingScreen *ui;
};

#endif // STARTINGSCREEN_H
