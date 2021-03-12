#include "mainwindow.h"
#include <QApplication>
#include "basic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    basic w;
    w.show();

    return a.exec();
}
