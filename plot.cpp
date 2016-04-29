#include "plot.h"
#include <QPainter>

Plot::Plot(QWidget *parent) : QLabel(parent)
{

}

void Plot::drawRectangle(int xStart, int yStart, int xEnd, int yEnd) {
    QRect a;
    a.setTopLeft(QPoint(xStart, yStart));
    a.setTopRight(QPoint(xEnd, yStart));
    a.setBottomRight(QPoint(xEnd, yEnd));
    a.setBottomLeft(QPoint(xStart, yEnd));
    this->rect->push_back(a);
    this->repaint();
}

void Plot::clearRectangle() {
    this->rect->clear();
}

void Plot::mouseMoveEvent(QMouseEvent *e) {
    this->x = e->localPos().x();
    this->y = e->localPos().y();
    emit mousePos();
}

void Plot::mousePressEvent(QMouseEvent *e) {
    this->xStart = e->localPos().x();
    this->yStart = e->localPos().y();
    emit mousePressed();
}

void Plot::mouseReleaseEvent(QMouseEvent *e) {
    this->xEnd = e->localPos().x();
    this->yEnd = e->localPos().y();
    if (this->xStart > this->xEnd) {
        int help = this->xStart;
        this->xStart = this->xEnd;
        this->xEnd = help;
    }
    if (this->yStart > this->yEnd) {
        int help = this->yStart;
        this->yStart = this->yEnd;
        this->yEnd = help;
    }
    emit mouseReleased();
}

void Plot::paintEvent(QPaintEvent *e) {
    QLabel::paintEvent(e);

    if (this->rect->size() > 0) {
        for (uint ind = 0; ind < this->rect->size(); ind++) {
            QPainter painter(this);
            QPen paintpen(Qt::red);
            paintpen.setWidth(1);
            painter.setPen(paintpen);
            painter.drawRect(this->rect->at(ind));
        }
    }
}
