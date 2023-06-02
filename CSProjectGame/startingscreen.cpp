#include "startingscreen.h"
#include "ui_startingscreen.h"
#include <QDebug>
#include <QGraphicsScene>
#include "signup.h"
#include "login.h"


StartingScreen::StartingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartingScreen)
{
    ui->setupUi(this);
    QPixmap background(":/icons/background.png");
    ui->background->setPixmap(background);
}

StartingScreen::~StartingScreen()
{
    delete ui;
}



void StartingScreen::on_quit_clicked()
{
    this->close();

}
void StartingScreen::runclicker()
{
    Clicker = new QMediaPlayer;
    Click = new QAudioOutput;
            Clicker->setAudioOutput(Click);
            Clicker->setSource(QUrl("qrc:/sound/Clicked.mp3"));
            Click->setVolume(0.8);
            Clicker->play();
}

void StartingScreen::on_signup_clicked()
{
    this->close();
    runclicker();
    signup* s = new signup;

    s->show();
}

void StartingScreen::on_login_clicked()
{
    this->close();
    runclicker();
    login* l = new login;
    l->show();
}


void StartingScreen::on_pushButton_clicked()
{
    runclicker();
    m = new QMessageBox;
    m->setText("Use arrow keys to move\nEnemies in level 1 die after 4 hits\nEnemies in level 2 die after 5 hits\nBullets move in the last direction the player moved in\nItaly flag refills your health\n");
    m->exec();
}

