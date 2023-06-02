#include "login.h"
#include "ui_login.h"

extern loggedinScreen *lis;

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::keyPressEvent(QKeyEvent* event)
{
    if(event->key()==Qt::Key_Return)
    {
        on_login_2_clicked();
    }
}

void login::runclicker()
{
    Clicker = new QMediaPlayer;
    Click = new QAudioOutput;
            Clicker->setAudioOutput(Click);
            Clicker->setSource(QUrl("qrc:/sound/Clicked.mp3"));
            Click->setVolume(0.8);
            Clicker->play();
}
bool login::checkUser(QString user)
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

bool login::CheckPass(QString USER, QString PASS)
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

void login::allaccounts()
{
    QFile file("/Users/omar/Desktop/AUC/Spring 22/CSCE/CSCE 1101/CSProjectGame/CSProjectGame/users.txt");
        if (file.open(QIODevice::ReadOnly)) {
            qDebug() << " allacounts()<<login<<opned";
            QTextStream read(&file);
        while(!read.atEnd()){
            read >> un[x] >> pw[x];
            x++;
        }
        }
        file.close();
}


void login::on_login_2_clicked()
{
    runclicker();
    user = ui->username->text();

    if(!checkUser(user))
    {
        ui->error->setText("user not found!!");
    }
    else
    {
        pass = ui->password->text();
        if(CheckPass(user,pass))
        {
            this->close();

            lis = new loggedinScreen (user);

            lis->show();
        }
        else
        {
            ui->error->setText("incorrect password!");
        }
    }
}


void login::on_pushButton_clicked()
{
    this->close();
    StartingScreen *ss = new StartingScreen;
    ss->show();
}

