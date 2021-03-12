#include "window.h"

window::window(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("函数调用关系分析");
    this->setFixedSize(1600,1200);
    file = new Console(this);
    analysis = new Console(this);

    file->setGeometry(100, 200, 600, 900);
    analysis->setGeometry(900, 200, 600, 900);

    button1= new button(this);
    button1->setText("选择文件");
    button1->setGeometry(350,50,100,50);
    button2 = new button0(this);
    button2->setText("分析调用");
    button2->setGeometry(1150,50,100,50);

    connect( button1,SIGNAL( write(QString) ),file,SLOT( write(QString) ) );
    connect( button2,SIGNAL( write(QString) ),analysis,SLOT( write(QString) ) );
    connect( button1,SIGNAL( savename(QString) ),button2,SLOT( savename(QString) ) );

}
