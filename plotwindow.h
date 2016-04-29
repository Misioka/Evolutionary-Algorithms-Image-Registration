#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include "structs.h"
#include "plot.h"
#include <QMainWindow>
#include <QPoint>
#include <QDebug>
#include <QSemaphore>
#include <QMouseEvent>
#include <QtConcurrent/QtConcurrent>
#include <QFileDialog>
#include <qmath.h>

#include <vector>
#include <matio.h>
#include <iostream>
#include <armadillo>
#include <random>

using namespace std;
using namespace arma;

namespace Ui {
class PlotWindow;
}

struct vector3d {
    int x;
    int y;
    int z;
    uint val;
};

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    vector<frame_t> *preProcessed = new vector<frame_t>();
    vector<transform_t> *sa = new vector<transform_t>();
    QPoint *roi = new QPoint[2];
    transform_t *res = new transform_t();
    transform_t boundTransform = new transform_t(0, 30, 30, 10);
    vec *thcnt = new vec(1);
    QElapsedTimer totalTimer;
    uint totalTime = 0;
    uint computedTimes = 0;
    uint criteriaOfSimilarity = 0;
    uint algorithm = 0;
    QTimer *timer;
    bool animate = false;

    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();

    void translate(mat &mat, int tx, int ty);
    void rotate(mat &mat, int delta);
    //void registerFrames(frame_t first, frame_t second, QPoint *roi, transform_t *tr);

private slots:
    void drawImage();
    void cntThrds();
    void animateReg();

    void on_openFile_clicked();

    void on_transImage_valueChanged(int value);
    void drawRoi();
    void drawRoiEnd();

    void on_nextFrame_released();

    void on_Compute_released();

    void on_computeOne_released();

    void on_channelsRadio_released();

    void on_checkerboardRadio_released();

    void on_showRoi_released();

    void on_NMI_released();

    void on_NED_released();

    void on_NCD_released();

    void on_BFA_released();

    void on_SAA_released();

    void on_CFA_released();

    void on_NCC_released();

    void on_SOMA_released();

    void on_prevFrame_released();

    void on_FA_released();

    void on_ABC_released();

    void on_goodReg_released();

    void on_badReg_released();

    void on_animate_released();

    void on_ES_released();

private:
    Ui::PlotWindow *ui;
    void enableUi(bool enable);
    vector<vector3d> frames = vector<vector3d>();
    uint currentFrame = 0;
    uint width = 0;
    uint height = 0;
    uint zCnt = 0;
    uint imageTrans = 1;
    bool allComputed = false;
    bool readError = false;

    void readVariable(QString varName, mat_t *mat, QUrl fileUrl);
    void plotData(QUrl fileUrl);
    void readMatCell(matvar_t *matvar, uint z);
    void printNumber(enum matio_types type, void *data, uint x, uint y, uint z);

    int roundDown(uint number, uint divider);
    int hex2int(QString hexNumber);
};

#endif // PLOTWINDOW_H
