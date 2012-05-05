#ifndef MATRIX3_C_H
#define MATRIX3_C_H
#include <complex>

class Matrix3_c
{
    std::complex<double> dat[3][3];
public:
    Matrix3_c();
    std::complex<double>& operator() (int i, int j){return dat[i][j];}
    const std::complex<double>& operator() (int i, int j)const{return dat[i][j];}
    std::ostream& operator>>(std::ostream& os)const;
};
std::ostream& operator<<(std::ostream& os, const Matrix3_c& r);

#endif // MATRIX3_C_H
