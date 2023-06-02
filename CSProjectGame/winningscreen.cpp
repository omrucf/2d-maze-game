#include "winningscreen.h"
#include "ui_winningscreen.h"
#include "map.h"

extern map *m;

winningScreen::winningScreen(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::winningScreen)
{
    ui->setupUi(this);

    this->name = name;
    runsound();


}

void winningScreen::runsound()
{
    misc = new QMediaPlayer;
    music = new QAudioOutput;
    misc->setAudioOutput(music);
    misc->setSource(QUrl("qrc:/sound/والله وعملوها الرجاله.mp3"));
    music->setVolume(0.5);
    misc->setLoops(QSoundEffect::Infinite);
    misc->play();
}

winningScreen::~winningScreen()
{
    delete ui;
}



void winningScreen::on_quit_clicked()
{

    m->panel->close();

    this->close();
    delete this;
    delete misc;
    delete music;
}


void winningScreen::on_logout_clicked()
{

    m->panel->close();

    StartingScreen* s = new StartingScreen;

    s->show();

    this->close();
    delete this;
    delete misc;
    delete music;

}

void winningScreen::on_startgame_clicked()
{
    m->panel->close();

    m = new map(name);

    m->show();

    this->close();
    delete this;
    delete misc;
    delete music;

}

