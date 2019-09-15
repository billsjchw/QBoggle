#include "Cube.h"

#include <QHBoxLayout>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    button = new QPushButton();
    button->setText("");
    QFont font = button->font();
    font.setPointSize(20);
    button->setFont(font);
    cancel();
    connect(button, &QPushButton::clicked, this, &Cube::clicked);

    this->setFixedSize(75, 75);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(button);
    setLayout(layout);
}

void Cube::setLetter(QChar l)
{
    if (l == 'Q')
        button->setText("Qu");
    else
        button->setText(l);
}

void Cube::select() {
    button->setStyleSheet("background-color: black; color: white; border-radius: 15px; border: 2px solid");
}

void Cube::cancel() {
    button->setStyleSheet("background-color: white; color: black; border-radius: 15px; border: 2px solid");
}

