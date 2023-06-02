#include "boss.h"
#include <cmath>
#include <QDebug>
#include <vector>
#include "map.h"

extern map *m;


bool boss::isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}
bool boss::isUnBlocked(int grid[][COL], int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col] >= 0 || grid[row][col] == -2 || grid[row][col] == -3 || grid[row][col] == -4)

      {
      //  qDebug()<<grid[row][col];
        return (true);
      }
    else
    {
        //qDebug()<<grid[row][col];
        return (false);
    }
}
bool boss::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first/35 && col == dest.second/35)
        return (true);
    else
        return (false);
}
double boss::calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (row - dest.first/35) * (row - dest.first/35)
        + (col - dest.second/35) * (col - dest.second/35)));
}
void boss::tracePath(cell cellDetails[][COL], Pair dest)
{
    qDebug()<<"tracePath function called";
    //printf("\nThe Path is ");
    int row = dest.first/35;
    int col = dest.second/35;

    std::stack<Pair> Path;
    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(std::make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(std::make_pair(row, col));
    Pathfinal=Path;
    qDebug()<<Pathfinal.size()<<"before";
    while (!Path.empty()) {
        std::pair<int, int> p = Path.top();
        Path.pop();
        qDebug()<<"("<<p.first<< p.second<<")";
    }
   // qDebug()<<"here";
    return;
}
void boss::aStarSearch(int grid[][COL], Pair src, Pair dest)
{
    //qDebug()<<"here1";
    // If the source is out of range

    if (isValid(src.first, src.second) == false) {
        qDebug() << "src.first: " << src.first << " src.second: " << src.second;

        qDebug()<<"Source is invalid\n";
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first/35, dest.second/35) == false) {
        qDebug() << "dest.first: " << dest.first << " dest.second: " << dest.second;
        qDebug()<<"Destination is invalid\n";
        return;
    }

    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == false
        || isUnBlocked(grid, dest.first/35, dest.second/35)
               == false) {
        qDebug()<<"Source or the destination is blocked\n";
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)
        == true) {
        qDebug()<<"We are already at the destination\n";
        return;
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell
    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    qDebug()<<"here5";
    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
    std::set<pPair> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair(0.0, std::make_pair(i, j)));

    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;

    while (!openList.empty()) {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

                   N   N.E
               \   |   /
                   |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)*/

        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j) == true) {
            // If the destination cell is the same as the
            // current successor

            if (isDestination(i - 1, j, dest) == true) {
                // Set the Parent of the destination cell
                up = true, down = false, right = false, left = false;
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                qDebug() << "test 1";
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j] == false
                     && isUnBlocked(grid, i - 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isnâ€™t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, std::make_pair(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------

        // Only process this cell if this is a valid one
        if (isValid(i + 1, j) == true) {
            // If the destination cell is the same as the
            // current successor

            if (isDestination(i + 1, j, dest) == true) {
                // Set the Parent of the destination cell
                up = false, down = true, right = false, left = false;

                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                qDebug() << "test 2";

                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j] == false
                     && isUnBlocked(grid, i + 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isnâ€™t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, std::make_pair(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor

            if (isDestination(i, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                up = false, down = false, right = true, left = false;

                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                qDebug() << "test 3";

                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j + 1] == false
                     && isUnBlocked(grid, i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isnâ€™t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, std::make_pair(i, j + 1)));

                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor

            if (isDestination(i, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                up = false, down = false, right = false, left = true;

                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                qDebug() << "test 4";

                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j - 1] == false
                     && isUnBlocked(grid, i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                // If it isnâ€™t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, std::make_pair(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

      }
    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    if (foundDest == false)
        qDebug()<<"Failed to find the Destination Cell\n";

   // qDebug()<<"end 0";

    return;
}
boss::boss(int boarddata[ROW][COL], player *ptr, int r, int c, QString name)
{
    this->name = name;
    row=r;
    column=c;
    this->ptr=ptr;
    QPixmap b(":/icons/BOSS.png");
    b=b.scaledToWidth(35);
    b=b.scaledToHeight(35);
    setPixmap(b);
    setPos(35+column*35,35+row*35);
    for (int i=0;i<26;i++)
        for (int j=0;j<40;j++)
        {
         data[i][j]=boarddata[i][j];
        };

    Pair src = std::make_pair(row, column);
    Pair dest = std::make_pair(ptr->getrow(), ptr->getcol());
    aStarSearch(boarddata, src, dest);
    qDebug()<<Pathfinal.size() << "after";
//    qDebug()<<Pathfinal.top()<<"top";

    myTimer();
}

void boss::myTimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(400);

    Astar = new QTimer(this);
    connect(Astar, SIGNAL(timeout()), this, SLOT(AStar()));
    Astar->start(500);

    shootT = new QTimer (this);
    connect(shootT,SIGNAL(timeout()),this,SLOT(shoot()));
    if (health>0){
        shootT->start(500);
    }

    col = new QTimer (this);
    connect(col,SIGNAL(timeout()),this,SLOT(collision()));
    if (health>0){
        col->start(100);
    }

    Enemies = new QTimer (this);
    connect(Enemies,SIGNAL(timeout()),this,SLOT(spawn()));
    if (health>0){
        Enemies->start(15000);
    }
}


void boss::shoot()
{
   if(up&&data[row-1][column]!=-1)
    {

        bullet* Bullet = new bullet(false,false,true,false,data);
        Bullet->setPos(35+35*column,0+35*row);
        scene()->addItem(Bullet);
    }
    if(down&&data[row+1][column]!=-1)
    {

        bullet* Bullet = new bullet(false,false,false,true,data);
        Bullet->setPos(35+35*column,70+35*row);
        scene()->addItem(Bullet);
    }
    if(left&&data[row][column-1]!=-1)
    {

        bullet* Bullet = new bullet(false,true,false,false,data);
        Bullet->setPos(0+35*column,35+35*row);
        scene()->addItem(Bullet);
    }
    if(right&&data[row][column+1]!=-1&&data[row][column+1]!=-2)
    {

        bullet* Bullet = new bullet(true,false,false,false,data);
        Bullet->setPos(70+35*column,35+35*row);
        scene()->addItem(Bullet);
    }
}

void boss::collision()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size();i<n;++i)
    {
        //if(enemy position is colliding with the bullet position
        //if(this->)
        if ((typeid(*(colliding_items[i])) ==  typeid(bullet)) )
        {
            collide = true;
            qDebug() << "bullet/enemy_1 collision ";
//            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
            if (health > 0)
            {
            health -= deduction;
            qDebug() << " boss's health: " << health ;
            }
            else
            {
                scene()->removeItem(this);

                alive = false;

                winningScreen* ws = new winningScreen(name);

                ws->show();

                c = new coins(row,column);

                m->scene->addItem(c);
//                delete this;
            }
            return;
        }

    }
}

void boss::spawn()
{

    if(Switch && alive)
    {
        enemy *e = new enemy(data,row,column);

        m->scene->addItem(e);

        Switch = false;
    }
    else if(!Switch && alive)
    {
        enemy_2 *e = new enemy_2(data,row,column);

        m->scene->addItem(e);

        Switch = true;
    }
}



void  boss:: move()
{
//    Pair temp=Pathfinal.top();

    qDebug() << "size bef: " << Pathfinal.size();

    Pair temp = Pathfinal.top();

    if(Pathfinal.empty()==false)
    {
    Pathfinal.pop();
    int ro=temp.first;
    int co=temp.second;
//    row = ro;
//    column = co;
    qDebug()<<"still moving";
    qDebug()<<"((" <<ro<<","<<co<<"))";
    setPos(35+co*35,35+ro*35);
    }
    qDebug() << "size after: " << Pathfinal.size();
}

void boss::AStar()
{
    row = y()/35 - 1;
    column = x()/35 - 1;
    Pair src = std::make_pair(row, column);
    Pair dest = std::make_pair(m->p->getrow(), m->p->getcol());
    aStarSearch(data, src, dest);
}
