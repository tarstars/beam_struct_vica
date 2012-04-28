#include "planewave.h"
#include "polymatrix.h"
#include "util.h"
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
    //plane<<"plane wave:"<<endl;
   // os<<"slow: "<<r.slow<<endl<<endl;
    //plane<<"slow: "<<r.slow<<endl<<endl;
    //os<<"q = "<<r.q<<endl;
    //os<<"k = "<<r.k<<endl;
    //os<<"tensor s= "<<r.S<<endl;
    //os<<"tensor t= "<<r.T<<endl;
    //plane<<"tensor t= "<<r.T<<endl;


    return os;
}
