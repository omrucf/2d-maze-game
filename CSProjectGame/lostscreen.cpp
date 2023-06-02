#include "lostscreen.h"
#include "ui_lostscreen.h"
#include "map.h"

extern map *m;

lostscreen::lostscreen(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lostscreen)
{
    ui->setupUi(this);

    this->name = name;
    runsound();

}

lostscreen::~lostscreen()
{
    delete ui;
}



void lostscreen::on_quit_clicked()
{

    m->panel->close();

    this->close();
    delete this;
    delete music;
    delete misc;
}


void lostscreen::on_logout_clicked()
{

    m->panel->close();

    StartingScreen* s = new StartingScreen;

    s->show();

    this->close();
    delete this;
    delete music;
    delete misc;

}
void lostscreen::runsound()
{
    misc = new QMediaPlayer;
    music = new QAudioOutput;
    misc->setAudioOutput(music);
    misc->setSource(QUrl("qrc:/sound/Directed by Robert B. Weide- theme meme.mp3"));
    music->setVolume(0.5);
    misc->setLoops(QSoundEffect::Infinite);
    misc->play();
}

void lostscreen::on_startgame_clicked()
{
    m->panel->close();

    m = new map(name);

    m->show();

    this->close();
    delete this;
    delete music;
    delete misc;

}

