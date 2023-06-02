#ifndef LOSTSCREEN_H
#define LOSTSCREEN_H

#include <QWidget>
#include "map.h"
#include "startingscreen.h"
#include <QMediaPlayer>
#include <QMessageBox>

namespace Ui {
class lostscreen;
}

class lostscreen : public QWidget
{
    Q_OBJECT

    QString name;
    QMediaPlayer* misc;
    QAudioOutput* music;
    void runsound();

public:
    explicit lostscreen(QString, QWidget *parent = nullptr);
    ~lostscreen();

private slots:

    void on_quit_clicked();

    void on_logout_clicked();



    void on_startgame_clicked();

private:
    Ui::lostscreen *ui;
};

#endif // LOSTSCREEN_H
