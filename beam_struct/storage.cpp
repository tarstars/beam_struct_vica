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
        os<<k<<endl;
        for (int i=0; i<d; ++i){
            for (int j=0; j<w; ++j){
                complex <double> val;
                val=dat[k*d*w+i*w+j];
                if(((k==11)||(k==12)||(k==13))&&abs(dat[k*d*w+i*w+j])<1e-10){
                    val=0;
                }
                os << val << "\t";
                // os<<dat[k*d*w+i*w+j]<<"\t";
            }
            os<<endl;
        }
        os<<endl<<endl<<endl;
    }
    return os;
}
