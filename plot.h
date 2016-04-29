#ifndef PLOT_H
#define PLOT_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QColor>
#include <QPaintEvent>
#include <QDebug>

#include <vector>

using namespace std;

class Plot : public QLabel
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    void drawRectangle(int xStart, int yStart, int xEnd, int yEnd);
    void clearRectangle();

    int x = 0;
    int y = 0;

    int xStart = 0;
    int yStart = 0;

    int xEnd = 0;
    int yEnd = 0;

private:
    vector<QRect> *rect = new vector<QRect>;

signals:
    void mousePressed();
    void mousePos();
    void mouseReleased();
};

#endif // PLOT_H
