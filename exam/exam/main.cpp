/*#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}*/
#include "window.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window w;
    w.show();

    return a.exec();
}
