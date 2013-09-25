#ifndef WAVEELEMENT_H
#define WAVEELEMENT_H

#include "wavecomposit.h"
#include "criteria.h"

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
    void setAOne(){ A = 1.0;}
    void incrementStorage(Storage& dat,int p, int q)const;
    void logState(std::ostream& os)const;


    int getRootQuantity()const;
    void makeShift(double dz);
    void eliminate (criteria& type);

    friend std::ostream& operator<<(std::ostream&, const WaveElement&);
};
std::ostream& operator<<(std::ostream& os, const WaveElement& r);

#endif // WAVEELEMENT_H
