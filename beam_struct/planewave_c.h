#ifndef PLANEWAVE_C_H
#define PLANEWAVE_C_H
#include <complex>

#include "vector3c.h"
#include "matrix3_c.h"
#include "storage.h"

class PolyMatrix;
class Tensor;
class Storage;

class PlaneWave_C
{
public:
    Vector3c slow, q, k;
    Matrix3_c S,T;
    PlaneWave_C();

    PlaneWave_C(double s1, double s2,std::complex<double> s3, const PolyMatrix& PolyMat, const Tensor& tens, double rho, double omega );

    void incrementStorage(Storage& dat, int p, int q, std::complex<double> ampl)const;
    void logState(std::ostream& os)const;

    void takeFromStorage(int i, int j,const Storage& stor);
    double getSqrtV()const;
    friend std::ostream& operator <<(std::ostream& os,const PlaneWave_C& r);
    double getSquareAmplitude()const
    {
      return q.norm();
    }
    std::complex <double> calculate_phase(double delta_z);
};

std::ostream& operator << (std::ostream& os,const PlaneWave_C& r);


#endif // PLANEWAVE_C_H
