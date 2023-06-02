#include "player.h"
#include "bullet.h"
#include <QDebug>
#include <QGraphicsScene>
#include "map.h"
#include "pausedscreen.h"

extern map* m;

extern loggedinScreen *lis;

player::player(int dataitem [26][40], QString name/*, bool* lvl1*/)
{
   this->name = name;
   row=1;
   column=0;
   QPixmap p(":/icons/mario.png");
   p=p.scaledToWidth(35);
   p=p.scaledToHeight(35);
   setPixmap(p);
   setPos(35+35*column,35+35*row);
   QGraphicsRectItem().setRect(35*25,0,35,350);
   for(int i=0;i<26;i++)
       for (int j=0;j<40;j++)
           data[i][j]=dataitem[i][j];

   col = new QTimer (this);
   connect(col,SIGNAL(timeout()),this,SLOT(collision()));

   col->start(500);

  // h= new QTimer (this);
  // connect(h,SIGNAL(timeout()),this,SLOT(Health()));

   //h->start(100);


}
void player::setHealth(int h)
{
    health = h;
}

void player::runsound()
{
    footsteps = new QMediaPlayer;
    foot = new QAudioOutput;
    if (onoroff == false){
            footsteps->setAudioOutput(foot);
            footsteps->setSource(QUrl("qrc:/sound/Single Footstep.mp3"));
            foot->setVolume(0.8);
            footsteps->play();
    }
}
void player::gunsounds()
{
    gunshot = new QMediaPlayer;
    gun = new QAudioOutput;
    if (onoroff == false){
            gunshot->setAudioOutput(gun);
            gunshot->setSource(QUrl("qrc:/sound/GunShotSnglFireIn PE1097304.mp3"));
            gun->setVolume(0.8);
            gunshot->play();

    }
}

void player::powerup()
{
    health1 = new QMediaPlayer;
    healthup = new QAudioOutput;
    if (onoroff == false){
            health1->setAudioOutput(healthup);
            health1->setSource(QUrl("qrc:/sound/Royalty Free Game sound sfx power Up.mp3"));
            healthup->setVolume(0.8);
            health1->play();
    }
}

void player::coinupsound()
{
    coin1 = new QMediaPlayer;
    coinup = new QAudioOutput;
    if (onoroff == false){
            coin1->setAudioOutput(coinup);
            coin1->setSource(QUrl("qrc:/sound/Mario Coin Sound - Sound Effect (HD).mp3"));
            coinup->setVolume(0.8);
            coin1->play();
    }
}

void player::isiton()
{
    if (onoroff == false){
            foot -> setVolume(0);
            gun -> setVolume(0);
            onoroff = true;
        }else {
            foot -> setVolume(0.8);
            gun -> setVolume(0.8);
            onoroff = false;
        }
}
int player::getHealt()
{
    return health;
}

