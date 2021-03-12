#include "console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

console::console(QWidget *parent) : QTextEdit(parent)
{
}

void console::reset()
{
    this->clear();
}

void console::write(QString msg)
{
    this->append(msg);
}

void console::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
    {
        QTextCursor cursor = this->textCursor();
        cursor.deletePreviousChar();
        return;
    }

    if (event->key() == Qt::Key_Delete)
    {
        QTextCursor cursor = this->textCursor();
        cursor.deleteChar();
        return;
    }
    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastLine = cursor.selectedText();
        newLineWritten(lastLine);//按回车前的一句话
    }
    QTextEdit::keyPressEvent(event);
}

