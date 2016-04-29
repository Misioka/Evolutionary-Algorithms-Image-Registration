#ifndef COMPUTEREGISTRATION_H
#define COMPUTEREGISTRATION_H

#include <armadillo>
#include <vector>
#include <QDebug>

using namespace arma;
using namespace std;

class ComputeRegistration
{
public:
	ComputeRegistration(mat &X, mat &Y);
    double findP(mat &X, mat &Y, double sigma2, float w, vec &P1, vec &Pt1, vec &PX, const float epsilon);
    vec direct(mat &target, vec &weights, mat &source, double bandWidth);
};

#endif // COMPUTEREGISTRATION_H
