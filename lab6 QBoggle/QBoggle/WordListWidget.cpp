#include "WordListWidget.h"
#include "WordTable.h"
#include "Board.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
using namespace std;

WordListWidget::WordListWidget(QWidget *parent, QString label) : QWidget(parent)
{

    isPass=new bool [size*size];
    for (int i=0;i<size*size;i++)
    {
        isPass[i]=false;
    }


    reset();

    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *headLayout = new QHBoxLayout();

    QLabel *nameLabel = new QLabel(this);
    scoreLabel = new QLabel(this);
    QFont font = nameLabel->font();
    font.setPointSize(25);
    nameLabel->setFont(font);
    scoreLabel->setFont(font);
    nameLabel->setText(label);
    scoreLabel->setText(QString::number(score));

    headLayout->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignLeft);
    headLayout->addWidget(scoreLabel, 0, Qt::AlignmentFlag::AlignRight);
    layout->addLayout(headLayout);

    QFrame *hline = new QFrame();
    hline->setFrameShape(QFrame::HLine);
    hline->setFrameShadow(QFrame::Sunken);
    layout->addWidget(hline);

    wordTable = new WordTable();
    layout->addWidget(wordTable);

    setLayout(layout);

    m_pTimer=new QTimer(this);
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(handleTimeout()));

}

void WordListWidget::addScore(int score)
{
    this->score += score;
    scoreLabel->setText(QString::number(this->score));
}

void WordListWidget::addWord(QString word)
{
    this->words.append(word);
    this->w1(word);
    this->wordTable->addWord(word);
}

void WordListWidget::reset()
{
    this->score = 0;
    this->words.clear();
}

void WordListWidget::megetword(QString word)
{
    for (int i=0;i<size*size;i++)
    {
        isPass[i]=false;
        setcubesbackground(i,false);
    }

    for (int i=0;i<word.length();i++)
        if (word.at(i).toLower()<'a' && word.at(i).toLower()>'z') return;

    string wordd=word.toStdString();
    bool accept=true;
    if (word.length()<=3) accept=false;
    if (!lexi.contains(wordd)) accept=false;

    bool isexist=false;
    for (int i=0;i<size*size;i++)
    {
        if ( lett[i]=="QU" && word.at(0).toLower()=="q" && word.at(1).toLower()=="u" )
        {
            isexist=isExist(word,1,i,word.length()-2);
            if (isexist == true) break;
            isPass[i]=false;
        }

        else if ( lett[i].toLower()==word.at(0).toLower() )
        {
            isexist=isExist(word,0,i,word.length()-1);
            if (isexist == true) break;
            isPass[i]=false;
        }

    }


    if (accept==true && isexist==true)
    {
        for (int i=0;i<size*size;i++)
        {
            if (isPass[i]==true) setcubesbackground(i,true);
        }
        m_pTimer->start(1500);

        this->addWord(word.toLower());
        this->addScore(word.length()-3);
        write("Good job!");
        write("/n");
    }
}

void WordListWidget::computergetword(QString word)
{
    if ( !(word.length()==1 && (word.at(0)=='#' || word.at(0)=='@')) ) return;

    if (word.at(0)=='#')//killer computer player
    {
        for (int i=0;i<size*size;i++)
        {
            isPass[i]=false;
        }

        QString letter="";
        for (int index=0;index<size*size;index++)
        {
            letter.append(lett[index].toLower());//把第i个cube上的字母的小写加入letter中
            isPass[index]=true;
            findnext(letter,index);

            if (letter=="qu") letter.remove(letter.length()-2,2);
            else letter.remove(letter.length()-1,1);
            isPass[index]=false;
        }

        write("Look how many words you missed? Go to study and never enter '@'!");
    }

    else if (word.at(0)=='@')
    {
        isPolish();
        this->polish();
        write("A new game!");
    }



}

