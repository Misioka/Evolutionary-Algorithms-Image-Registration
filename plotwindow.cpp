#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "dialog.h"

using namespace arma;

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    enableUi(false);
    ui->openFile->setEnabled(true);
    ui->prevFrame->setEnabled(false);
    ui->goodReg->setEnabled(false);
    ui->badReg->setEnabled(false);
    ui->animate->setEnabled(false);
    ui->badReg->setVisible(false);

    roi[0].setX(80);
    roi[0].setY(50);
    roi[1].setX(120);
    roi[1].setY(70);


    ui->transfom->setText(QString("Total time:\t0")+ QString("\tms\n") +
                          QString("Average time:\t0") + QString("\tms\n") +
                          QString("Frame time:\t0") + QString("\tms\n") +
                          QString("Average sim.:\t0") + QString("\t%\n") +
                          QString("Tx:\t\t0") + QString("\tpx\n") +
                          QString("Ty:\t\t0") + QString("\tpx\n") +
                          QString("Tr:\t\t0") + QString("\tdeg\n") +
                          QString("Frame:\t\t0") + QString("\n") +
                          QString("Similarity:\t0") + QString("\t\n") +
                          QString("Iterations:\t0"));
    ui->criteria->setText(QString("Criterium:\t"));

    ui->info->setText(QString("Frames: \t0\n") +
                      QString("File: \t"));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animateReg()));

    connect(ui->histo, SIGNAL(mousePos()), this, SLOT(drawRoi()));
    connect(ui->histo, SIGNAL(mouseReleased()), this, SLOT(drawRoiEnd()));
}

void mutualInformation(vector<frame_t> *frames, regdata_t frame, QPoint *roi, transform_t tr, transform_t *res) {
    int tx = tr.tx;
    int ty = tr.ty;
    int rot = tr.tr;
    QImage secImage;
    if (rot != 0) {
        QTransform rotate;
        rotate.rotate(rot);
        secImage = QImage(frames->at(frame.frame).image->transformed(rotate));
    } else {
        secImage = *frames->at(frame.frame).image;
    }
    mat joinH;
    joinH.resize(256, 256);
    vector<double> secondHistogram;
    secondHistogram.resize(256);
    vector<double> firstHistogram;
    firstHistogram.resize(256);
    int cyg, cxg;
    int width = frames->at(frame.firstFrame).image->width();
    int height = frames->at(frame.firstFrame).image->height();
    uint count = 0;
    for (int py = roi[0].y(); py < roi[1].y(); py++) {
        for (int px = roi[0].x(); px < roi[1].x(); px++) {
            if (px+tx > 0 && px+tx < width &&
                py+ty > 0 && py+ty < height) {
                cyg = qRed(secImage.pixel(px+tx, py+ty));
            } else {
                cyg = 0;
            }
            cxg = qRed(frames->at(frame.firstFrame).image->pixel(px, py));
            joinH(cxg, cyg)++;
            secondHistogram.at(cyg)++;
            firstHistogram.at(cxg)++;
            count++;
        }
    }
    double sP = 0;
    double sPs = 0;
    double fP = 0;
    double fPs = 0;
    for (uint n = 0; n < secondHistogram.size(); n++) {
        sP = secondHistogram.at(n);
        if (sP > 0) {
            sP /= count;
            sP *= log(sP);
            sPs += sP;
        }
        fP = firstHistogram.at(n);
        if (fP > 0) {
            fP /= count;
            fP *= log(fP);
            fPs += fP;
        }
    }
    fPs *= -1;
    sPs *= -1;

    double Hab = 0;
    double Habe = 0;
    for (uint n = 0; n < joinH.n_elem; n++) {
        Habe = joinH.at(n);
        if (Habe != 0) {
            Habe /= count;
            Habe *= log(Habe);
            Hab += Habe;
        }
    }
    Hab *= -1;

    double sim = 1;
    if (Hab > 0) {
        sim = (fPs + sPs) / Hab / 2.0;
    }
    res->tx = tx;
    res->ty = ty;
    res->tr = rot;
    res->sim = sim;
    res->Ha = fPs;
}

void euclideanDistance(vector<frame_t> *frames, regdata_t frame, QPoint *roi, transform_t tr, transform_t *res) {
    int tx = tr.tx;
    int ty = tr.ty;
    int rot = tr.tr;
    QImage secImage;
    if (rot != 0) {
        QTransform rotate;
        rotate.rotate(rot);
        secImage = QImage(frames->at(frame.frame).image->transformed(rotate));
    } else {
        secImage = *frames->at(frame.frame).image;
    }
    double cyg, cxg, cxyg;
    double ed = 0;
    int width = frames->at(frame.firstFrame).image->width();
    int height = frames->at(frame.firstFrame).image->height();
    int count = 0;
    for (int py = roi[0].y(); py < roi[1].y(); py++) {
        for (int px = roi[0].x(); px < roi[1].x(); px++) {
            if (px+tx > 0 && px+tx < width &&
                py+ty > 0 && py+ty < height) {
                cyg = qRed(secImage.pixel(px+tx, py+ty)) / 255.0;
            } else {
                cyg = 0;
            }
            cxg = qRed(frames->at(frame.firstFrame).image->pixel(px, py)) / 255.0;
            cxyg = ((cxg - cyg)*(cxg - cyg));
            ed += cxyg;
            count++;
        }
    }
    res->tx = tx;
    res->ty = ty;
    res->tr = rot;
    res->sim = 1 - (sqrt(ed) / sqrt(count));
    res->Ha = 0;
}

void cosineDistance(vector<frame_t> *frames, regdata_t frame, QPoint *roi, transform_t tr, transform_t *res) {
    int tx = tr.tx;
    int ty = tr.ty;
    int rot = tr.tr;
    QImage secImage;
    if (rot != 0) {
        QTransform rotate;
        rotate.rotate(rot);
        secImage = QImage(frames->at(frame.frame).image->transformed(rotate));
    } else {
        secImage = *frames->at(frame.frame).image;
    }
    double cyg, cxg;
    double totalSum = 0;
    double powSumFirst = 0;
    double powSumSecond = 0;
    int width = frames->at(frame.firstFrame).image->width();
    int height = frames->at(frame.firstFrame).image->height();
    uint count = 0;
    for (int py = roi[0].y(); py < roi[1].y(); py++) {
        for (int px = roi[0].x(); px < roi[1].x(); px++) {
            if (px+tx > 0 && px+tx < width &&
                py+ty > 0 && py+ty < height) {
                cyg = qRed(secImage.pixel(px+tx, py+ty)) / 255.0;
            } else {
                cyg = 0;
            }
            cxg = qRed(frames->at(frame.firstFrame).image->pixel(px, py)) / 255.0;
            totalSum += (cyg) * (cxg);
            powSumFirst += (cxg) * (cxg);
            powSumSecond += (cyg) * (cyg);
            count++;
        }
    }
    res->tx = tx;
    res->ty = ty;
    res->tr = rot;
    res->sim = totalSum / (sqrt(powSumFirst) * sqrt(powSumSecond));
    res->Ha = 0;
}

