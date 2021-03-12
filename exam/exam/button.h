#ifndef BUTTON_H
#define BUTTON_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>

class button: public QPushButton
{
    Q_OBJECT
public:
    button(QWidget *parent = nullptr):QPushButton(parent)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(OnClicked()));
    }

    QString filename;
signals:
    void write(QString word);
    void savename(QString filename);
private slots:
    void OnClicked();
};



#endif // BUTTON_H
