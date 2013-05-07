#ifndef VECTOR3C_H
#define VECTOR3C_H

#include <complex>

class Vector3c
{
   std::complex<double> x,y,z;
public:
    Vector3c();
    Vector3c(std::complex<double> a,std::complex<double> b,std::complex<double> c);
    Vector3c operator+( const Vector3c&)const;
    Vector3c operator*(std::complex<double> c) const;
    Vector3c operator*(double c) const;
    std::complex<double>& operator() (int i);
    const std::complex<double>& operator() (int i)const;
    void normalize();
    std::complex<double> abs();
    std::ostream& operator>>(std::ostream& os)const;
    double norm()const
    {
       return (std::norm(x)+std::norm(y)+std::norm(z));
    }
};

std::ostream& operator<<(std::ostream& os, const Vector3c& r);


#endif // VECTOR3C_H
