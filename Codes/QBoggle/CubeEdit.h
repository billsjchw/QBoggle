#ifndef CUBEEDIT_H
#define CUBEEDIT_H

#include <QTextEdit>
#include <QWidget>

class CubeEdit: public QTextEdit {
public:
    explicit CubeEdit(QWidget *parent = nullptr);
    virtual ~CubeEdit();
};

#endif // CUBEEDIT_H
