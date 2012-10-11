#include "waveelement.h"

using namespace std;

WaveElement::WaveElement(){}

WaveElement::WaveElement(double s_1, double s_2, const Tensor& t,const Vector3& force, double rho,double omega):cv(s_1, s_2, t,force, rho, omega){

}

void
WaveElement::setAmplitude(const std::complex<double>& r){
    A=r;
}

void
WaveElement::logState(ostream& os)const{
  os << "A = " << A << " ";
  cv.logState(os);
}

void
WaveElement::makeZShift(double dz){
    cv.makeZShift(dz);
}

ostream& operator<<(ostream& os, const WaveElement& r){
  os<<"WaveEl: "<<endl;
  os<<"A= "<<r.A<<endl;
  os<<r.cv<<endl;
  return os;
}

void
WaveElement::incrementStorage(Storage& dat,int p, int q)const{
  cv.incrementStorage(dat, p, q, A);
}
