#include "ConfigurationWindow.h"
#include "CubeEdit.h"
#include "BoggleWindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QString>
#include <QMessageBox>

ConfigurationWindow::ConfigurationWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("Board Configuration");
    setFixedSize(WIDTH, HEIGHT);
    setAttribute(Qt::WA_DeleteOnClose);

    this->boardEdit = new BoardEdit(this);

    QPushButton *customButton = new QPushButton("Start With Custom Configuration", this);
    QPushButton *defaultButton = new QPushButton("Start With Default Configuration", this);
    customButton->setFixedSize(500, 50);
    defaultButton->setFixedSize(500, 50);
    connect(customButton, &QPushButton::clicked, this, &ConfigurationWindow::startWithCustom);
    connect(defaultButton, &QPushButton::clicked, this, &ConfigurationWindow::startWithDefault);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(boardEdit, 0, Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(customButton, 0, Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(defaultButton, 0, Qt::AlignmentFlag::AlignCenter);
    setLayout(layout);
}

ConfigurationWindow::~ConfigurationWindow() {
}

void ConfigurationWindow::startWithCustom() {
    QString *cubeLetters = boardEdit->cubeLetters();
    if (!cubeLetters) {
        QMessageBox::warning(this, "Wrong Input", "More letters are needed.", QMessageBox::Ok, QMessageBox::Ok);
    } else {
        close();
        BoggleWindow *boggleWindow = new BoggleWindow(cubeLetters);
        boggleWindow->show();
    }
    delete[] cubeLetters;
}

void ConfigurationWindow::startWithDefault() {
    close();
    BoggleWindow *boggleWindow = new BoggleWindow;
    boggleWindow->show();
}