void crossCorelation(vector<frame_t> *frames, regdata_t frame, QPoint *roi, transform_t tr, transform_t *res) {
    int tx = tr.tx;
    int ty = tr.ty;
    int rot = tr.tr;
    QImage secImage;
    if (rot != 0) {
        QTransform rotate;
        rotate.rotate(rot);
        secImage = QImage(frames->at(frame.frame).image->transformed(rotate));
    } else {
        secImage = *frames->at(frame.frame).image;
    }
    double firstAvg = 0;
    double secondAvg = 0;
    double firstStd = 0;
    double secondStd = 0;
    double size = (roi[1].y() - roi[0].y()) * (roi[1].x() - roi[0].x());
    int width = frames->at(frame.firstFrame).image->width();
    int height = frames->at(frame.firstFrame).image->height();
    for (int py = roi[0].y(); py < roi[1].y(); py++) {
        for (int px = roi[0].x(); px < roi[1].x(); px++) {
            if (px+tx > 0 && px+tx < width &&
                py+ty > 0 && py+ty < height) {
                secondAvg += qRed(secImage.pixel(px+tx, py+ty));
            }
            firstAvg += qRed(frames->at(frame.firstFrame).image->pixel(px, py));
        }
    }
    firstAvg = (firstAvg / size) / 255.0;
    secondAvg = (secondAvg / size) / 255.0;
    for (int py = roi[0].y(); py < roi[1].y(); py++) {
        for (int px = roi[0].x(); px < roi[1].x(); px++) {
            if (px+tx > 0 && px+tx < width &&
                py+ty > 0 && py+ty < height) {
                secondStd += (pow((qRed(secImage.pixel(px+tx, py+ty)) / 255.0) - secondAvg, 2));
            }
            firstStd += (pow((qRed(frames->at(frame.firstFrame).image->pixel(px, py)) / 255.0) - firstAvg, 2));
        }
    }
    firstStd = sqrt(firstStd / size);
    secondStd = sqrt(secondStd / size);
    double cyg = 0;
    for (int py = roi[0].y(); py < roi[1].y(); py++) {
        for (int px = roi[0].x(); px < roi[1].x(); px++) {
            if (px+tx > 0 && px+tx < width &&
                py+ty > 0 && py+ty < height) {
                cyg = qRed(secImage.pixel(px+tx, py+ty)) / 255.0;
            } else {
                cyg = 0;
            }
            res->sim += (((qRed(frames->at(frame.firstFrame).image->pixel(px, py)) / 255.0) - firstAvg) * ((cyg) - secondAvg)) / (firstStd * secondStd);
        }
    }
    res->tx = tx;
    res->ty = ty;
    res->tr = rot;
    res->sim = res->sim / size;
    res->Ha = 0;
}

void registerFrames(vector<frame_t> *frames, regdata_t frame, QPoint *roi, transform_t tr, transform_t *res) {
    switch (frame.criteriaOfSimilarity) {
        case 1:
            euclideanDistance(frames, frame, roi, tr, res);
            break;
        case 2:
            cosineDistance(frames, frame, roi, tr, res);
            break;
        case 3:
            crossCorelation(frames, frame, roi, tr, res);
            break;
        default:
            mutualInformation(frames, frame, roi, tr, res);
    }
}

void transform(transform_t &in) {
    double r = (double)rand() / RAND_MAX;
    r -= 0.5;
    in.tx = r*60;
    r = (double)rand() / RAND_MAX;
    r -= 0.5;
    in.ty = r*60;
    r = (double)rand() / RAND_MAX;
    r -= 0.5;
    in.tr = r*10;
}

transform_t threadRegFramesBf(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    double r = (double)rand() / RAND_MAX;
    r -= 0.5;
    transform_t sa = transform_t(-1, r*30, r*30, r*10);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);
    for (int x = -1*frame.boundTransform.tx; x <= frame.boundTransform.tx; x++) {
        for (int y = -1*frame.boundTransform.ty; y <= frame.boundTransform.ty; y++) {
            for (int tr = -1*frame.boundTransform.tr; tr <= frame.boundTransform.tr; tr++) {
                transform_t sat = transform_t(0, x, y, tr);
                registerFrames(frames, frame, roi, sat, res);
                if (sa.sim < res->sim) {
                    sa.sim = res->sim;
                    sa.tx = res->tx;
                    sa.ty = res->ty;
                    sa.tr = res->tr;
                    sa.Ha = res->Ha;
                }
            }
        }
    }
    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = frame.boundTransform.tx * 2 * frame.boundTransform.ty * 2 * frame.boundTransform.tr * 2;
    sa.criterium = "Iterations " + QString::number(sa.iters);
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    //qDebug() << sa.sim << sa.Ha << sa.tx << " " << sa.ty << " " << sa.tr << " frame: " << frame.frame;
    return sa;
}

transform_t threadRegFramesSa(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    double r = (double)rand() / RAND_MAX;
    r -= 0.5;
    transform_t sa = transform_t(-1, r*frame.boundTransform.tx, r*frame.boundTransform.ty, r*frame.boundTransform.tr);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);

    double iters = 0;
    double maxIters = 100000;
    double minSim = 0.99;
    double T0 = 10;
    double T;
    while (iters < maxIters && sa.sim < minSim) {
        transform_t sat = transform_t(0, sa.tx, sa.ty, sa.tr);
        transform(sat);
        registerFrames(frames, frame, roi, sat, res);
        if (sa.sim < res->sim) {
            sa.sim = res->sim;
            sa.tx = res->tx;
            sa.ty = res->ty;
            sa.tr = res->tr;
            sa.Ha = res->Ha;
        } else {
            double r = (double)rand() / RAND_MAX;
            T = T0 * (1- iters / maxIters);
            double rr = exp(-(abs(sa.sim-res->sim)/T));
            if (r < rr) {
                sa.sim = res->sim;
                sa.tx = res->tx;
                sa.ty = res->ty;
                sa.tr = res->tr;
                sa.Ha = res->Ha;
            }
        }
        iters++;
    }
    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = iters;
    if (iters == maxIters) {
        sa.criterium = "Iterations " + QString::number(maxIters);
    } else if (sa.sim > minSim) {
        sa.criterium = "Similarity";
    } else {
        sa.criterium = "Unknown reason";
    }
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    //qDebug() << sa.sim << sa.Ha << sa.tx << " " << sa.ty << " " << sa.tr << " frame: " << frame.frame;
    return sa;
}