bool WordListWidget::isExist(QString word,int which,int index,int left)//word记录单词，which记录第几个字母，index记录"which"字母的位置，left记录还余多少个字母
{
    isPass[index]=true;//index是“which”字母所在的位置，现在找“which+1”字母的位置
    if ( this->words.contains(word) ) return false;
    if (left==0) return true;



    for (int i=0;i<8;i++)
    {
        if ( index+arr[i]>=size*size || index+arr[i]<0 || isPass[ index+arr[i] ]==true ) continue;
        if ( index%5==0 && (i==0 || i==3 || i==5) ) continue;
        if ( index%5==4 && (i==2 || i==4 || i==7) ) continue;

        bool indexx;
        if (lett[ index+arr[i] ]=="QU" && word.at(which+1).toLower()=="q" && word.at(which+1).toLower()=="u")
            indexx=isExist(word,which+2,index+arr[i],left-2);
        else if (lett[ index+arr[i] ].toLower()==word.at(which+1).toLower()) indexx=isExist(word,which+1,index+arr[i],left-1);
        else continue;//如果index+arr[i]位置上找不到第“which+1”个字母，就下一个i

        if (indexx==false) {isPass[ index+arr[i] ]=false;continue;}
        else if (indexx==true) return true;//只有可能在最后一层等于true时才返回true
    }

    return false;//如果八个方位都找遍了还没有,就返回false
}

bool WordListWidget::isWord(const QString &letter)//看字典中有没有前缀
{
    string LETTER=letter.toStdString();
    if ( lexi.contains(LETTER) && this->words.contains(letter)==false && letter.length()>3)
    {this->addWord(letter);this->addScore(letter.length()-3);}//如果字典中有，就加入
    if (lexi.containsPrefix(LETTER)) return true;
    else return false;
}

void WordListWidget::findnext(QString &letter,int index)
{
    for (int j=0;j<8;j++)
    {
        if (index+arr[j]>=size*size || index+arr[j]<0 || isPass[ index+arr[j] ]==true) continue;
        if ( index%5==0 && (j==0 || j==3 || j==5)) continue;
        if ( index%5==4 && (j==2 || j==4 || j==7)) continue;

        letter.append(lett[ index+arr[j] ].toLower());
        isPass[ index+arr[j] ]=true;
        bool ISWORD=isWord(letter);

        bool qu=false;
        if (lett[ index+arr[j] ].toLower()=="qu") qu=true;
        if (ISWORD==false && qu==false) {letter.remove(letter.length()-1,1); isPass[ index+arr[j] ]=false; continue;}//字典中没有前缀,就去掉最后一个字母，继续找下一个j
        else if (ISWORD==false && qu==true) {letter.remove(letter.length()-2,2); isPass[ index+arr[j] ]=false; continue;}
        else if (ISWORD==true && qu==false) { findnext(letter,index+arr[j]); letter.remove(letter.length()-1,1); isPass[ index+arr[j] ]=false;}//加入本字母,然后继续找四周的下一个字母
        else if (ISWORD==true && qu==true) { findnext(letter,index+arr[j]); letter.remove(letter.length()-2,2); isPass[ index+arr[j] ]=false;}
    }
}

void WordListWidget::polishlett(QString *lett,int size)
{
    this->size=size;
    this->lett=new QString[size*size];
    for (int i=0;i<size*size;i++) this->lett[i]=lett[i];
}

void WordListWidget::polish()
{
    this->reset();
    this->scoreLabel->setText(QString::number(this->score));
    this->wordTable->polish();
}

void WordListWidget::handleTimeout()
{
    for (int i=0;i<size*size;i++)
    {
        isPass[i]=false;
        setcubesbackground(i,false);
    }
}

/*void WordListWidget::mousePressEventSlot(QMouseEvent *e)
{
    int x=e->x();    //e->x()属于500-1100，e->y()属于40-640
    int y=e->y();
    if (x<500 || x>1100 || y<40 || y>640 || clickedletters.length()>0)
    {clickedletters.remove(0,clickedletters.length());return;}//如果点的不是cubes，就清除已记录的letters

    x=(x-500)/120;
    y=(x-40)/120;
    clickedletters.append(lett[x*5+y].toLower());
    write(clickedletters);

    string cl=clickedletters.toStdString();
    if (cl.length()>3 && lexi.contains(cl))
    {
        this->addWord(clickedletters);
        this->addScore(clickedletters.length()-3);
        write(clickedletters);
    }
    if (lexi.containsPrefix(cl)==false)
    {
        write("You find a wrong word.");
        clickedletters.remove(0,clickedletters.length());//如果不含前缀就删掉
    }
}*/
