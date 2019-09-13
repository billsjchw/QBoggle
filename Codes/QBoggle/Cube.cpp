#include "Cube.h"

#include <QHBoxLayout>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    label = new QLabel();
    label->setText("");
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPointSize(20);
    label->setFont(font);
    cancel();

    this->setFixedSize(75, 75);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
}

void Cube::setLetter(QChar l)
{
    label->setText(l);
}

void Cube::select() {
    label->setStyleSheet("background-color: black; color: white; border-radius: 15px; border: 2px solid");
}

void Cube::cancel() {
    label->setStyleSheet("background-color: white; color: black; border-radius: 15px; border: 2px solid");
}