transform_t threadRegFramesFa(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    transform_t sa = transform_t(0, 0, -4, 0);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);
    uint Nffs = 20;
    //registerFrames(frames, frame, roi, sa, res);
    //qDebug() << res->sim;

    vector<transform_t> ffs = vector<transform_t>(Nffs);
    for (uint i = 0; i < Nffs; i++) {
        ffs.at(i).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
        ffs.at(i).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
        ffs.at(i).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
        registerFrames(frames, frame, roi, ffs.at(i), res);
        ffs.at(i).sim = res->sim;
        //qDebug() << ffs.at(i).sim << " " << ffs.at(i).tx << " " << ffs.at(i).ty << " " << ffs.at(i).tr << " ffly: " << i;
        if (sa.sim < ffs.at(i).sim) {
            sa = ffs.at(i);
            sa.Ha = i;
        }
    }

    double r = 0;
    double B = 1;
    double a = 0.5;
    double e = 1;
    double y = 0.08;

    double dispersion = 1;
    uint iters = 0;

    uint maxIters = 200;
    double dispersionTresh = 0.005;
    double minSim = 0.9999;

    double maxR = sqrt(pow(frame.boundTransform.tx*2, 2) + pow(frame.boundTransform.ty*2, 2) + pow(frame.boundTransform.tr*2, 2));

    while (iters < maxIters && sa.sim < minSim && dispersion > dispersionTresh) {
        for (uint i = 0; i < Nffs; i++) {
            for (uint j = 0; j < Nffs; j++) {
                r = sqrt(pow(ffs.at(i).tx - ffs.at(j).tx, 2) + pow(ffs.at(i).ty - ffs.at(j).ty, 2) + pow(ffs.at(i).tr - ffs.at(j).tr, 2));
                dispersion += r / maxR / Nffs;
                if (ffs.at(i).sim > ffs.at(j).sim) {
                    //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << i;
                    ffs.at(j).tx = ffs.at(j).tx + B*exp(-y*r)*(ffs.at(i).tx - ffs.at(j).tx) + a*e;
                    ffs.at(j).ty = ffs.at(j).ty + B*exp(-y*r)*(ffs.at(i).ty - ffs.at(j).ty) + a*e;
                    ffs.at(j).tr = ffs.at(j).tr + B*exp(-y*r)*(ffs.at(i).tr - ffs.at(j).tr) + a*e;
                    if ((ffs.at(j).tx == sa.tx && ffs.at(j).ty == sa.ty && ffs.at(j).tr == sa.tr) ||
                        (ffs.at(j).tx == ffs.at(i).tx && ffs.at(j).ty == ffs.at(i).ty && ffs.at(j).tr == ffs.at(i).tr)) {
                        ffs.at(j).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
                        ffs.at(j).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
                        ffs.at(j).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
                        //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << i;
                    }
                    registerFrames(frames, frame, roi, ffs.at(j), res);
                    ffs.at(j).sim = res->sim;
                    if (sa.sim < res->sim) {
                        sa = ffs.at(j);
                        sa.Ha = j;
                    }
                    if (sa.sim > minSim) {
                        break;
                    }
                    //qDebug() << ffs.at(i).sim << " " << ffs.at(i).tx << " " << ffs.at(i).ty << " " << ffs.at(i).tr << " ffly: " << i;
                    //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << j;
                }
                if (sa.sim > minSim) {
                    break;
                }
            }
            if (sa.sim > minSim) {
                break;
            }
            dispersion -= 1;
            if (dispersion < dispersionTresh) {
                break;
            } else {
                dispersion = 1;
            }
        }
        iters++;
    }

    /*for (uint i = 0; i < Nffs; i++) {
        //qDebug() << (sa.sim < ffs.at(i).sim) << ffs.at(i).sim << " " << ffs.at(i).tx << " " << ffs.at(i).ty << " " << ffs.at(i).tr << " ffly: " << i;
        if (sa.sim < ffs.at(i).sim) {
            sa = ffs.at(i);
            sa.Ha = i;
        }
    }*/

    //qDebug() << sa.sim << " " << sa.tx << " " << sa.ty << " " << sa.tr << " ffly: " << sa.Ha << " it " << iters << dispersion;
    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = iters;
    if (iters == maxIters) {
        sa.criterium = "Iterations " + QString::number(maxIters);
    } else if (sa.sim > minSim) {
        sa.criterium = "Similarity";
    } else if (dispersion < dispersionTresh) {
        sa.criterium = "Dispersion " + QString::number(dispersion);
    } else {
        sa.criterium = "Unknown reason";
    }
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    return sa;
}

transform_t threadRegFramesCfa(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    transform_t sa = transform_t(0, 0, -4, 0);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);
    uint Nffs = 20;
    //registerFrames(frames, frame, roi, sa, res);
    //qDebug() << res->sim;

    vector<transform_t> ffs = vector<transform_t>(Nffs);
    for (uint i = 0; i < Nffs; i++) {
        ffs.at(i).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
        ffs.at(i).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
        ffs.at(i).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
        registerFrames(frames, frame, roi, ffs.at(i), res);
        ffs.at(i).sim = res->sim;
        //qDebug() << ffs.at(i).sim << " " << ffs.at(i).tx << " " << ffs.at(i).ty << " " << ffs.at(i).tr << " ffly: " << i;
        if (sa.sim < ffs.at(i).sim) {
            sa = ffs.at(i);
            sa.Ha = i;
        }
    }

    double r = 0;
    double B = 1;
    double a = 0.5;
    double e = 1;
    double y = 0.2;
    double uy = 4;
    double ua = uy;

    double dispersion = 1;
    uint iters = 0;

    uint maxIters = 20;
    double dispersionTresh = 0.005;
    double minSim = 0.995;

    double maxR = sqrt(pow(frame.boundTransform.tx*2, 2) + pow(frame.boundTransform.ty*2, 2) + pow(frame.boundTransform.tr*2, 2));

    while (iters < maxIters && sa.sim < minSim && dispersion > dispersionTresh) {
        for (uint i = 0; i < Nffs; i++) {
            for (uint j = 0; j < Nffs; j++) {
                r = sqrt(pow(ffs.at(i).tx - ffs.at(j).tx, 2) + pow(ffs.at(i).ty - ffs.at(j).ty, 2) + pow(ffs.at(i).tr - ffs.at(j).tr, 2));
                dispersion += r / maxR / Nffs;
                if (ffs.at(i).sim > ffs.at(j).sim) {
                    //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << i;
                    ffs.at(j).tx = ffs.at(j).tx + B*exp(-y*r)*(ffs.at(i).tx - ffs.at(j).tx) + a*e;
                    ffs.at(j).ty = ffs.at(j).ty + B*exp(-y*r)*(ffs.at(i).ty - ffs.at(j).ty) + a*e;
                    ffs.at(j).tr = ffs.at(j).tr + B*exp(-y*r)*(ffs.at(i).tr - ffs.at(j).tr) + a*e;
                    if ((ffs.at(j).tx == sa.tx && ffs.at(j).ty == sa.ty && ffs.at(j).tr == sa.tr) ||
                        (ffs.at(j).tx == ffs.at(i).tx && ffs.at(j).ty == ffs.at(i).ty && ffs.at(j).tr == ffs.at(i).tr)) {
                        ffs.at(j).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
                        ffs.at(j).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
                        ffs.at(j).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
                        //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << i;
                    }
                    registerFrames(frames, frame, roi, ffs.at(j), res);
                    ffs.at(j).sim = res->sim;
                    if (sa.sim < res->sim) {
                        sa = ffs.at(j);
                        sa.Ha = j;
                    }
                    if (sa.sim > minSim) {
                        break;
                    }
                    y = uy * y * (1 - y);
                    a = ua * a * (1 - a);
                    //qDebug() << ffs.at(i).sim << " " << ffs.at(i).tx << " " << ffs.at(i).ty << " " << ffs.at(i).tr << " ffly: " << i;
                    //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << j;
                }
                if (sa.sim > minSim) {
                    break;
                }
            }
            if (sa.sim > minSim) {
                break;
            }
            dispersion -= 1;
            if (dispersion < dispersionTresh) {
                break;
            } else {
                dispersion = 1;
            }
        }
        iters++;
    }

    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = iters;
    if (iters == maxIters) {
        sa.criterium = "Iterations " + QString::number(maxIters);
    } else if (sa.sim > minSim) {
        sa.criterium = "Similarity";
    } else if (dispersion < dispersionTresh) {
        sa.criterium = "Dispersion " + QString::number(dispersion);
    } else {
        sa.criterium = "Unknown reason";
    }
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    return sa;
}

