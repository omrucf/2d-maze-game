#ifndef PAUSEDSCREEN_H
#define PAUSEDSCREEN_H

#include <QWidget>
#include "map.h"

#include "startingscreen.h"
#include "loggedinScreen.h"
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QtMultiMedia>
namespace Ui {
class pausedScreen;
}

class pausedScreen : public QWidget
{
    Q_OBJECT

    QString name;


    QMessageBox* t;
public:
    int coins;
    explicit pausedScreen(QString,QWidget *parent = nullptr);
    ~pausedScreen();
    void runsound();
    QMediaPlayer* Clicker;
    QAudioOutput* Click;
    void onoroff();

private slots:
    void on_pushButton_clicked();

    void on_sound_clicked();

    void on_logout_clicked();

    void on_login_clicked();

    void on_exit_clicked();

    void on_health10_clicked();

    void on_health25_clicked();

    void on_health50_clicked();

    void on_health100_clicked();

    void keyPressEvent(QKeyEvent* event);

    void on_pushButton_2_clicked();

private:
    Ui::pausedScreen *ui;
};

#endif // PAUSEDSCREEN_H
