#include "signup.h"
#include "ui_signup.h"
#include <fstream>
#include <QDebug>

extern loggedinScreen *lis;

signup::signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::runclicker()
{
    Clicker = new QMediaPlayer;
    Click = new QAudioOutput;
            Clicker->setAudioOutput(Click);
            Clicker->setSource(QUrl("qrc:/sound/Clicked.mp3"));
            Click->setVolume(0.8);
            Clicker->play();

}
void signup::on_create_clicked()
{

    QFile file("/Users/omar/Desktop/AUC/Spring 22/CSCE/CSCE 1101/CSProjectGame/CSProjectGame/users.txt");
        if (file.open(QIODevice::Append)) {
            qDebug() << "append file opened";
            QTextStream write(&file);
            user = ui->username->text();
            if(!checkUser(user)&&user!=""){
                qDebug() << "user available";
                    pass = ui->password->text();
                    passc = ui->passwordconfirm->text();
                    if(pass!=passc){
                       ui->error->setText("password and confirmation must be the same");
                    }
                    else
                    {
                        qDebug() << "user and pass written";
                        write<<user<<"\t"<<pass<<"\n";
                        this->close();

                        lis = new loggedinScreen (user);

                        lis->show();
                    }
                    file.close();
            }
            else
            {
                ui->error->setText("user already exists! \t please try again!");
            }
        }
        else
            qDebug() << "file failed to open" ;
    runclicker();
}

bool signup::checkUser(QString user)
{
    bool found = false;
       allaccounts();
       for(int i=0;i<=x;i++){
           if(user==un[i]){
               found = true;
               break;
           }
       }if(found){
           return true;
       } else{
           return false;
       }
}

bool signup::CheckPass(QString USER, QString PASS)
{
    for(int i=0;i<=x;i++){
            if(USER==un[i]){
                x=i;
                break;
            }
        }
        if(PASS==pw[x]){
            return true;
        }else{
            return false;
        }
}

void signup::allaccounts()
{
    QFile file(":/users/users.txt");
    qDebug() << "allaccounts() file opened";
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream read(&file);
        while(!read.atEnd()){
            read >> un[x] >> pw[x];
            x++;
        }
        }
        file.close();
}


void signup::on_pushButton_clicked()
{
    this->close();
    StartingScreen *ss = new StartingScreen;
    ss->show();
}

