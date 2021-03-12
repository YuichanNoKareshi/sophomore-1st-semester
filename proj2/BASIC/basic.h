#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include "console.h"
#include "expression.h"
#include "running.h"
#include <cstdlib>
#include <cstring>
#include <QMainWindow>
using namespace std;

class basic : public QMainWindow
{
    Q_OBJECT
private:
    console *Console;
    expression *exp;
    running *runing;
    static const int BASIC_WINDOW_WIDTH = 800;
    static const int BASIC_WINDOW_HEIGHT = 1000;
public:
    basic(QWidget *parent = nullptr);
    ~basic(){}
public slots:
    void quit();
};
#endif // BASIC_H
