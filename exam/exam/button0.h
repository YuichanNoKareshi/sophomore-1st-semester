#ifndef BUTTON0_H
#define BUTTON0_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <list>
using namespace std;
class button0: public QPushButton
{
    Q_OBJECT
public:
    button0(QWidget *parent = nullptr):QPushButton(parent)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
        filename="";
    }
    QString filename;
    QString mainfunc;
    void Analysis();

    struct node{
        QString name;
        QString function;
        node (QString a,QString b) {name=a;function=b;}
    };

    list<node> List;
    void call(QString func,int depth);




private slots:
    void OnClicked()
    {
        QString str;
        str = "You press " + this->text();
        QMessageBox::information(this, tr("Information"), str);
        Analysis();
    }
    void savename(QString filename)
    {
        this->filename=filename;
    }
signals:
    void write(QString word);
};



#endif // BUTTON0_H