void player::keyPressEvent(QKeyEvent* event)
{
    if(alive)
    {

        if((event->key()==Qt::Key_Up)&&(data[row-1][column]>-1||data[row-1][column]==-2||data[row-1][column]==-3||data[row-1][column]==-4))
        {
            row--;
            up=true;
            down=false;
            right=false;
            left=false;
            runsound();
        }
        else if((event->key()==Qt::Key_Down)&&(data[row+1][column]>-1||(data[row+1][column]==-3)||(data[row+1][column]==-2)||(data[row+1][column]==-4)))
        {
            row++;
            down=true;
            up=false;
            right=false;
            left=false;
            runsound();
        }
        else if((event->key()==Qt::Key_Left)&&(data[row][column-1]>-1||data[row][column-1]==-2||data[row][column-1]==-3||data[row][column-1]==-4))
        {
//            column--;
//            left=true;
//            down=false;
//            up=false;
//            right=false;
            if(((data[row][column]!=-3||!m->D2)))
            {
                column--;
                right=false;
                left=true;
                down=false;
                up=false;
                runsound();
            }
        }
        else if((event->key()==Qt::Key_Right)&&(data[row][column+1]>-1||(data[row][column+1]==-2)||data[row][column+1]==-3||data[row][column+1]==-4))
        {
            if(((data[row][column]!=-2||!m->D1)))
            {
                column++;
                right=true;
                left=false;
                down=false;
                up=false;
                runsound();
            }
            /*if(((data[row][column]!=-3||!m->D2)))
            {
//                column++;
                right=true;
                left=false;
                down=false;
                up=false;
            }*/
//            if (right)
//             {
//                column++;
//            }

        }
        else if (event->key()==Qt::Key_Space&&up/*direction->key()==Qt::Key_Up*/)
        {
            bullet* Bullet = new bullet(false,false,true,false,data);
            Bullet->setPos(35+35*column,0+35*row);
            scene()->addItem(Bullet);
            gunsounds();
        }
        else if (event->key()==Qt::Key_Space&&down/*direction->key()==Qt::Key_Up*/)
        {
            bullet* Bullet = new bullet(false,false,false,true,data);
            Bullet->setPos(35+35*column,70+35*row);
            scene()->addItem(Bullet);
            gunsounds();
        }
        else if (event->key()==Qt::Key_Space&&right/*direction->key()==Qt::Key_Up*/)
        {
            bullet* Bullet = new bullet(true,false,false,false,data);
            Bullet->setPos(70+35*column,35+35*row);
            scene()->addItem(Bullet);
            gunsounds();
        }
        else if (event->key()==Qt::Key_Space&&left/*direction->key()==Qt::Key_Up*/)
        {
            bullet* Bullet = new bullet(false,true,false,false,data);
            Bullet->setPos(0+35*column,35+35*row);
            scene()->addItem(Bullet);
            gunsounds();
        }
        else if(event->key() == Qt::Key_Escape)
        {
            qDebug() << "escape pressed";
            if(!paused)
            {
                m->e->timer->stop();
                m->e->shootT->stop();
                m->e->col->stop();
                m->e_1_2->timer->stop();
                m->e_1_2->shootT->stop();
                m->e_1_2->col->stop();
                m->e_1_3->timer->stop();
                m->e_1_3->shootT->stop();
                m->e_1_3->col->stop();
                m->e_1_3_4->timer->stop();
                m->e_1_3_4->shootT->stop();
                m->e_1_3_4->col->stop();
                m->e2->timer->stop();
                m->e2->shootT->stop();
                m->e2->col->stop();
                m->e2_2->timer->stop();
                m->e2_2->shootT->stop();
                m->e2_2->col->stop();
                m->e2_3->timer->stop();
                m->e2_3->shootT->stop();
                m->e2_3->col->stop();
                m->e2_3_4->timer->stop();
                m->e2_3_4->shootT->stop();
                m->e2_3_4->col->stop();
                paused = true;
                pausedScreen* ps = new pausedScreen(name);
                ps->show();
            }
            else
            {
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
                m->e2_3_4->timer->start();
                m->e2_3_4->shootT->start();
                m->e2_3_4->col->start();
                paused = false;
            }
        }
        setPos(35+35*column,35+35*row);
    }
}

int player::getcol()
{
    return (35+35*column);
}

int player::getrow()
{
    return (35+35*row);
}

player::player(bool lvl1)
{
    this->lvl1=lvl1;
}

void player::collision()
{


    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size() && alive;i<n;++i)
    {

        if ((typeid(*(colliding_items[i])) == typeid(enemy))||(typeid(*(colliding_items[i])) == typeid(enemy_2)) || (typeid(*(colliding_items[i])) == typeid(boss)))
        {
            qDebug() << "bullet, enemy_1, or enemy_2/player collision ";


//            if(m->health->getHealth()==10)
//            {
//                m->health->decrease();
//                 scene()->removeItem(this);
//                 alive = false;
////                  delete this;
//            }
            if (alive)
            {
                if(m->health->getHealth()==10)
                {
                    scene()->removeItem(this);
                }
            m->health->decrease();
            //setHealth(health-10);
            //qDebug() << "health: " << health ;
            return;
            }


        }
        if((typeid(*(colliding_items[i])) == typeid(bullet)))
        {
//               qDebug() << "bullet collided with player";
               scene()->removeItem(colliding_items[i]);
            if (alive)
            {
                if(m->health->getHealth()==10)
                {
                    scene()->removeItem(this);
                }
            m->health->decrease();
            //setHealth(health-10);
            //qDebug() << "health: " << health ;

            }
//            delete colliding_items[i];
            return;
        }
        if(typeid(*(colliding_items[i])) == typeid(heart))
        {
             health = 100;
            m->health->setHealth(health);
            powerup();
            scene()->removeItem(colliding_items[i]);
//            delete colliding_items[i];
        }

        if(typeid(*(colliding_items[i])) == typeid(coins))
        {
            m->p->Coins += 50;
            coinupsound();
            scene()->removeItem(colliding_items[i]);
//            delete colliding_items[i];
        }

        if(typeid(*(colliding_items[i])) == typeid(door))
        {
            if(column==11&&row==5)
            {
                column--;
            }
            if(column==17&&row==5)
            {
                column++;
            }
            if(column==31&&row==10)
            {
                column--;
            }
            if(column==27&&row==14)
            {
                column--;
            }

            qDebug() << "x: " << x() << " y: " << y();
            setPos(35+35*column,35+35*row);
        }

    }
}


//void player::Health()
//{
//    if(m->health->getHealth()==10)
//    {
//        m->health->decrease();
//         scene()->removeItem(this);
//         alive = false;
////                  delete this;
//    }
//}