transform_t threadRegFramesSoma(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    transform_t sa = transform_t(0, 0, -4, 0);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);
    uint N = 10;
    //registerFrames(frames, frame, roi, sa, res);
    //qDebug() << res->sim;

    vector<transform_t> pop = vector<transform_t>(N);
    for (uint i = 0; i < N; i++) {
        pop.at(i).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
        pop.at(i).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
        pop.at(i).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
        registerFrames(frames, frame, roi, pop.at(i), res);
        pop.at(i).sim = res->sim;
        //qDebug() << pop.at(i).sim << " " << pop.at(i).tx << " " << pop.at(i).ty << " " << pop.at(i).tr << " ffly: " << i;
        if (sa.sim < pop.at(i).sim) {
            sa = pop.at(i);
            sa.Ha = i;
        }
    }

    double mass = 1.1;
    double step = 0.11;
    uint nSteps = floor(mass/step);

    uint iters = 0;
    uint maxIters = 1000;
    double minSim = 0.995;

    while (iters < maxIters && sa.sim < minSim) {
        for (uint j = 0; j < N; j++) {
            if (j != sa.Ha) {
                //qDebug() << ffs.at(j).sim << " " << ffs.at(j).tx << " " << ffs.at(j).ty << " " << ffs.at(j).tr << " ffly: " << i;
                int r = round(rand() / RAND_MAX * 6);
                for (uint i = 0; i < nSteps; i++) {
                    switch(r) {
                        case 0:
                                pop.at(j).tx = round(pop.at(j).tx + ((sa.tx - pop.at(j).tx) * step));
                            break;
                        case 1:
                                pop.at(j).ty = round(pop.at(j).ty + ((sa.ty - pop.at(j).ty) * step));
                            break;
                        case 2:
                                pop.at(j).tr = round(pop.at(j).tr + ((sa.tr - pop.at(j).tr) * step));
                            break;
                        case 3:
                                pop.at(j).tx = round(pop.at(j).tx + ((sa.tx - pop.at(j).tx) * step));
                                pop.at(j).ty = round(pop.at(j).ty + ((sa.ty - pop.at(j).ty) * step));
                            break;
                        case 4:
                                pop.at(j).ty = round(pop.at(j).ty + ((sa.ty - pop.at(j).ty) * step));
                                pop.at(j).tr = round(pop.at(j).tr + ((sa.tr - pop.at(j).tr) * step));
                            break;
                        case 5:
                                pop.at(j).tx = round(pop.at(j).tx + ((sa.tx - pop.at(j).tx) * step));
                                pop.at(j).tr = round(pop.at(j).tr + ((sa.tr - pop.at(j).tr) * step));
                                break;
                        case 6:
                                pop.at(j).tx = round(pop.at(j).tx + ((sa.tx - pop.at(j).tx) * step));
                                pop.at(j).ty = round(pop.at(j).ty + ((sa.ty - pop.at(j).ty) * step));
                                pop.at(j).tr = round(pop.at(j).tr + ((sa.tr - pop.at(j).tr) * step));
                            break;
                    }
                    registerFrames(frames, frame, roi, pop.at(j), res);
                    pop.at(j).sim = res->sim;
                    if (pop.at(j).sim > sa.sim) {
                        sa = pop.at(j);
                        sa.Ha = j;
                    }
                }
                //qDebug() << sa.sim << " " << sa.tx << " " << sa.ty << " " << sa.tr << " ffly: " << sa.Ha;
                //qDebug() << pop.at(j).sim << " " << pop.at(j).tx << " " << pop.at(j).ty << " " << pop.at(j).tr << " ffly: " << j;
            }
        }
        iters++;
    }

    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = iters;
    if (iters == maxIters) {
        sa.criterium = "Iterations " + QString::number(maxIters);
    } else if (sa.sim > minSim) {
        sa.criterium = "Similarity";
    } else {
        sa.criterium = "Unknown reason";
    }
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    //qDebug() << sa.sim << " " << sa.tx << " " << sa.ty << " " << sa.tr << " ffly: " << sa.Ha << " it " << iters;
    return sa;
}

