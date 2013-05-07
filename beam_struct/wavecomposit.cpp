#include "wavecomposit.h"
#include "polymatrix.h"
#include "matrix3.h"
#include "util.h"
#include "storage.h"
#include <algorithm>
#include <iostream>
#include <fstream>


using namespace std;
ofstream ves("weight.txt");
CompositWave::CompositWave()
{
}

CompositWave::CompositWave(double s_1, double s_2, const Tensor& t,const Vector3& force, double rho,double omega){

  PolyMatrix p=t.make_polyMatrix(rho, s_1, s_2);
 
  Polinom d;
  d=p.Determinant();
  vector<CD> f;
  f=d.all_roots();
  double eps=1e-6;
  vector<CD> fplus;
  //vector <double>real_fplus=real_part(fplus);
  for (int i=0; i<int(f.size()); i++)
  {
    if (abs(imag(f[i]))>eps)
    {
      stringstream dest;
    //  cout<<"1imaginary root in compvawe ("<<s_1<<","<<s_2<<")"<<endl;
      if ((imag(f[i]))>0)
      {
        fplus.push_back(f[i]);
      }
      cout<<" im "<<endl;
    }

    if ((abs(imag(f[i]))<eps)&&(real(f[i])<0))
    {
       fplus.push_back(f[i]);
    }
  }

  if (fplus.size()!=3)
  {
    stringstream dest;
    dest<<"ne 3 kornya "<<fplus.size()<<endl;
    throw (string(dest.str()));
  }

  // cout<<" "<<fplus<<"  eto korny"<<endl<<endl;
  //getLog() << *max_element(fplus.begin(), fplus.end())<<"  ";

  for (int r=0; r<3; ++r){
    pav[r]=PlaneWave_C(s_1,s_2, fplus[r], p, t, rho, omega);
   // cout<<pav[r];
  }

  Matrix3_c work;
  for (int i=0; i<3; i++){
    Matrix3_c help=pav[i].T;
    for (int j=0; j<3; j++){
      work(j,i)=help(2,j);

    }
  }

  //cout<<" dla vesov "<<endl<<work<<endl;
  //cout<<endl<<endl;
  //cout<<"vesa"<<endl;
  //ves<<" dla vesov "<<endl<<work<<endl;
  ves<<endl<<endl;
  ves<<"vesa"<<endl;

 /* Vector3 force;
  force(0)=0.2;
  force(1)=0.3;
  force(2)=0.4;
  force.normalize();*/

  std::complex<double> determ=work.det(work);

  for (int i=0; i<3; i++){
    Matrix3_c work_dop=work;
    for (int k=0; k<3; k++){
    work_dop(k,i)=force(k);}
    std::complex<double> det_dop=work_dop.det(work_dop);
      ves<<i<<"  dopolnit. opredelitel "<<det_dop<<endl;
   ves<<" opredilitel "<<determ<<endl;
    weight(i)=det_dop/determ;
    //cout<<weight(i)<<endl;
    ves<<"x"<<i<<"=det_dop/determ= "<<weight(i)<<endl<<endl;
    }
    cout<<endl<<endl;
}
void
CompositWave::incrementStorage(Storage& dat, int p, int q,const complex<double>& ampl)const{
    for (int f=0;f<3; f++){
        pav[f].incrementStorage(dat,p,q,ampl*weight(f));
    }
}

/*
void
CompositWave::makeShift(double dz) {
    for (int i=0; i<3; i++) {
        weight(i)=weight(i)*exp(complex<double>(0,1)*dz*pav[i].getKz());
    }
}*/


void
CompositWave::logState(ostream& os)const{
  os << "B_1 B_2 B_3 = " << weight(0) << " " << weight(1) << " " << weight(2) << " ";

  for(int t = 0; t < 3; ++t){
    os << "pv_" << t << ": ";
    pav[t].logState(os);
  }
}

Vector3c
CompositWave:: TSum()const
{
  Vector3c sum;
  complex<double> sum1=0.0;
  complex<double> sum2=0.0;
  complex<double> sum3=0.0;
  for (int i=0; i<3; i++)
  {
    sum1+=weight(i)*pav[i].T(0,2);
    sum2+=weight(i)*pav[i].T(1,2);
    sum3+=weight(i)*pav[i].T(2,2);
  }
  sum(0)=sum1;
  sum(1)=sum2;
  sum(2)=sum3;
  return sum;
}

void
CompositWave::makeShift(double delta_z){
    for (int i=0; i<3; ++i){
        weight(i)*=pav[i].calculate_phase(delta_z);
    }
}

std::ostream& operator<<(std::ostream& os, const CompositWave& r){
    os<<"composit wave:"<<endl;
    for(int t=0; t<3; ++t){
        os<<"amplitude for plane wave  "<<r.weight(t)<<endl;
        os<<r.pav[t]<<endl;
    }

    return os;

}
