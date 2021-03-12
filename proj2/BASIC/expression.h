/*
 * File: exp.h
 * -----------
 * This interface defines a class hierarchy for arithmetic expressions.
 */
#ifndef EXP_H
#define EXP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <string>
#include <QMap>
#include <list>
#include <iostream>
#include "console.h"
using namespace std;

enum statement{REM, LET, PRINT, INPUT, GOTO, IF, END};
enum command{RUN, LIST, CLEAR, HELP, QUIT , LET1, PRINT1, INPUT1};

class expression : public QObject
{
    Q_OBJECT
protected:

    struct node//map中的值
    {
        statement s;
        QString movement;
        node(statement s=statement::REM,QString movement="")
        {
            this->s=s;
            this->movement=movement;
        }
    };

    bool isInputing;
    QMap<int,node> map;//map中存键值对
    QMap<int,QString> listmap;//用于list操作的maps
    list<int> valid;//记录用户输入的expression是否合法，哪一行不合法

signals:
    void writeToConsole(QString msg);
    void quit();
    void run(QMap<int,node> map);
    void com(int com,QString movement);
public slots:
    void getExpression(QString expression);
    void validfailed();
    void setisInputing(bool is);
public:
    expression();
    ~expression(){}

};

#endif // EXP_H
