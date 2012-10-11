#ifndef PLANEWAVE_H
#define PLANEWAVE_H
#include <complex>

#include "vector3.h"
#include "matrix3.h"

class PolyMatrix;
class Tensor;
class Storage;

class PlaneWave
{
   // Vector3 slow, q, k;
   // Matrix3 S,T;
public:
    Vector3 slow, q, k;
    Matrix3 S,T;

    PlaneWave();
    PlaneWave(double s1, double s2, double s3, const PolyMatrix& PolyMat, const Tensor& tens, double rho, double omega );

    void incrementStorage(Storage& dat, int p, int q, std::complex<double> ampl)const;
    void logState(std::ostream& os)const;


    std::complex <double> calculate_phase(double delta_z);


  //  double getKz();

    friend std::ostream& operator <<(std::ostream& os,const PlaneWave& r);
    static int getDimensions();
};
    std::ostream& operator <<(std::ostream& os,const PlaneWave& r);

#endif // PLANEWAVE_H
