#include "pausedscreen.h"
#include "ui_pausedscreen.h"

extern map* m;

extern loggedinScreen *lis;

pausedScreen::pausedScreen(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pausedScreen)
{
    this->name = name;
    ui->setupUi(this);
    QPixmap background(":/icons/background.png");
    ui->background->setPixmap(background);
    ui->name->setText(name);
    coins = m->p->Coins;
    ui->balance->setText(" You have " + QString::number(coins) + " coins");
}

pausedScreen::~pausedScreen()
{
    delete ui;
}

void pausedScreen::on_pushButton_clicked()
{
    this->close();
    m->e->timer->start();
    m->e->shootT->start();
    m->e->col->start();
    m->e_1_2->timer->start();
    m->e_1_2->shootT->start();
    m->e_1_2->col->start();
    m->e_1_3->timer->start();
    m->e_1_3->shootT->start();
    m->e_1_3->col->start();
    m->e_1_3_4->timer->start();
    m->e_1_3_4->shootT->start();
    m->e_1_3_4->col->start();
    m->e2->timer->start();
    m->e2->shootT->start();
    m->e2->col->start();
    m->e2_2->timer->start();
    m->e2_2->shootT->start();
    m->e2_2->col->start();
    m->e2_3->timer->start();
    m->e2_3->shootT->start();
    m->e2_3->col->start();
    m->e2_3_4->timer->start();
    m->e2_3_4->shootT->start();
    m->e2_3_4->col->start();
    m->p->paused = false;
    m->p->Coins = coins;
}


void pausedScreen::on_sound_clicked()
{
//    m->misc->play();
}


void pausedScreen::on_logout_clicked()
{
    delete lis->misc;
    delete lis->music;
    delete lis->Click;
    delete lis->Clicker;
    this->close();
    m->panel->close();
    StartingScreen *ss = new StartingScreen;
    ss->show();
}

void pausedScreen::runsound()
{
    Clicker = new QMediaPlayer;
    Click = new QAudioOutput;
            Clicker->setAudioOutput(Click);
            Clicker->setSource(QUrl("qrc:/sound/Clicked.mp3"));
            Click->setVolume(0.8);
            Clicker->play();
}

void pausedScreen::on_login_clicked()
{
    delete lis->misc;
    delete lis->music;
    delete lis->Click;
    delete lis->Clicker;

    this->close();
    this->close();
    m->panel->close();
    loggedinScreen *ls = new loggedinScreen(name);
    ls->show();
}


void pausedScreen::on_exit_clicked()
{
    on_pushButton_clicked();
}


void pausedScreen::on_health10_clicked()
{
    runsound();
    if(coins >= 10)
    {
        coins -= 10;
        ui->balance->setText(" You have " + QString::number(coins) + " coins");
        m->health->setHealth(m->health->getHealth() + 10);
        if (m->health->getHealth() > 100)
        {
            m->health->setHealth(100);
        }
        ui->error->setText("your health is now: " + QString::number(m->health->getHealth()));
    }
    else
        ui->error->setText("yoou don't have enogh coins to buy this!");
}


void pausedScreen::on_health25_clicked()
{
    runsound();
    if(coins >= 25)
    {
        coins -= 25;
        ui->balance->setText(" You have " + QString::number(coins) + " coins");
        m->health->setHealth(m->health->getHealth() + 25);
        if (m->health->getHealth() > 100)
        {
            m->health->setHealth(100);
        }
        ui->error->setText("your health is now: " + QString::number(m->health->getHealth()));
    }
    else
        ui->error->setText("yoou don't have enogh coins to buy this!");
}


void pausedScreen::on_health50_clicked()
{
    runsound();
    if(coins >= 50)
    {
        coins -= 50;
        ui->balance->setText(" You have " + QString::number(coins) + " coins");
        m->health->setHealth(m->health->getHealth() + 50);
        if (m->health->getHealth() > 100)
        {
            m->health->setHealth(100);
        }
        ui->error->setText("your health is now: " + QString::number(m->health->getHealth()));
    }
    else
        ui->error->setText("yoou don't have enogh coins to buy this!");
}


void pausedScreen::on_health100_clicked()
{
    runsound();
    if(coins >= 100)
    {
        coins -= 100;
        ui->balance->setText(" You have " + QString::number(coins) + " coins");
        m->health->setHealth(100);
        ui->error->setText("your health is now: " + QString::number(m->health->getHealth()));
    }
    else
        ui->error->setText("you don't have enogh coins to buy this!");
}

void pausedScreen::keyPressEvent(QKeyEvent *event)
{
    runsound();
    if(event->key() == Qt::Key_Escape)
    {
        on_pushButton_clicked();
    }
}



void pausedScreen::on_pushButton_2_clicked()
{
    runsound();
    t = new QMessageBox;
    t->setText("Use arrow keys to move\nEnemies in level 1 die after 4 hits\nEnemies in level 2 die after 5 hits\nBullets move in the last direction the player moved in\nItaly flag refills your health\n");
    t->exec();
}