transform_t threadRegFramesAbc(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    transform_t sa = transform_t(0, 0, -4, 0);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);
    uint N = 10;

    vector<transform_t> pop = vector<transform_t>(N/2);
    for (uint i = 0; i < N/2; i++) {
        pop.at(i).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
        pop.at(i).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
        pop.at(i).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
        registerFrames(frames, frame, roi, pop.at(i), res);
        pop.at(i).sim = res->sim;
        if (sa.sim < pop.at(i).sim) {
            sa = pop.at(i);
            sa.Ha = i;
        }
    }

    uint iters = 0;
    uint maxIters = 1000;
    double minSim = 0.99;

    transform_t v;
    uint j, k;
    uint T = round(N*3/2);
    vector<uint> beeCounter = vector<uint>(N/2);
    vector<double> p = vector<double>(N/2);
    double w;
    double fitSum = 0;

    while (iters < maxIters && sa.sim < minSim) {
        for (uint i = 0; i < N/2; i++) {
            j = round((double)rand() / RAND_MAX * 2);
            k = round((double)rand() / RAND_MAX * ((N/2)-1));
            w = -1 + ((double)rand() / RAND_MAX * 2);
            switch(j) {
                case 0:
                    v.tx = pop.at(i).tx + w * (pop.at(i).tx - pop.at(k).tx);
                    v.ty = pop.at(i).ty;
                    v.tr = pop.at(i).tr;
                    break;
                case 1:
                    v.tx = pop.at(i).tx;
                    v.ty = pop.at(i).ty + w * (pop.at(i).ty - pop.at(k).ty);
                    v.ty = pop.at(i).ty;
                    break;
                case 2:
                    v.tx = pop.at(i).tx;
                    v.ty = pop.at(i).ty;
                    v.tr = pop.at(i).tr + w * (pop.at(i).tr - pop.at(k).tr);
                    break;
            }
            registerFrames(frames, frame, roi, v, res);
            if (pop.at(i).sim < res->sim) {
                pop.at(i) = v;
                pop.at(i).sim = res->sim;
                beeCounter.at(i) = 0;
                if (sa.sim < pop.at(i).sim) {
                    sa = pop.at(i);
                }
            } else {
                beeCounter.at(i)++;
            }
            fitSum += pop.at(i).sim;
        }

        for (uint i = 0; i < N/2; i++) {
            p.at(i) = pop.at(i).sim / fitSum;
        }
        sort(p.begin(), p.end());

        for (uint i = 0; i < N/2; i++) {
            double randP = ((double)rand() / RAND_MAX);
            uint randBee = 0;
            for (uint i = 0; i < N/2; i++) {
                if (randP - p.at(i) <= 0) {
                    randBee = i;
                    break;
                }
            }
            j = round((double)rand() / RAND_MAX * 2);
            k = round((double)rand() / RAND_MAX * ((N/2)-1));
            w = -1 + ((double)rand() / RAND_MAX * 2);
            switch(j) {
                case 0:
                    v.tx = pop.at(randBee).tx + w * (pop.at(randBee).tx - pop.at(k).tx);
                    v.ty = pop.at(randBee).ty;
                    v.tr = pop.at(randBee).tr;
                    break;
                case 1:
                    v.tx = pop.at(randBee).tx;
                    v.ty = pop.at(randBee).ty + w * (pop.at(randBee).ty - pop.at(k).ty);
                    v.ty = pop.at(randBee).ty;
                    break;
                case 2:
                    v.tx = pop.at(randBee).tx;
                    v.ty = pop.at(randBee).ty;
                    v.tr = pop.at(randBee).tr + w * (pop.at(randBee).tr - pop.at(k).tr);
                    break;
            }
            registerFrames(frames, frame, roi, v, res);
            if (pop.at(randBee).sim < res->sim) {
                pop.at(randBee) = v;
                pop.at(randBee).sim = res->sim;
                beeCounter.at(i) = 0;
                if (sa.sim < pop.at(i).sim) {
                    sa = pop.at(i);
                }
            } else {
                beeCounter.at(i)++;
            }
        }
        for (uint i = 0; i < N/2; i++) {
            if (beeCounter.at(i) >= T) {
                pop.at(i).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
                pop.at(i).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
                pop.at(i).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
                registerFrames(frames, frame, roi, pop.at(i), res);
                pop.at(i).sim = res->sim;
                if (sa.sim < pop.at(i).sim) {
                    sa = pop.at(i);
                }
            }
        }
        iters++;
    }

    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = iters;
    if (iters == maxIters) {
        sa.criterium = "Iterations " + QString::number(maxIters);
    } else if (sa.sim > minSim) {
        sa.criterium = "Similarity";
    } else {
        sa.criterium = "Unknown reason";
    }
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    //qDebug() << sa.sim << " " << sa.tx << " " << sa.ty << " " << sa.tr << " ffly: " << sa.Ha << " it " << iters;
    return sa;
}

bool sortTransformT(transform_t i, transform_t j) {
    return (i.sim < j.sim);
}

transform_t threadRegFramesEs(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    transform_t sa = transform_t(0, 0, -4, 0);
    QElapsedTimer timer;
    timer.start();
    transform_t *res = new transform_t(0, 0, 0, 0);
    uint N = 5;
    uint L = 7*N;

    vector<transform_t> pop = vector<transform_t>(N);
    for (uint i = 0; i < N; i++) {
        pop.at(i).tx = -1*frame.boundTransform.tx + (double)rand() / RAND_MAX * 2*frame.boundTransform.tx;
        pop.at(i).ty = -1*frame.boundTransform.ty + (double)rand() / RAND_MAX * 2*frame.boundTransform.ty;
        pop.at(i).tr = -1*frame.boundTransform.tr + (double)rand() / RAND_MAX * 2*frame.boundTransform.tr;
        registerFrames(frames, frame, roi, pop.at(i), res);
        pop.at(i).sim = res->sim;
        if (sa.sim < pop.at(i).sim) {
            sa = pop.at(i);
            sa.Ha = i;
        }
    }

    uint j;
    uint iters = 0;
    uint maxIters = 10000;
    double minSim = 0.99;

    vector<transform_t> lpop = vector<transform_t>(L+N);
    double w;
    double sigmaTx = 2.2;
    double sigmaTy = 2.2;
    double sigmaTr = 1.6;
    double phi = 0.2;
    double c = 0.95;

    default_random_engine generator;
    normal_distribution<double> distributionTx(0, sigmaTx);
    normal_distribution<double> distributionTy(0, sigmaTy);
    normal_distribution<double> distributionTr(0, sigmaTr);

    while (iters < maxIters && sa.sim < minSim) {
        for (uint i = 0; i < L; i++) {
            j = floor(i/7);
            w = distributionTx(generator);
            lpop.at(i).tx = pop.at(j).tx + w;
            w = distributionTy(generator);
            lpop.at(i).ty = pop.at(j).ty + w;
            w = distributionTr(generator);
            lpop.at(i).tr = pop.at(j).tr + w;
            registerFrames(frames, frame, roi, lpop.at(i), res);
            lpop.at(i).sim = res->sim;
            if (pop.at(j).sim < lpop.at(j).sim) {
                sa = lpop.at(i);
                phi += 1.0 / L;
            } else {
                phi -= 1.0 / L;
            }
            if (phi < 0.2) {
                sigmaTx *= c;
                sigmaTy *= c;
                sigmaTr *= c;
                distributionTx = normal_distribution<double>(0, sigmaTx);
                distributionTy = normal_distribution<double>(0, sigmaTy);
                distributionTr = normal_distribution<double>(0, sigmaTr);
            } else if (phi > 0.2) {
                sigmaTx /= c;
                sigmaTy /= c;
                sigmaTr /= c;
                distributionTx = normal_distribution<double>(0, sigmaTx);
                distributionTy = normal_distribution<double>(0, sigmaTy);
                distributionTr = normal_distribution<double>(0, sigmaTr);
            }
        }
        for (uint i = 0; i < N; i++) {
            lpop.at(L+i) = pop.at(i);
        }
        sort(lpop.begin(), lpop.end(), sortTransformT);
        for (uint i = 0; i < N; i++) {
            pop.at(i) = lpop.at(i);
            if (sa.sim < lpop.at(i).sim) {
                sa = lpop.at(i);
            }
        }
        iters++;
    }

    sa.time = timer.elapsed();
    sa.frame = frame.frame;
    sa.iters = iters;
    if (iters == maxIters) {
        sa.criterium = "Iterations " + QString::number(maxIters);
    } else if (sa.sim > minSim) {
        sa.criterium = "Similarity";
    } else {
        sa.criterium = "Unknown reason";
    }
    trs->at(frame.frame) = sa;
    thcnt->at(frame.frame) = 1;
    return sa;
}

