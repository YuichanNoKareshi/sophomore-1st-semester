#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include <QTimer>
#include "WordTable.h"
#include "Board.h"
#include "lexicon.h"
#include <QWidget>


class WordListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WordListWidget(QWidget *parent = nullptr, QString label = "");
    void addScore(int s);
    void addWord(QString word);

    int whichNext(QChar a,int index);//判断一个字母是否在另一个字母的旁边
    bool isExist(QString word,int which,int index,int left);
    bool isWord(const QString &letter);//电脑判断board上的一个单词是否在lexicon中是前缀，有前缀返回true
    void findnext(QString &letter,int index);//找到可以构成前缀的下一次字母
    void reset();

    QLabel *scoreLabel;

    int size;
    Lexicon lexi;
    QString *lett;//记录每个cube朝上的单词
   // QString clickedletters="";
    bool *isPass;//记录棋盘上的某个字母在一个单词中是否已被包括进去了
    const int arr[8]={-6,-5,-4,-1,1,4,5,6};
    QList<QString> words;
    QTimer *m_pTimer;

signals:
    void w1(QString word);
    void isPolish();//要polish
    void write(QString msg);
    void setcubesbackground(int index,bool flag);
 //   void clicked(QMouseEvent *e);

public slots:
    void megetword(QString word);
    void computergetword (QString word);
    void w2(QString word) {this->words.append(word);}
    void polish();
    void polishlett(QString *lett,int size);
    void handleTimeout();//超时处理函数
//    void mousePressEventSlot(QMouseEvent *e);

private:


    QString label;
    int score;
    WordTable *wordTable;

};

#endif // WORDLISTWIDGET_H
