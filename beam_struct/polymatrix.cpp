#include "polymatrix.h"
#include "tensor.h"
#include "polinom.h"
#include <iostream>
using namespace std;
PolyMatrix::PolyMatrix(){}

ostream& PolyMatrix::operator >>(ostream& os) const{
    for (int j=0; j<3; ++j){
        for (int i=0; i<3; ++i){
                    os<<i<<""<<j<<"  "<<dat[i][j]<< "    ";
                   // os<<"\t";
            }
            os<<endl;
            }
    return os;
}

Matrix3 PolyMatrix::evaluatePolyMatrix(double s_3) const{
    Matrix3 Matr;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
          RetVal p=(*this)(i,j).count(s_3);
          Matr(i,j)=real(p.val);
        }
    }
  //  cout<<Matr<<endl;
    return Matr;
}

Matrix3_c PolyMatrix::evaluatePolyMatrixC(std::complex<double> s_3) const{
    Matrix3_c Matr;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
          RetVal p=(*this)(i,j).count(s_3);
          Matr(i,j)=p.val;
        }
    }
  //  cout<<Matr<<endl;
    return Matr;
}


Polinom PolyMatrix::Determinant()const{
    Polinom c;
    c=dat[0][0]*(dat[1][1]*dat[2][2]-dat[2][1]*dat[1][2])-
            dat[0][1]*(dat[1][0]*dat[2][2]-dat[2][0]*dat[1][2])+
            dat[0][2]*(dat[1][0]*dat[2][1]-dat[2][0]*dat[1][1]);
    return c;
}
ostream& operator <<(ostream& os, const PolyMatrix& r){
 return r>>os;
}



