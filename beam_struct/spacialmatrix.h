#ifndef SPACIALMATRIX_H
#define SPACIALMATRIX_H
#include <vector>
#include "planewave_c.h"

class SpacialMatrix
{
    int n;
    std::vector<PlaneWave_C> dat;
public:
    SpacialMatrix();
    SpacialMatrix(int nn):n(nn),dat(nn*nn){}
    PlaneWave_C& operator()(int i,int j){return dat[n*i+j];}
    const PlaneWave_C& operator()(int i,int j)const{return dat[n*i+j];}
    std::ostream& operator>>(std::ostream& os)const;
    void printv(std::ostream&)const;
    void fillSlice( int t,Storage& dat);
};
std::ostream& operator<<(std::ostream& os, const SpacialMatrix& r);
#endif // SPACIALMATRIX_H
