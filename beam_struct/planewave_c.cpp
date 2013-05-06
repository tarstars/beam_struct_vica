#include "planewave_c.h"
#include "storage.h"
#include "vector3c.h"
#include "polymatrix.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

PlaneWave_C::PlaneWave_C()
{
}

PlaneWave_C::PlaneWave_C(double s1, double s2, std::complex<double> s3, const PolyMatrix& PolyMat, const Tensor& tens, double rho, double omega ):slow(s1,s2,s3),k(slow*omega)
{
    Matrix3_c Matrr=PolyMat.evaluatePolyMatrixC(s3);
    q=Matrr.calc_pol();
    Vector3c vectorTestoviy=Matrr*q;
    cout<<"root"<<s3<<"  polarization "<<q<<endl<<"testoviy vector "<<vectorTestoviy<<endl<<" matrix "<<Matrr<<endl<<endl;
    S=create_tensor_S_c(k,q);
    T=create_tensor_T_c(S,tens);
}

ostream& operator <<(ostream& os,const PlaneWave_C& r){
    //os<<"plane wave:"<<endl; это вывод значений
    // ofstream plane;
    // plane.open("plane.txt");
    cout<<"plane wave:"<<endl;
    cout<<"slow: "<<r.slow<<endl<<endl;
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


/*int
PlaneWave_C::getDimensions(){
return 15;
}*/


std::complex <double>
PlaneWave_C::calculate_phase(double delta_z){
    return exp(complex<double>(0,1)*delta_z*k(2));
}

void
PlaneWave_C::incrementStorage(Storage& dat, int p, int q, std::complex<double> ampl)const{
    dat(0,p,q)+=ampl*this -> q(0);
    dat(1,p,q)+=ampl*this -> q(1);
    dat(2,p,q)+=ampl*this -> q(2);

    dat(3,p,q)+=(S(0,0))*ampl;
    dat(4,p,q)+=(S(1,1))*ampl;
    dat(5,p,q)+=(S(2,2))*ampl;
    dat(6,p,q)+=(S(1,2))*ampl;
    dat(7,p,q)+=(S(0,2))*ampl;
    dat(8,p,q)+=(S(0,1))*ampl;

    dat(9,p,q)+=(T(0,0))*ampl;
    dat(10,p,q)+=(T(1,1))*ampl;
    dat(11,p,q)+=(T(2,2))*ampl;
    dat(12,p,q)+=(T(1,2))*ampl;
    dat(13,p,q)+=(T(0,2))*ampl;
    dat(14,p,q)+=(T(0,1))*ampl;


   /* for(int t = 0; t < 15; ++t)
        dat(t,p,q)=(t + 1) * 100 + 10 *(p+1) + q+1;*/
}

void
PlaneWave_C::logState(ostream& os)const{
  os << "s = " << slow  << " q = " << q << " k = " << k << " S = ";
  S.logState(os);
  os << " T = ";
  T.logState(os);
}

double
PlaneWave_C::getSqrtV()const{
    double res=real(sqrt(q(0)*conj(q(0))+q(1)*conj(q(1))+q(2)*conj(q(2))));
    ofstream plane;
    plane.open("plane.txt");
    plane<<res<<endl;
return res;
}


