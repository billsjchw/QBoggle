#include "ConfigurationWindow.h"
#include "CubeEdit.h"

ConfigurationWindow::ConfigurationWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("Board Configuration");
    setFixedSize(800, 600);
    setAttribute(Qt::WA_DeleteOnClose);

    CubeEdit *cubeEdit = new CubeEdit(this);
}

ConfigurationWindow::~ConfigurationWindow() {
}
