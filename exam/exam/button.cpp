#include "button.h"

void button::OnClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框！"),"F:",tr("文本文件(*txt *sep);;"));
    filename=fileName;
    savename(fileName);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray  t= file.readAll();
    file.close();
    write(t);

}
