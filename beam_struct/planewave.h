#ifndef PLANEWAVE_H
#define PLANEWAVE_H
#include "vector3.h"
#include "matrix3.h"

class PolyMatrix;

class Tensor;

class PlaneWave
{
   // Vector3 slow, q, k;
   // Matrix3 S,T;
public:
    Vector3 slow, q, k;
    Matrix3 S,T;
    PlaneWave();
    PlaneWave(double s1, double s2, double s3, const PolyMatrix& PolyMat, const Tensor& tens, double rho, double omega );
    friend std::ostream& operator <<(std::ostream& os,const PlaneWave& r);
};
    std::ostream& operator <<(std::ostream& os,const PlaneWave& r);

#endif // PLANEWAVE_H
