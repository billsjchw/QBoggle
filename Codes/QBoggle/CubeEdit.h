#ifndef CUBEEDIT_H
#define CUBEEDIT_H

#include <QLineEdit>
#include <QString>

class CubeEdit: public QLineEdit {
public:
    explicit CubeEdit(QWidget *parent = nullptr);
    virtual ~CubeEdit();
private:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // CUBEEDIT_H