transform_t threadRegFrames(vector<frame_t> *frames, regdata_t frame, QPoint *roi, vector<transform_t> *trs, vec *thcnt) {
    transform_t ret;
    switch (frame.algorithm) {
        case 1:
            ret =  threadRegFramesSa(frames, frame, roi, trs, thcnt);
            break;
        case 2:
            ret =  threadRegFramesFa(frames, frame, roi, trs, thcnt);
            break;
        case 3:
            ret =  threadRegFramesCfa(frames, frame, roi, trs, thcnt);
            break;
        case 4:
            ret =  threadRegFramesSoma(frames, frame, roi, trs, thcnt);
            break;
        case 5:
            ret =  threadRegFramesAbc(frames, frame, roi, trs, thcnt);
            break;
        case 6:
            ret =  threadRegFramesEs(frames, frame, roi, trs, thcnt);
            break;
        default:
            ret =  threadRegFramesBf(frames, frame, roi, trs, thcnt);
    }
    return ret;
}

void PlotWindow::enableUi(bool enable) {
    ui->transImage->setEnabled(enable);
    ui->channelsRadio->setEnabled(enable);
    ui->checkerboardRadio->setEnabled(enable);
    ui->computeOne->setEnabled(enable);
    ui->Compute->setEnabled(enable);
    ui->nextFrame->setEnabled(enable);
    ui->showRoi->setEnabled(enable);
    ui->openFile->setEnabled(enable);
    ui->tofirstFrame->setEnabled(enable);
    ui->toprevFrame->setEnabled(enable);
    ui->NMI->setEnabled(enable);
    ui->NED->setEnabled(enable);
    ui->NCD->setEnabled(enable);
    ui->NCC->setEnabled(enable);
    ui->BFA->setEnabled(enable);
    ui->SAA->setEnabled(enable);
    ui->CFA->setEnabled(enable);
    ui->FA->setEnabled(enable);
    ui->SOMA->setEnabled(enable);
    ui->ABC->setEnabled(enable);
    ui->ES->setEnabled(enable);
    ui->goodReg->setEnabled(enable);
    ui->badReg->setEnabled(enable);
}

int PlotWindow::hex2int(QString hexNumber) {
    uint x;
    std::stringstream ss;
    ss << std::hex << hexNumber.toStdString();
    ss >> x;
    return static_cast<int>(x);
}

int PlotWindow::roundDown(uint number, uint divider) {
    int remainder = number % divider;
    number = number - remainder;
    return number / divider;
}

void PlotWindow::readVariable(QString varName, mat_t *mat, QUrl fileUrl) {
    currentFrame = 0;
    width = 0;
    height = 0;
    zCnt = 0;
    imageTrans = 0;
    preProcessed = new vector<frame_t>();
    matvar_t *matvar = 0;

    matvar = Mat_VarRead(mat, varName.toStdString().c_str()) ;
    if(matvar) {
        readMatCell(matvar, 0);
    }
    Mat_Close(mat);

    if (this->frames.size() > 0 && !this->readError) {
        ui->transfom->setText(QString("Total time:\t-")+ QString("\tms\n") +
                              QString("Average time:\t-") + QString("\tms\n") +
                              QString("Frame time:\t-") + QString("\tms\n") +
                              QString("Average sim.:\t-") + QString("\t%\n") +
                              QString("Tx:\t\t-") + QString("\tpx\n") +
                              QString("Ty:\t\t-") + QString("\tpx\n") +
                              QString("Tr:\t\t-") + QString("\tdeg\n") +
                              QString("Frame:\t\t-") + QString("\t\n") +
                              QString("Similarity:\t-") + QString("\t\n") +
                              QString("Iterations:\t-"));
        ui->criteria->setText(QString("Criterium:\t-"));

        ui->info->setText(QString("Frames: \t") + QString::number(this->zCnt) + QString("\n") +
                          QString("File: \t") + fileUrl.fileName() + QString("\n") +
                          QString("Variable: \t") + varName);

        this->sa->resize(this->zCnt);
        preProcessed->resize(this->zCnt);

        int fr = 0;
        bool initiate = true;
        ui->progressBar->setMaximum(this->frames.size());
        ui->progressBar->setFormat(QString("Preprocessing data: %p%"));
        ui->progressBar->setValue(0);
        for (uint f = 0; f < this->frames.size(); f++) {
            if (this->frames.at(f).z != fr) {
                initiate = true;
                fr++;
            }
            if (initiate) {
                initiate = false;
                preProcessed->at(fr).image = new QImage(this->width, this->height, QImage::Format_RGB32);
            }
            preProcessed->at(fr).image->setPixel(this->frames.at(f).x, this->frames.at(f).y, qRgb(this->frames.at(f).val, this->frames.at(f).val, this->frames.at(f).val));

            if ((uint)ui->progressBar->value()+1000 < f) {
                ui->progressBar->setValue(f);
            }
        }
        ui->progressBar->setValue(100);
        ui->progressBar->setMaximum(100);
        drawImage();
    } else {
        ui->progressBar->setMaximum(1);
        ui->progressBar->setValue(1);
        ui->info->setText(QString("Frames: \t0\n") +
                          QString("File ") + fileUrl.fileName() + QString(" has invalid file format. Expecting data1 variable with cell of 2D images UINT8."));
    }
}

void PlotWindow::plotData(QUrl fileUrl) {
    this->frames = vector<vector3d>();
    enableUi(false);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setValue(0);
    ui->progressBar->setFormat(QString("Reading file: %p%"));
    mat_t *mat = Mat_Open(fileUrl.toString().replace(0, 7, "").toStdString().c_str(), MAT_ACC_RDONLY);
    if(mat) {
        matvar_t *matvar=0;
        QStringList options;
        while ((matvar = Mat_VarReadNextInfo(mat)) != NULL) {
            options.append(QString(matvar->name));
            Mat_VarFree(matvar);
            matvar = NULL;
        }
        if (options.size() > 1) {
            Dialog *chooseVar = new Dialog;
            chooseVar->setRadiosButtons(options);
            if (chooseVar->exec()) {
                readVariable(chooseVar->getCheckedRadio(), mat, fileUrl);

            } else {
                ui->progressBar->setMaximum(1);
                ui->progressBar->setValue(1);
                ui->info->setText(QString("Frames: \t0\n") +
                                  QString("File ") + fileUrl.fileName() + QString(". No variable selected."));
            }
        } else {
            readVariable(options.at(0), mat, fileUrl);
        }
    } else {
        ui->progressBar->setMaximum(1);
        ui->progressBar->setValue(1);
        ui->info->setText(QString("Frames: \t0\n") +
                          QString("File ") + fileUrl.fileName() + QString(" can't open file."));
    }
}

PlotWindow::~PlotWindow() {
    delete ui;
}

