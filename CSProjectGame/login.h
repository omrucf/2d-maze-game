#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include "loggedinScreen.h"
#include "startingscreen.h"
#include <QKeyEvent>
#include <QtMultiMedia>
#include <QMediaPlayer>
#define MAX 100
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT
    QString user, pass;
    QString un[MAX];
    QString pw[MAX];
    int x = 0;
public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    bool checkUser(QString);
    void allaccounts();
    bool CheckPass(QString,QString);
    QMediaPlayer* Clicker;
    QAudioOutput* Click;
    void runclicker();
private slots:
    void keyPressEvent(QKeyEvent* event);
    void on_login_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
