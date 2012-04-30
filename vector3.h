#ifndef VECTOR3_H
#define VECTOR3_H
#include <iostream>

class Vector3
{
double x,y,z;
public:
    Vector3();
    Vector3(double, double, double);
    Vector3 operator+( const Vector3&)const;
    Vector3 operator*(double c) const;
    double& operator() (int i);
   const double& operator() (int i)const;
    void normalize();
    double abs();
    Vector3 real_part();
    Vector3 image_part();
    std::ostream& operator>>(std::ostream& os)const;
};

std::ostream& operator<<(std::ostream& os, const Vector3& r);


#endif // VECTOR3_H