void PlotWindow::drawImage() {
    ui->transImage->setVisible(true);
    ui->histo->clearRectangle();

    ui->progressBar->setFormat(QString("Done: %p%"));
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);

    enableUi(true);

    uint firstFrame = 0;

    if (currentFrame > 0) {
        ui->prevFrame->setEnabled(true);
        if (ui->toprevFrame->isChecked()) {
            firstFrame = this->currentFrame - 1;
        }
        if (currentFrame >= this->zCnt -1) {
            ui->nextFrame->setEnabled(false);
        } else {
            ui->nextFrame->setEnabled(true);
        }
    } else {
        ui->prevFrame->setEnabled(false);
    }

    if (this->sa->at(currentFrame).well) {
        ui->goodReg->setVisible(false);
        ui->badReg->setVisible(true);
    } else {
        ui->goodReg->setVisible(true);
        ui->badReg->setVisible(false);
    }

    uint avgTime = 0;
    double avgSim = 0;
    uint cnt = this->sa->size();
    for (uint i = 0; i < cnt; i++) {
        avgTime += (double)this->sa->at(i).time / cnt;
        avgSim += this->sa->at(i).sim / cnt;
    }

    res = new transform_t(this->sa->at(this->currentFrame));
    ui->transfom->setText(QString("Total time:\t") + QString::number(totalTime) + QString("\tms\n") +
                          QString("Average time:\t") + QString::number(avgTime) + QString("\tms\n") +
                          QString("Frame time:\t") + QString::number(res->time) + QString("\tms\n") +
                          QString("Average sim.:\t") + QString::number(avgSim * 100, 'f', 2) + QString("\t%\n") +
                          QString("Tx:\t\t") + QString::number(res->tx) + QString("\tpx\n") +
                          QString("Ty:\t\t") + QString::number(res->ty) + QString("\tpx\n") +
                          QString("Tr:\t\t") + QString::number(res->tr) + QString("\tdeg\n") +
                          QString("Frame:\t\t") + QString::number(res->frame) + QString("\t\n") +
                          QString("Similarity:\t") + QString::number(res->sim * 100, 'f', 2) + QString("\t%\n") +
                          QString("Iterations:\t") + QString::number(res->iters));
    ui->criteria->setText(QString("Criterium: ") + res->criterium);

    QTransform trans;
    trans.rotate(res->tr);

    QImage last;
    if (this->zCnt > this->currentFrame) {
        last = preProcessed->at(this->currentFrame).image->transformed(trans);
    } else {
        last = preProcessed->at(0).image->transformed(trans);
        ui->nextFrame->setEnabled(true);
    }

    QImage mutualImage = QImage(this->width * 2, this->height * 2, QImage::Format_RGB32);
    mutualImage.fill(QColor("black"));
    QRgb aPixel, bPixel;
    uint gray;
    uint alpha;

    QString chbFile = QString(":/checkerboard.png");
    QImage checkerboard = QImage(chbFile);

    if (ui->checkerboardRadio->isChecked()) {
        QTransform scale;
        scale.scale(qreal((double)(imageTrans+255)/255.0), qreal((double)(imageTrans+255)/255.0));
        checkerboard = checkerboard.transformed(scale);
        ui->transImage->setEnabled(true);
    } else {
        ui->transImage->setEnabled(false);
    }

    for (uint x = 0; x < this->width; x++) {
        for (uint y = 0; y < this->height; y++) {
            aPixel = preProcessed->at(firstFrame).image->pixel(x, y);
            if (ui->channelsRadio->isChecked()) {
                mutualImage.setPixel(x+100, y+100, qRgb(0, qGreen(aPixel), 0));
            } else {
                mutualImage.setPixel(x+100, y+100, aPixel);
            }
        }
    }

    for (int x = 0; x < last.width(); x++) {
        for (int y = 0; y < last.height(); y++) {
            bPixel = last.pixel(x, y);
            alpha = qAlpha(bPixel);
            if (ui->channelsRadio->isChecked()) {
                aPixel = mutualImage.pixel(x+100-res->tx, y+100-res->ty);
                aPixel = qRgba(0, qGreen(aPixel), 0, 128);
                bPixel = qRgba(qRed(bPixel), 0, 0, 127);
                bPixel = aPixel + bPixel;
            } else {
                gray = qRed(checkerboard.pixel(x+100-res->tx, y+100-res->ty));
                if (gray == 0) {
                    continue;
                }
            }
            if (alpha > 0) {
                mutualImage.setPixel(x+100-res->tx, y+100-res->ty, bPixel);
            }
        }
    }

    if (ui->showRoi->isChecked()) {
        ui->label->clearRectangle();
        ui->label->drawRectangle(100+roi[0].x(), 100+roi[0].y(), 100+roi[1].x(), 100+roi[1].y());
        ui->histo->clearRectangle();
        ui->histo->drawRectangle(roi[0].x(), roi[0].y(), roi[1].x(), roi[1].y());
    } else {
        ui->label->clearRectangle();
        ui->histo->clearRectangle();
    }

    ui->label->setMaximumSize(QSize(mutualImage.width(), mutualImage.height()));
    ui->histo->setMaximumSize(QSize(last.width(), last.height()));

    ui->label->setPixmap(QPixmap::fromImage(mutualImage));
    ui->histo->setPixmap(QPixmap::fromImage(last));

    ui->nextFrame->setEnabled(true);
}


