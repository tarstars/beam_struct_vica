#ifndef COMPOSITWAVE_H
#define COMPOSITWAVE_H
#include "planewave.h"
class Tensor;
class Storage;
class CompositWave
{
    std::complex<double> k[3];
    Vector3 weight;
    PlaneWave pav[3];
public:
    CompositWave();
    CompositWave(double s_1, double s_2,const Tensor& t,const Vector3& force, double rho, double omega);
    void incrementStorage(Storage& dat, int p, int q, const std::complex<double>& ampl)const;
    friend std::ostream& operator<<(std::ostream& os, const CompositWave& r);
   // storage serialize(double p,double q);
};
    std::ostream& operator<<(std::ostream& os, const CompositWave& r);

#endif // COMPOSITWAVE_H
