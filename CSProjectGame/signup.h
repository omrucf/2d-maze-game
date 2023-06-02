#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include "startingscreen.h"
#include "loggedinScreen.h"

namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT
    QString user, pass, passc;
    QString un[MAX];
    QString pw[MAX];
    int x = 0;
public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();
    bool checkUser(QString);
    void allaccounts();
    bool CheckPass(QString,QString);
    QMediaPlayer* Clicker;
    QAudioOutput* Click;
    void runclicker();

private slots:
    void on_create_clicked();

    void on_pushButton_clicked();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
