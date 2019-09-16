#include "CubeEdit.h"
#include <QFont>
#include <QKeyEvent>
#include <QChar>

CubeEdit::CubeEdit(QWidget *parent): QLineEdit(parent) {
    setFixedSize(100, 40);
    QFont font = this->font();
    font.setPointSize(12);
    setFont(font);
}

CubeEdit::~CubeEdit() {
}

void CubeEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) {
        if (text().length() < 6)
            insert(event->text().toUpper());
    } else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        QLineEdit::keyPressEvent(event);
}
