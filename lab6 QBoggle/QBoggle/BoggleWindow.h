#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include "lexicon.h"
#include <QMainWindow>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>

class BoggleWindow : public QMainWindow
{
    Q_OBJECT

public:
    BoggleWindow(QWidget *parent = 0);
    ~BoggleWindow();
    void mousePressEvent(QMouseEvent *e)
    {
        emit this->clicked(e);
    }

signals:
    void clicked(QMouseEvent *e);

public slots:
    void mousePressEventSlot(QMouseEvent *e);
    void setcubesbackground(int index,bool flag);
private:
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    QString clickedletters="";
    int prex;
    int prey;//记录前一次点击的位置
    bool isFirst=true;//记录是否是第一次点击
    bool *isPass;

    Lexicon Lex;
    static const int BOGGLE_WINDOW_WIDTH = 1600;//全部乘以2
    static const int BOGGLE_WINDOW_HEIGHT = 1200;
};

#endif // BOGGLEWINDOW_H
