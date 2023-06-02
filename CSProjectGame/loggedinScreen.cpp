#include "loggedinScreen.h"
#include "ui_loggedinScreen.h"
#include <QDebug>
#include <QGraphicsScene>
#include "signup.h"
#include "login.h"

extern map* m;
loggedinScreen::loggedinScreen(QString username,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loggedinScreen)
{
    ui->setupUi(this);
    this->username = username;
    ui->name->setText("welcome "+this->username + "!");
    QPixmap background(":/icons/background.png");
    ui->background->setPixmap(background);
    runsound();
}

loggedinScreen::~loggedinScreen()
{
    delete ui;
}

void loggedinScreen::runsound()
{
    misc = new QMediaPlayer;
    music = new QAudioOutput;
    misc->setAudioOutput(music);
    misc->setSource(QUrl("qrc:/sound/Bully - Soundtrack Main Theme.mp3"));
    music->setVolume(0.1);
    misc->setLoops(QSoundEffect::Infinite);
    misc->play();
}

void loggedinScreen::onoroff()
{
    if (onoroffmusic == false){
            music -> setVolume(0);
            onoroffmusic = true;
        }else {
            music -> setVolume(0.1);
            onoroffmusic = false;
        }
}

void loggedinScreen::runclicker()
{
    Clicker = new QMediaPlayer;
    Click = new QAudioOutput;
    if (clickeronoff == false){
            Clicker->setAudioOutput(Click);
            Clicker->setSource(QUrl("qrc:/sound/Clicked.mp3"));
            Click->setVolume(0.8);
            Clicker->play();
    }
}

void loggedinScreen::clikconoroff()
{
    if (clickeronoff == false){
            Click -> setVolume(0);
            clickeronoff = true;
        }else {
            Click -> setVolume(0.8);
            clickeronoff = false;
        }
}



void loggedinScreen::on_quit_clicked()
{
    this->close();
}


void loggedinScreen::on_logout_clicked()
{
    this->close();
    runclicker();
    delete misc;
    delete music;
    delete Click;
    delete Clicker;
    StartingScreen* s = new StartingScreen;

    s->show();
}
void loggedinScreen::on_startgame_clicked()
{
    this->close();
    runclicker();
    m = new map(username);
    m->show();
}


void loggedinScreen::on_music_clicked()
{
    onoroff();
    runclicker();
}


void loggedinScreen::on_pushButton_2_clicked()
{
    runclicker();
    t = new QMessageBox;
    t->setText("Use arrow keys to move\nEnemies in level 1 die after 4 hits\nEnemies in level 2 die after 5 hits\nBullets move in the last direction the player moved in\nItaly flag refills your health\n");
    t->exec();
}

