#include "storage.h"
using namespace std;


Storage::Storage():h(0),d(0),w(0){}

Storage::Storage(int a, int b, int c):h(a),d(b),w(c), dat(a*b*c){
}

ostream& operator<<(ostream& os, const Storage& r){
    return r >> os;
}

ostream&
Storage::operator>>(ostream& os)const{
    os<<"y"<<endl;
    for (int k=0; k<h; ++k){
        for (int i=0; i<d; ++i){
            for (int j=0; j<w; ++j){
                    os<< dat[k*d*w+i*w+j]<< "\t";
            }
            os<<endl;
            }
        os<<endl<<endl<<endl;
    }
    return os;
}
