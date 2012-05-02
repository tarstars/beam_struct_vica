#ifndef WAVEELEMENT_H
#define WAVEELEMENT_H
#include "wavecomposit.h"

class Tensor;
class WaveElement
{
    double A;
    CompositWave cv;
public:
    WaveElement();
    WaveElement(double s_1, double s_2, const Tensor& t, double rho, double omega);
};

#endif // WAVEELEMENT_H
