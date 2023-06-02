#ifndef WINNINGSCREEN_H
#define WINNINGSCREEN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMessageBox>
namespace Ui {
class winningScreen;
}

class winningScreen : public QWidget
{
    Q_OBJECT
    QString name;
    QMediaPlayer* misc;
    QAudioOutput* music;
    void runsound();
    void onoroff();

public:
    explicit winningScreen(QString, QWidget *parent = nullptr);
    ~winningScreen();

private slots:

    void on_quit_clicked();

    void on_logout_clicked();



    void on_startgame_clicked();

private:
    Ui::winningScreen *ui;
};

#endif // WINNINGSCREEN_H
