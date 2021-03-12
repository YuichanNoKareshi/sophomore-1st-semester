#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"

#include <QWidget>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    void shake();


    QString *letters;
    QString *lett;//用来储存每个cube朝上面的字母
    int size;
    Cube **cubes;

signals:
    void polishlett(QString *lett,int size);
public slots:
    void polish();
private:
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];


    inline int index(int i, int j) { return i * size + j; }

};

#endif // BOARD_H
