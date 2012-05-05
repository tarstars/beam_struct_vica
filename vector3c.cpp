#include "vector3c.h"
#include <complex>
using namespace std;

Vector3c::Vector3c()
{
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

ostream&
operator<<(ostream& os, const Vector3c& r){
    return r >> os;
}

ostream&
Vector3c::operator>>(ostream& os)const{
    return os<< x << "   "<< y << "   "<< z;
}
