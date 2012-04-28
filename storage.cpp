#include "storage.h"
using namespace std;


storage::storage():h(0),w(0),d(0){}
storage::storage(int a, int b, int c):h(a), w(b), d(c), dat(a*b*c)
{
}
ostream& operator<<(ostream& os, const storage& r){
    return r >> os;

}

ostream&
storage::operator>>(ostream& os)const{
    os<<"y"<<endl;
    for (int k=0; k<d; ++k){
        for (int i=0; i<h; ++i){
            for (int j=0; j<w; ++j){
                    os<< dat[k*w*h+i*w+j]<< "\t";
            }
            os<<endl;
            }
        os<<endl<<endl<<endl;
    }
    return os;
}
