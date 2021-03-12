#include "Board.h"
#include "Cube.h"

#include <cstdlib>
#include <QGridLayout>
#include <windows.h>
#include <QTime>


const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{
    this->size = size;//默认值为5
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];
    this->lett = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        this->letters[i] = cubeLetters[i];//cubeLetters默认值是big cube，QString[25].把CUBES的string传进letters

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(20);//20
    layout->setSpacing(10);//10
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);//index返回i*size+j
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
        }
    }
    setLayout(layout);


    shake();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->lett[index(i, j)]);
        }
    }


    polishlett(this->lett,this->size);//让me和computer更新lett
    // this->setStyleSheet("background-color:grey; border: 3px solid");
}

Board::~Board()
{
    if (cubes) delete[] cubes;
    if (letters) delete[] letters;
}

void Board::shake()
{
    // Shake Cubes

    //先换cubes
    SYSTEMTIME sys;
    GetLocalTime( &sys );

    unsigned seed=10;
    int random[25];
    for(int i=0; i<25; i++)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+seed);
        seed+=10;
        random[i]=qrand();//生成了25个随机数
    }

    for (int i=0;i<size*size;i++)
    {
        int left=size*size-i;//i到最后一个数之间有多少数
        int r=i+random[i]%left;//生成在i到最后一个数之间的某个数
        QString temp=letters[r];
        letters[r]=letters[i];
        letters[i]=temp;
    }

    for(int i=0; i<25; i++)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+seed);
        seed+=20;
        random[i]=qrand();//又生成了25个随机数
    }

    //换完cubes的位置，换6个面
    for (int i=0;i<25;i++)
    {
        int temp=random[i]%6;
        lett[i]=letters[i].at(temp);//lett记录了每个朝上的字母
        if (lett[i]=="Q") lett[i].append("U");
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->lett[index(i, j)]);
        }
    }


}

void Board::polish()
{
    shake();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->lett[index(i, j)]);
        }
    }
    // this->setStyleSheet("background-color:grey; border: 3px solid");
    polishlett(lett,this->size);//让me和computer更新lett
}
