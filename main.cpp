#include "plotwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlotWindow w;
    w.setWindowTitle("Image Registration ...");
    w.setWindowFlags(Qt::WindowMaximizeButtonHint);
    w.show();

    return a.exec();
}
