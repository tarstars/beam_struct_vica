#include "planewave_c.h"
#include "storage.h"
#include "vector3c.h"
#include <complex>

using namespace std;

PlaneWave_C::PlaneWave_C()
{
}

ostream& operator <<(ostream& os,const PlaneWave_C& r){
    //os<<"plane wave:"<<endl; это вывод значений
    // ofstream plane;
    // plane.open("plane.txt");
    cout<<"plane wave:"<<endl;
    //plane<<"slow: "<<r.slow<<endl<<endl;
    cout<<"q = "<<r.q<<endl;
    cout<<"k = "<<r.k<<endl;
    cout<<"tensor s= "<<r.S<<endl;
    cout<<"tensor t= "<<r.T<<endl;
    return os;
}

void
PlaneWave_C::takeFromStorage(int i, int j, const Storage& stor){
    q(0)=stor( 0, i, j);
    q(1)=stor( 1, i, j);
    q(2)=stor( 2, i, j);

    S(0,0)=stor( 3, i, j);
    S(1,1)=stor( 4, i, j);
    S(2,2)=stor( 5, i, j);
    S(1,2)=stor( 6, i, j);
    S(0,2)=stor( 7, i, j);
    S(0,1)=stor( 8, i, j);

    T(0,0)= stor(9, i, j);
    T(1,1)= stor(10, i, j);
    T(2,2)= stor(11, i, j);
    T(1,2)= stor(12, i, j);
    T(0,2)= stor(13, i, j);
    T(0,1)= stor(14, i, j);

}

double
PlaneWave_C::getSqrtV()const{
    double res=real(sqrt(q(0)*conj(q(0))+q(1)*conj(q(1))+q(2)*conj(q(2))));

return res;
}


