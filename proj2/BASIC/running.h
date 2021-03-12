#ifndef RUNNING_H
#define RUNNING_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMap>
#include <QEventLoop>
#include <list>
#include <iostream>
#include "expression.h"
using namespace std;

struct numnode
{

    numnode* left;
    numnode* right;
    int x;
    char s;

    numnode (int x=0,char s=' ',numnode* l=nullptr,numnode* r=nullptr)
    {
        this->x=x;
        this->s=s;
        left=l;
        right=r;
    }
    numnode():left(nullptr),right(nullptr) {}
    ~numnode () {}
};

struct opnode
{

    opnode* left;
    opnode* right;
    char s;

    opnode (char s,opnode* l=nullptr,opnode* r=nullptr)
    {
        this->s=s;
        left=l;
        right=r;
    }
    opnode():left(nullptr),right(nullptr) {}
    ~opnode () {}
};

/*class Tree
{
private:
    NODE* root;
public:
    Tree () {}
    Tree (NODE* root) {this->root=root;}
};*/

class running : public QObject
{
    Q_OBJECT
private:
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

    struct Node//list中的值
    {
        QString key;
        int value;
        Node (QString key,int value)
        {
            this->key=key;
            this->value=value;
        }
    };

    bool isInputing;
    QString Inputnum;//用户input的数
    QEventLoop loop;
    QMap<int,node> mapp;
    list<Node> List;
    list<numnode> numlist;//数字列表
    list<opnode> oplist;//操作符列表


public:
    running();
    ~running (){}
    bool isExpressionValid(QString expression);//用来检验表达式格式对不对
    bool isNodeExist(QString key0);
    int NodeValue(QString key0);
    bool pushop(char op);
    int mi(int a,int b);//乘方运算

    bool let_func(QString movement);
    bool if_func(bool &isTrue,int &des,QString movement);
    bool value_of(int &num,QString movemont);

public slots:
    void run(QMap<int,node> mapp);
    void getInput(QString word);
    void com(int c,QString movement);

signals:
    void validfailed();
    void writeToConsole(QString msg);
    void setExpisInputing(bool is);

};

#endif // RUNNING_H
