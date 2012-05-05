#include "spacialmatrix.h"
using namespace std;

SpacialMatrix::SpacialMatrix():n(0)
{
}

ostream& operator<<(ostream& os, const SpacialMatrix& r){
    return r >> os;

}

ostream&
SpacialMatrix::operator>>(ostream& os)const{
    os<<"y"<<endl;
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
                    os<< "(" << i << "," << j << ")" << endl;
                    os<< dat[i*n+j]<< "\t";
            }
            os<<endl;
            }
    return os;
}