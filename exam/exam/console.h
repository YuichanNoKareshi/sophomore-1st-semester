#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>

class Console : public QTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

signals:
    void newLineWritten(QString newline);

public slots:
    void reset();
    void write(QString word);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // CONSOLE_H
