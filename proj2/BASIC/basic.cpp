#include <iostream>
#include "basic.h"
using namespace std;

basic::basic(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("BASIC");
    this->setFixedSize(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);


    Console = new console(this);
    Console->setGeometry(0, 0,BASIC_WINDOW_WIDTH,BASIC_WINDOW_HEIGHT);
    Console->write("Welcome to BASIC interpreter!\n");
    exp = new expression;
    runing = new running;

    connect( Console,SIGNAL(newLineWritten(QString)),exp,SLOT(getExpression(QString)));
    connect( exp,SIGNAL(writeToConsole(QString)),Console,SLOT(write(QString)));
    connect( runing,SIGNAL(validfailed()),exp,SLOT(validfailed()));
    connect( runing,SIGNAL(writeToConsole(QString)),Console,SLOT(write(QString)));
    connect( exp,SIGNAL(quit()),this,SLOT(quit()));
    connect( exp,SIGNAL(run(QMap<int,node>)),runing,SLOT(run(QMap<int,node>)));
    connect( runing,SIGNAL(setExpisInputing(bool)),exp,SLOT(setisInputing(bool)));
    connect( exp,SIGNAL(com(int,QString)),runing,SLOT(com(int,QString)));
    connect( Console,SIGNAL(newLineWritten(QString)),runing,SLOT(getInput(QString)));
}

void basic::quit()
{
    this->close();
}

