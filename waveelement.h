#ifndef WAVEELEMENT_H
#define WAVEELEMENT_H
#include "wavecomposit.h"
#include <complex>
class Storage;
class Tensor;
class WaveElement
{
    std::complex <double> A;
    CompositWave cv;
public:
    WaveElement();
    WaveElement(double s_1, double s_2, const Tensor& t,const Vector3& force, double rho, double omega);
    void setAmplitude(const std::complex<double>& r);
    void incrementStorage(Storage& dat,int p, int q)const;
    friend std::ostream& operator<<(std::ostream&, const WaveElement&);
};
std::ostream& operator<<(std::ostream& os, const WaveElement& r);

#endif // WAVEELEMENT_H
