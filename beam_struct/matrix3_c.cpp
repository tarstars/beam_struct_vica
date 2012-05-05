#include "matrix3_c.h"

using namespace std;

Matrix3_c::Matrix3_c(){
    for (int i = 0; i<3 ;++i)
        for (int j = 0; j<3; ++j)
            dat[i][j]=0;
}

ostream& operator<<(ostream& os, const Matrix3_c& r){
    return r >> os;

}

ostream&
Matrix3_c::operator>>(ostream& os)const{
    for (int j=0; j<3; ++j){
        for (int i=0; i<3; ++i){
            os<< dat[j][i]<<"\t";
        }
        os<<endl;
    }
    return os;
}
