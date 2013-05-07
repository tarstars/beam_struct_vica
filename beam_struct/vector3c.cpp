#include "vector3c.h"
#include <complex>
using namespace std;

Vector3c::Vector3c(): x(0,0), y(0,0), z(0,0)
{}

Vector3c::Vector3c(complex<double> a, complex<double> b,complex<double> c)
{
  x=a, y=b, z=c;
}

complex<double>&
Vector3c::operator ()(int i){
    if (i==0) return x;
    if (i==1) return y;
    return z;
}
const complex<double>&
Vector3c::operator ()(int i)const{
    if (i==0) return x;
    if (i==1) return y;
    return z;
}

Vector3c
Vector3c::operator +(const Vector3c& r)const
{
  return Vector3c(x+r.x, y+r.y, z+r.z); // возвращаем обьект класса вектор, чтобы его вернуть надо сконструировать
}

Vector3c
Vector3c:: operator*(complex<double> c) const{
    return Vector3c(x*c, y*c, z*c);
}

Vector3c
Vector3c:: operator*(double c) const{
    return Vector3c(x*c, y*c, z*c);
}

void
Vector3c::normalize()// Vector3::normalize - ф-ция нормалайз принадл. классу вектор3
{
  std::complex<double> a =sqrt (x*x+y*y+z*z);
  x=x/a;
  y=y/a;
  z=z/a;
}
std::complex<double>
 Vector3c::abs(){
 std::complex<double> a=sqrt (x*conj(x)+y*conj(y)+z*conj(z));
 return a;
 }

ostream&
operator<<(ostream& os, const Vector3c& r){
    return r >> os;
}

ostream&
Vector3c::operator>>(ostream& os)const{
    return os<< x << "   "<< y << "   "<< z;
}
