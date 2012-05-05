#include "vector3.h"
#include <cmath>
using namespace std;


Vector3::Vector3(): x(0), y(0), z(0)
{}
Vector3::Vector3(double a, double b, double c){
    x=a, y=b, z=c;
}

Vector3 //вовращаемое значение для оператор+
Vector3::operator +(const Vector3& r)const {


    return Vector3(x+r.x, y+r.y, z+r.z); // возвращаем обьект класса вектор, чтобы его вернуть надо сконструировать
}

Vector3
Vector3:: operator*(double c) const{
    return Vector3(x*c, y*c, z*c);
}

double&
Vector3::operator ()(int i){
    if (i==0) return x;
    if (i==1) return y;
    return z;
}
const double&
Vector3::operator ()(int i)const{
    if (i==0) return x;
    if (i==1) return y;
    return z;
}
ostream&
operator<<(ostream& os, const Vector3& r){
 return r >> os;
 }

ostream&
Vector3::operator>>(ostream& os)const{
 return os<< x << "   "<< y << "   "<< z;
}

void
Vector3::normalize()// Vector3::normalize - ф-ция нормалайз принадл. классу вектор3
{ double a =sqrt (x*x+y*y+z*z);
  x=x/a;
  y=y/a;
  z=z/a;
}
 double
 Vector3::abs(){
 double a=sqrt (x*x+y*y+z*z);
 return a;
 }



