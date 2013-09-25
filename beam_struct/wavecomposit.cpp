#include "wavecomposit.h"
#include "criteria_for_nonhomogenious.h"
#include "polymatrix.h"
#include "matrix3.h"
#include "util.h"
#include "storage.h"
#include <algorithm>
#include <iostream>
#include <fstream>


using namespace std;
//ofstream ves("weight.txt");
CompositWave::CompositWave()
{
}

CompositWave::CompositWave(double s_1, double s_2, const Tensor& t,const Vector3& force, double rho,double omega){

  PolyMatrix p=t.make_polyMatrix(rho, s_1, s_2);
  Polinom d;
  d=p.Determinant();
  vector<CD> f;
  f=d.all_roots();

   stringstream dest;
  double eps=1e-6;
  vector<CD> fplus;
  int r=0;
  for (int i=0; i<int(f.size()); i++)
  {
    if ((abs(imag(f[i]))>eps)&&(imag(f[i])<0))
    {
       PlaneWave_C Pv(s_1,s_2, f[i], p, t, rho, omega);
       pav[r] = Pv;
       r++;
    }
    if (abs(imag(f[i]))<eps)
    {
         PlaneWave_C Pv(s_1,s_2, f[i], p, t, rho, omega);
         Vector3c PoitingDir = Pv.T * Pv.q;
         if (real(PoitingDir(3)) < 0)
         {
            pav[r] = Pv;
            r++;
         }
    }
  }

  if (r!=3)
  {
    throw (string(dest.str()));
  }


  Matrix3_c work;
  for (int i=0; i<3; i++){
    Matrix3_c help=pav[i].T;
    for (int j=0; j<3; j++){
      work(j,i)=help(2,j);

    }
  }


  std::complex<double> determ=work.det(work);
  if (abs(determ)<1e-7) throw (string ("zero determinant in composit wave"));

  for (int i=0; i<3; i++)
  {
    Matrix3_c work_dop=work;
    for (int k=0; k<3; k++)
    {
      work_dop(k,i)=force(k);
    }
    std::complex<double> det_dop=work_dop.det(work_dop);
  //  ves<<i<<"  dopolnit. opredelitel "<<det_dop<<endl;
 //   ves<<" opredilitel "<<determ<<endl;
    weight(i)=det_dop/determ;
 //   ves<<"x"<<i<<"=det_dop/determ= "<<weight(i)<<endl<<endl;
  }
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

int CompositWave::getRootQuantity()const
{
   int res=0;
   Criteria_For_Nonhomogenious type;
   for (int i=0; i<3; i++)
   {
       if (type.needEliminate(this->pav[i])) { res++; }
   }
   return res;
}

void
CompositWave::eliminate (criteria& type)
{
    for (int i=0; i<3; i++)
    {
        if ( type.needEliminate(this->pav[i]) ) {this->weight(i) = 0;} // если тип.удалить, т.е .волна другого типа то true
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
