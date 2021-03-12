#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "button.h"
#include "button0.h"
#include "console.h"



class window: public QMainWindow
{
    Q_OBJECT
public:
    window(QWidget *parent = 0);
    ~window(){}
    Console *file;
    Console *analysis;
    button *button1;
    button0 *button2;
};

#endif // WINDOW_H
