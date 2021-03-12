#include "Cube.h"

#include <QHBoxLayout>

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    label = new QLabel();
    label->setText("");
    label->setAlignment(Qt::AlignCenter);//居中
    QFont font = label->font();
    font.setPointSize(33);
    label->setFont(font);

    this->setFixedSize(120, 120);

    this->setStyleSheet("background-color:white; border-radius: 15px; border: 2px solid");
    QHBoxLayout *layout = new QHBoxLayout();//水平布局
    layout->addWidget(label);
    setLayout(layout);


}

void Cube::setLetter(QString l)
{
    label->setText(l);
}

