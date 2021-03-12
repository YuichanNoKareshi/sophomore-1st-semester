#ifndef CONSOLE_H
#define CONSOLE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTextEdit>

class console : public QTextEdit
{
    Q_OBJECT
public:
    explicit console(QWidget *parent = nullptr);

signals:
    void newLineWritten(QString newline);

public slots:
    void reset();
    void write(QString msg);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // CONSOLE_H