void PlotWindow::readMatCell(matvar_t *matvar, uint z) {
    size_t nmemb;
    uint i, j;

    if ( matvar == NULL )
        return;
    nmemb = matvar->dims[0];
    for ( i = 1; i < (uint)matvar->rank; i++ ) {
        nmemb *= matvar->dims[i];
    }
    if ( MAT_C_CELL == matvar->class_type ) {
        matvar_t **cells = (matvar_t **)matvar->data;
        int ncells = matvar->nbytes / matvar->data_size;
        for ( i = 0; i < (uint)ncells; i++ ) {
            readMatCell(cells[i], i);
        }
        return;
    }


    if ( matvar->rank > 2 ) {
        printf("I can't print more than 2 dimensions\n");
    } else if ( matvar->rank==2 ) {
        switch( matvar->class_type ) {
            case MAT_C_DOUBLE:
            case MAT_C_SINGLE:
            case MAT_C_INT32:
            case MAT_C_UINT32:
            case MAT_C_INT16:
            case MAT_C_UINT16:
            case MAT_C_INT8:
            case MAT_C_UINT8:
            {
               size_t stride = Mat_SizeOf(matvar->data_type);
               char *data = static_cast<char *>(matvar->data);
               for ( i = 0; i < matvar->dims[0]; i++ ) {
                    for ( j = 0; j < matvar->dims[1]; j++ ) {
                        size_t idx = matvar->dims[0]*j+i;
                        printNumber(matvar->data_type, data+idx*stride, i, j, z);
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}

void PlotWindow::printNumber(enum matio_types type, void *data, uint x = 0, uint y = 0, uint z = 0) {
    uchar varm = 0;
    if (this->width <= x) {
        this->width = x+1;
    }
    if (this->height <= y) {
        this->height = y+1;
    }
    if (this->zCnt <= z) {
        this->zCnt = z+1;
    }

    vector3d zyx;
    zyx.x = x;
    zyx.y = y;
    zyx.z = z;
    switch ( type ) {
        case MAT_T_UINT8:
            varm = *(uchar*)data;
            zyx.val = static_cast<int>(varm);
            this->frames.push_back(zyx);
            break;
        default:
            this->readError = true;
            break;
    }
}

void PlotWindow::animateReg() {
    if (this->currentFrame < this->zCnt - 1) {
        this->currentFrame++;
    } else {
        this->currentFrame = 1;
    }
    drawImage();
}

void PlotWindow::on_openFile_clicked()
{
    QUrl fileUrl = QFileDialog::getOpenFileUrl(this, tr("Open Matlab file"), QUrl("/"), tr("Matlab (*.mat)"));
    plotData(fileUrl);
}

void PlotWindow::on_transImage_valueChanged(int value)
{
    imageTrans = value;
    drawImage();
}

void PlotWindow::drawRoi() {
    ui->histo->clearRectangle();
    ui->histo->drawRectangle(ui->histo->xStart, ui->histo->yStart, ui->histo->x, ui->histo->y);
}

void PlotWindow::drawRoiEnd() {
    roi[0].setX(ui->histo->xStart);
    roi[0].setY(ui->histo->yStart);
    roi[1].setX(ui->histo->xEnd);
    roi[1].setY(ui->histo->yEnd);
    ui->histo->clearRectangle();
    ui->histo->drawRectangle(ui->histo->xStart, ui->histo->yStart, ui->histo->xEnd, ui->histo->yEnd);
    ui->label->clearRectangle();
    ui->label->drawRectangle(100+ui->histo->xStart, 100+ui->histo->yStart, 100+ui->histo->xEnd, 100+ui->histo->yEnd);
}

void PlotWindow::cntThrds() {
    ui->progressBar->setValue(sum(*thcnt));
    if (sum(*thcnt) >= this->zCnt-1) {
        totalTime = totalTimer.elapsed();
        ui->progressBar->setValue(100);
        ui->progressBar->setMaximum(100);
        ui->nextFrame->setEnabled(false);
        ui->nextFrame->setText(tr("Next frame"));
        drawImage();
    }
}

void PlotWindow::on_prevFrame_released()
{
    if (this->currentFrame > 0) {
        this->currentFrame--;
        drawImage();
    }
}

void PlotWindow::on_nextFrame_released()
{
    if (this->currentFrame < this->zCnt-1) {
        this->currentFrame++;
        if (allComputed == true) {
            drawImage();
        } else {
            enableUi(false);
            ui->progressBar->setFormat(QString("Computing frame: " + QString::number(this->currentFrame)));
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(0);
            ui->progressBar->setValue(0);
            regdata_t frame;
            frame.frame = this->currentFrame;
            frame.criteriaOfSimilarity = this->criteriaOfSimilarity;
            frame.algorithm = this->algorithm;
            if (ui->toprevFrame->isChecked()) {
                frame.firstFrame = this->currentFrame - 1;
            } else {
                frame.firstFrame = 0;
            }
            frame.boundTransform = this->boundTransform;
            QFutureWatcher<void> *wt = new QFutureWatcher<void>;
            wt->setFuture(QtConcurrent::run(threadRegFrames, this->preProcessed, frame, this->roi, this->sa, this->thcnt));
            connect(wt, SIGNAL(finished()), this, SLOT(drawImage()));
        }
    }
}

void PlotWindow::on_Compute_released()
{
    thcnt->resize(this->zCnt);
    thcnt->zeros(this->zCnt);
    ui->progressBar->setFormat(QString("Computing registration: %p%"));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(this->zCnt);
    ui->progressBar->setValue(0);
    ui->computeOne->setEnabled(false);
    ui->nextFrame->setEnabled(false);
    QThreadPool::globalInstance()->setMaxThreadCount(8);
    uint cf = 1;
    enableUi(false);
    totalTimer.start();
    while (cf < this->zCnt) {
        regdata_t frame;
        frame.frame = cf;
        frame.criteriaOfSimilarity = this->criteriaOfSimilarity;
        frame.algorithm = this->algorithm;
        if (ui->toprevFrame->isChecked()) {
            frame.firstFrame = cf - 1;
        } else {
            frame.firstFrame = 0;
        }
        frame.boundTransform = this->boundTransform;
        QFutureWatcher<void> *wt = new QFutureWatcher<void>;
        wt->setFuture(QtConcurrent::run(threadRegFrames, this->preProcessed, frame, this->roi, this->sa, this->thcnt));
        connect(wt, SIGNAL(finished()), this, SLOT(cntThrds()));
        cf++;
    }
    allComputed = true;
    ui->prevFrame->setEnabled(true);
    ui->animate->setEnabled(true);
}

void PlotWindow::on_computeOne_released()
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setValue(0);
    enableUi(false);
    regdata_t frame;
    frame.frame = this->currentFrame;
    frame.criteriaOfSimilarity = this->criteriaOfSimilarity;
    frame.algorithm = this->algorithm;
    if (ui->toprevFrame->isChecked()) {
        frame.firstFrame = this->currentFrame - 1;
    } else {
        frame.firstFrame = 0;
    }
    frame.boundTransform = this->boundTransform;
    QFutureWatcher<void> *wt = new QFutureWatcher<void>;
    wt->setFuture(QtConcurrent::run(threadRegFrames, this->preProcessed, frame, this->roi, this->sa, this->thcnt));
    connect(wt, SIGNAL(finished()), this, SLOT(drawImage()));
}

void PlotWindow::on_channelsRadio_released()
{
    drawImage();
}

void PlotWindow::on_checkerboardRadio_released()
{
    drawImage();
}

void PlotWindow::on_showRoi_released()
{
    drawImage();
}

void PlotWindow::on_NMI_released()
{
    this->criteriaOfSimilarity = 0;
}

void PlotWindow::on_NED_released()
{
    this->criteriaOfSimilarity = 1;
}

void PlotWindow::on_NCD_released()
{
    this->criteriaOfSimilarity = 2;
}

void PlotWindow::on_NCC_released()
{
    this->criteriaOfSimilarity = 3;
}

void PlotWindow::on_BFA_released()
{
    this->algorithm = 0;
}

void PlotWindow::on_SAA_released()
{
    this->algorithm = 1;
}

void PlotWindow::on_FA_released()
{
    this->algorithm = 2;
}

void PlotWindow::on_CFA_released()
{
    this->algorithm = 3;
}

void PlotWindow::on_SOMA_released()
{
    this->algorithm = 4;
}

void PlotWindow::on_ABC_released()
{
    this->algorithm = 5;
}

void PlotWindow::on_ES_released()
{
    this->algorithm = 6;
}

void PlotWindow::on_goodReg_released()
{
    this->sa->at(this->currentFrame).well = true;
    ui->goodReg->setVisible(false);
    ui->badReg->setVisible(true);
}

void PlotWindow::on_badReg_released()
{
    this->sa->at(this->currentFrame).well = false;
    ui->goodReg->setVisible(true);
    ui->badReg->setVisible(false);
}

void PlotWindow::on_animate_released()
{
    if (timer->isActive()) {
        timer->stop();
    } else {
        timer->start(200);
    }
}
