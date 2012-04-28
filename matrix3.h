#ifndef MATRIX3_H
#define MATRIX3_H
#include "polinom.h"
#include <iostream>
#include "vector3.h"

class Matrix3
            {
    double dat[3][3];
public:
    Matrix3();

    Matrix3(const Vector3 &a,const Vector3 &b, const Vector3 &c);

    double vector3(int i, int j);

    double& operator() (int i, int j){return dat[i][j];};
    const double& operator() (int i, int j)const{return dat[i][j];};

    Vector3 operator*( const Vector3& ) const;

    double det(Matrix3);

    Matrix3 rotation(double phi, char p);
    Matrix3 operator* (double v)const;
    Matrix3 operator+ (const Matrix3& b)const;
    Polinom char_poly() const;

    Vector3 calc_pol() const;

    std::ostream& operator>>(std::ostream& os)const;
};
std::ostream& operator<<(std::ostream& os, const Matrix3& r);
#endif // MATRIX3_H
