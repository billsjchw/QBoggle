#ifndef BOARDEDIT_H
#define BOARDEDIT_H

#include "CubeEdit.h"
#include <QWidget>

class BoardEdit: public QWidget {
public:
    BoardEdit(QWidget *parent = nullptr, int size = 5);
    virtual ~BoardEdit();
private:
    inline int index(int i, int j) { return i * size + j; }
    int size;
    CubeEdit **cubeEdits;
};

#endif // BOARDEDIT_H
