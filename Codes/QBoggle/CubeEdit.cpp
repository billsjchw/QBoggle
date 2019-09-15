#include "CubeEdit.h"
#include <QFont>

CubeEdit::CubeEdit(QWidget *parent): QTextEdit(parent) {
    setFixedSize(100, 40);
    QFont font = this->font();
    font.setPointSize(12);
    setFont(font);
}

CubeEdit::~CubeEdit() {
}
