#include "BoggleWindow.h"
#include "lexicon.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>
#include <sstream>
using namespace std;

BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);

    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(this);
    console = new Console(this);

    me->setGeometry(40, 40, 460, 600);
    board->setGeometry(500, 40, 600, 600);
    computer->setGeometry(1600 - 460 - 40, 40, 460, 600);
    console->setGeometry(60, 640, 1480, 520);

    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }
    Lexicon Lex(qFile);

    me->lexi=Lex;
    computer->lexi=Lex;
    me->size=board->size;
    computer->size=board->size;

    me->lett=new QString[me->size*me->size];
    computer->lett=new QString[computer->size*computer->size];
    for (int i=0;i<board->size*board->size;i++)
    {
        me->lett[i]=board->lett[i];
        computer->lett[i]=board->lett[i];
    }

    /*
    for (std::string s: lex) {
        std::cout << s << std::endl;
    }
    */
    isPass=new bool [board->size*board->size];
    for (int i=0;i<board->size*board->size;i++)
        isPass[i]=false;

    console->write("Welcome to the game Boggle!");
    console->write("If you cannot find words any more, enter '#' to implement killer computer player!\n");


    connect( board,SIGNAL(polishlett(QString*,int)),me,SLOT(polishlett(QString*,int)));//board在shake之后要polish me和computer的lett
    connect( board,SIGNAL(polishlett(QString*,int)),computer,SLOT(polishlett(QString*,int)));

    connect( console,SIGNAL(newLineWritten(QString)),me,SLOT(megetword(QString)));//获得单词
    connect( console,SIGNAL(newLineWritten(QString)),computer,SLOT(computergetword(QString)));
    connect( me,SIGNAL(setcubesbackground(int,bool)),this,SLOT(setcubesbackground(int,bool)));


    connect( me,SIGNAL( w1(QString) ),computer,SLOT( w2(QString) ) );//me和computer的words列表链接起来
    connect( computer,SIGNAL( w1(QString) ),me,SLOT( w2(QString) ) );

    connect( computer,SIGNAL( isPolish() ),me,SLOT( polish() ) );//输入#之后要polish
    connect( computer,SIGNAL( isPolish() ),board,SLOT( polish() ) );
    connect( computer,SIGNAL( isPolish() ),console,SLOT( reset() ) );
    connect( computer,SIGNAL( write(QString) ),console,SLOT( write(QString) ) );

    connect(this,SIGNAL(clicked(QMouseEvent *)),this,SLOT(mousePressEventSlot(QMouseEvent *)));//鼠标点击事件
}

BoggleWindow::~BoggleWindow()
{
}

void BoggleWindow::mousePressEventSlot(QMouseEvent *e)
{
    int x=e->x();    //e->x()属于500-1100，e->y()属于40-640
    int y=e->y();
    if ((x<500 || x>1100 || y<40 || y>640) && clickedletters.length()>0)
    {clickedletters.remove(0,clickedletters.length());return;}//如果点的不是cubes，就清除已记录的letters

    x=(x-500)/120;
    y=(y-40)/120;

    if ((abs(x-prex)<=1 && abs(y-prey)<=1 && isPass[x+y*5]==false ) || isFirst==true)//只能点击临近的
    {
        clickedletters.append(me->lett[x+y*5].toLower());
        isPass[x+y*5]=true;
        setcubesbackground(x+y*5,true);
        //console->write(clickedletters);
        //QString x1 = QString::number(x);
        //console->write("x="+x1);
        //QString y1 = QString::number(y);
        //console->write("y="+y1);


        if (clickedletters.length()>3 && me->lexi.contains(clickedletters.toStdString()) && (me->words.contains(clickedletters)==false) )
        {
            me->addWord(clickedletters);
            me->addScore(clickedletters.length()-3);
            console->write("'"+clickedletters+"' is found. Great!");
            clickedletters.remove(0,clickedletters.length());
            for (int i=0;i<board->size*board->size;i++)
                {isPass[i]=false;setcubesbackground(i,false);}
            isFirst=true;
            return;
        }

        bool isThereRoad=false;
        for (int i=0;i<8;i++)
        {
            if ( (x+y*5)+me->arr[i]>=me->size*me->size || (x+y*5)+me->arr[i]<0 ) continue;
            if ( (x+y*5)%5==0 && (i==0 || i==3 || i==5) ) continue;
            if ( (x+y*5)%5==4 && (i==2 || i==4 || i==7) ) continue;
            if (isPass[ x+y*5+me->arr[i] ]==false) isThereRoad=true;
        }

        if (me->lexi.containsPrefix(clickedletters.toStdString())==false || isThereRoad==false)
        {
            console->write("There is not a word with the prefix '"+clickedletters+"'. Go on!");
            clickedletters.remove(0,clickedletters.length());//如果不含前缀就删掉
            for (int i=0;i<board->size*board->size;i++)
                {isPass[i]=false;setcubesbackground(i,false);}
            isFirst=true;
            return;
        }

        prex=x;
        prey=y;
        isFirst=false;
    }

}

void BoggleWindow::setcubesbackground(int index,bool flag)
{
    if (flag==true) board->cubes[index]->setStyleSheet("background-color:yellow; border-radius: 15px; border: 2px solid");
    else if (flag==false) board->cubes[index]->setStyleSheet("background-color:white; border-radius: 15px; border: 2px solid");
}
