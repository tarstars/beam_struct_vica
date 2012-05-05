#ifndef POLYMATRIX_H
#define POLYMATRIX_H
#include "tensor.h"
//#include "polinom.h"

class Polinom;
class PolyMatrix
{
    Polinom dat[3][3];
public:
    PolyMatrix();
    Polinom Determinant()const;
    Polinom& operator() (int i, int j){return dat[i][j];};
    const Polinom& operator() (int i, int j)const{return dat[i][j];}
  //  Polinom detPoly();
    std::ostream& operator>>(std::ostream& os)const;
    Matrix3 evaluatePolyMatrix(double s_3)const;
};
std::ostream& operator<<(std::ostream& os, const PolyMatrix& r);
#endif // POLYMATRIX_H
