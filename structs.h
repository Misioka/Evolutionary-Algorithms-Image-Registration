#ifndef STRUCTS
#define STRUCTS

#include <armadillo>
#include <QImage>
#include <vector>

using namespace arma;

class transform_t {
public:
    transform_t(double sim, int tx, int ty, int tr, int frame = 0) {
        this->sim = sim;
        this->frame = frame;
        this->tx = tx;
        this->ty = ty;
        this->tr = tr;
    }

    transform_t(transform_t *t) {
        this->sim = t->sim;
        this->frame = t->frame;
        this->tx = t->tx;
        this->ty = t->ty;
        this->tr = t->tr;
        this->time = t->time;
        this->Ha = t->Ha;
        this->iters = t->iters;
        this->criterium = t->criterium;
        this->well = t->well;
    }

    transform_t() {
        this->sim = 0;
        this->tx = 0;
        this->ty = 0;
        this->tr = 0;
    }

    double sim = 0;
    double Ha = 0;
    int frame = 0;
    int tx = 0;
    int ty = 0;
    int tr = 0;
    int time = 0;
    uint iters = 0;
    QString criterium;
    bool well = false;

};

struct frame_t {
    mat original;
    QImage *image;
    vec histogram;
    vec P; //pravdepodobnost
    double H; //entropie
    mat joinH; // vzajemna entropie
    double avg; //prumer celeho obrazu
};

struct regdata_t {
    uint frame = 0;
    uint criteriaOfSimilarity = 0;
    uint algorithm = 0;
    uint firstFrame = 0;
    transform_t boundTransform;
};

#include <QThread>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

#endif // STRUCTS

