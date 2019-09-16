#include "ConfigurationWindow.h"
#include "CubeEdit.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QDebug>

ConfigurationWindow::ConfigurationWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("Board Configuration");
    setFixedSize(WIDTH, HEIGHT);
    setAttribute(Qt::WA_DeleteOnClose);

    this->boardEdit = new BoardEdit(this);

    QPushButton *customButton = new QPushButton("Start With Custom Configuration", this);
    QPushButton *defaultButton = new QPushButton("Start With Default Configuration", this);
    customButton->setFixedSize(500, 50);
    defaultButton->setFixedSize(500, 50);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(boardEdit, 0, Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(customButton, 0, Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(defaultButton, 0, Qt::AlignmentFlag::AlignCenter);
    setLayout(layout);
}

ConfigurationWindow::~ConfigurationWindow() {
}
