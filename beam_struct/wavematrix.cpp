#include <iomanip>

#include "matrixFFTW.h"
#include "wavematrix.h"
#include "storage.h"

using namespace std;

WaveMatrix::WaveMatrix(int nn): n(nn), dat(nn*nn)
{

}

void WaveMatrix::loadFFTW(const matrixfftw& r){
  if (r.width()!=n || r.height()!=n)
    throw (string("dimension of Wavematrix != dimension of furie"));
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      (*this)(i,j).setAmplitude(r(i,j));
    }
  }
}

void
WaveMatrix::logState(ostream& os){
  os.precision(5);
  os << scientific;
  for(int p = 0; p < n; ++p){
    for(int q = 0; q < n; ++q){
      os << "(p,q) = (" << p << "," << q << ") ";
      (*this)(p,q).logState(os);
      os << endl;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const WaveMatrix &r){
  os<<"Wave Matrix: "<<endl;
  for (int p=0; p<r.n; ++p){
    for (int q=0; q<r.n; ++q){
      os<<"element("<<p<<", "<<q<<"):"<<endl;
      os<<r(p,q)<<endl;
    }
    os<<endl;
  }
  return os;
}

void
WaveMatrix::makeShift (double dz){
for (int p=0; p<n; ++p)
    for (int q=0; q<n; ++q)
        (*this)(p,q).makeShift(dz);
};


Storage
WaveMatrix::getStorage()const{
  Storage dat(PlaneWave::getDimensions(),n,n);
  for (int o=0; o<n; o++){
    for (int k=0; k<n; k++){
      (*this)(o,k).incrementStorage(dat,o,k);

    }
  }
  return dat;
}
