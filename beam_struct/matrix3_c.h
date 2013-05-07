#ifndef MATRIX3_C_H
#define MATRIX3_C_H
#include <complex>
#include "vector3c.h"
#include "polinom.h"

class Matrix3_c
{
    std::complex<double> dat[3][3];
public:
    Matrix3_c();
    Matrix3_c(const Vector3c &a,const Vector3c &b, const Vector3c &c);

    double vector3c(int i, int j);

    std::complex<double>& operator() (int i, int j){return dat[i][j];}

    Vector3c operator*( const Vector3c& ) const;
    std::complex<double> det(Matrix3_c);
    void logState(std::ostream&)const;

    Matrix3_c rotation(double phi, char p);
    Matrix3_c operator* (std::complex<double> v)const;
    Matrix3_c operator+ (const Matrix3_c& b)const;
    Polinom char_poly() const;

    Vector3c calc_pol() const;


    const std::complex<double>& operator() (int i, int j)const{return dat[i][j];}
    std::ostream& operator>>(std::ostream& os)const;
};
std::ostream& operator<<(std::ostream& os, const Matrix3_c& r);

#endif // MATRIX3_C_H
