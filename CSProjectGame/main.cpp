#include <QApplication>
#include <time.h>
#include "map.h"
#include "startingscreen.h"
#include "loggedinScreen.h"

map* m;

loggedinScreen* lis;

int main(int argc, char *argv[])
{

    srand((unsigned) time(NULL));

    QApplication a(argc, argv);

    StartingScreen* s = new StartingScreen;
    s->show();

//     m = new map("name");
//     m->show();

    return a.exec();
}
