#ifndef PLANEWAVE_C_H
#define PLANEWAVE_C_H


#include "vector3c.h"
#include "matrix3_c.h"
#include "storage.h"

class PlaneWave_C
{
public:
    Vector3c q, k;
    Matrix3_c S,T;
    PlaneWave_C();
    void takeFromStorage(int i, int j,const Storage& stor);
    double getSqrtV()const;
    friend std::ostream& operator <<(std::ostream& os,const PlaneWave_C& r);
};

std::ostream& operator << (std::ostream& os,const PlaneWave_C& r);


#endif // PLANEWAVE_C_H
