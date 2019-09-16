#include "BoardEdit.h"
#include <QGridLayout>

BoardEdit::BoardEdit(QWidget *parent, int size): QWidget(parent) {
    this->size = size;
    this->cubeEdits = new CubeEdit*[size * size];
    for (int i = 0; i < size * size; ++i)
        cubeEdits[i] = new CubeEdit(this);
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            layout->addWidget(cubeEdits[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
    setLayout(layout);
}

BoardEdit::~BoardEdit() {
    delete [] cubeEdits;
}

QString * BoardEdit::cubeLetters() {
    for (int i = 0; i < size * size; ++i)
        if (cubeEdits[i]->text().length() < 6)
            return nullptr;
    QString *result = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        result[i] = cubeEdits[i]->text();
    return result;
}
