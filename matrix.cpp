#include "matrix.h"

using namespace std;


matrix::matrix(int a,int b):h(a),w(b),dat(a*b){

}
ostream& operator<<(ostream& os, const matrix& r){
    return r >> os;

}

ostream&
matrix::operator>>(ostream& os)const{
    os<<"y"<<endl;
    for (int i=0; i<h; ++i){
        for (int j=0; j<w; ++j){
                    os<< dat[i*w+j]<< "\t";
            }
            os<<endl;
            }
    return os;
}
