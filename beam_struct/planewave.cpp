#include "planewave.h"
#include "polymatrix.h"
#include "util.h"
#include "storage.h"
#include <iostream>
#include <fstream>

using namespace std;

PlaneWave::PlaneWave(){}
PlaneWave::PlaneWave(double s1, double s2, double s3, const PolyMatrix& PolyMat, const Tensor& tens, double rho, double omega ):slow(s1,s2,s3),k(slow*omega)
{
    Matrix3 Matrr=PolyMat.evaluatePolyMatrix(s3);
    q=Matrr.calc_pol();
    //cout<<"  polarization "<<q<<endl;
    S=create_tensor_S(q,k);
    T=create_tensor_T(S,tens);
}
    ostream& operator <<(ostream& os,const PlaneWave& r){
    //os<<"plane wave:"<<endl; это вывод значений
   // ofstream plane;
   // plane.open("plane.txt");
    //os<<"plane wave:"<<endl;
    //os<<"slow: "<<r.slow<<endl<<endl;
    //os<<"q = "<<r.q<<endl;
    //os<<"k = "<<r.k<<endl;
    //os<<"tensor s= "<<r.S<<endl;
    //os<<"tensor t= "<<r.T<<endl;
    return os;
}
int
PlaneWave::getDimensions(){
return 15;
}


std::complex <double>
PlaneWave::calculate_phase(double delta_z){
    return exp(complex<double>(0,1)*delta_z*k(2));
}



/*double
PlaneWave::getKz(){
return k(2);
}*/


void
PlaneWave::incrementStorage(Storage& dat, int p, int q, std::complex<double> ampl)const{
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
PlaneWave::logState(ostream& os)const{
  os << "s = " << slow  << " q = " << q << " k = " << k << " S = ";
  S.logState(os);
  os << " T = ";
  T.logState(os);
}
