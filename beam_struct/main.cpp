#define _USE_MATH_DEFINES

#include "tensor.h"
#include "util.h"
#include "vector3.h"
#include <iostream>
#include <fstream>
//#include "matrix3.h"
//#include "matrix.h"
//#include <conio.h>
//#include "polinom.h"
#include "polymatrix.h"
//#include "tensor.h"
#include <QImage>
#include "matrix.h"
#include <algorithm>
#include "wavematrix.h"
#include "plan.h"
#include "storage.h"
#include "spacialmatrix.h"

using namespace std;


void work(){
  Tensor t = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  // Tensor t=tt.rotation_for_VB_picture(9.0/180*M_PI);
  PolyMatrix p;
  double rho=5.96e3;
  int n=100;
  int m=1000;
  ofstream dest("a_im2.txt");
  // ofstream dest("log.txt");
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      double s_1=-0.002+(0.004/n)*i;
      double s_2=-0.002+(0.004/n)*j;
      p= t.make_polyMatrix(rho,s_1,s_2);
      Polinom d;
      d=p.Determinant();
      vector<CD> f;
      vector <double> freal;
      vector <CD> fimage;
      f=d.all_roots();
      freal=real_part(f);
      fimage=image_part(f);
      sort(freal.begin(),freal.end());
      /* if (freal.size()>0){
	 double z=freal[(freal.size()-1)];
	 dest<<"sphere{<"<<s_1*m<<", "<<z*m<<", "<<s_2*m<<">, 0.02 pigment {color<1, 1, 1>}}"<<endl;
	 // dest<<"sphere{<"<<s_1*m<<", "<<-1*(z*m)<<", "<<s_2*m<<">, 0.02 pigment {color<1, 1, 1>}}"<<endl;
	 }*/
      if (fimage.size()>1){
	// for (int i=0; i<int(fimage.size()); i++){
	// sort(fimage.begin(),fimage.end());
	CD q=fimage[1];
	double rre=real(q);
	double imm=imag(q);
	dest<<"sphere{<"<<s_1*m<<", "<<rre*m<<", "<<s_2*m<<">, 0.02 pigment {color<2, 0, 1>}}"<<endl;
	dest<<"sphere{<"<<s_1*m<<", "<<imm*m<<", "<<s_2*m<<">, 0.02 pigment {color<2, 1, 0>}}"<<endl;
	// }
      }
      //   vector <double> freal;
      // vector <CD> fimage;
      // freal=real_part(f);
      //fimage=image_part(f);
      /*  double max_1=0;
	  double min_1=real(f[0]);
	  int sign_1=0;
	  int sign_2=0;
	  int sign_3=0;
	  for (int k=0; k<int(f.size()); k++){
	  if (max_1<real(f[k])&&abs(imag(f[k]))<1e-5)
	  { max_1=real(f[k]);
	  sign_1+=1;}
	  if (min_1>real(f[k])&&abs(imag(f[k]))<1e-5)
	  { min_1=real(f[k]);
	  sign_1+=1;}}
	  for (int i=0; i<3; i++){
	  if ((i!=sign_1)&&(i=!sign_2)){sign_3+=i;}
	  }
	  double i_0=real(f[sign_3]);
	  if (number=sign_1)
	  { dest<<"sphere{<"<<s_1*m<<", "<<max_1*m<<", "<<s_2*m<<">, 0.02 pigment {color<1, 1, 1>}}"<<endl;}
	  if (number=sign_2)
	  { dest<<"sphere{<"<<s_1*m<<", "<<min_1*m<<", "<<s_2*m<<">, 0.02 pigment {color<1, 1, 1>}}"<<endl;}
	  if (number=sign_3)
	  { dest<<"sphere{<"<<s_1*m<<", "<<i_0*m<<", "<<s_2*m<<">, 0.02 pigment {color<1, 1, 1>}}"<<endl;}*/


    }
  }
}

void
testStorage(){
  int h = 3, d = 4, w = 5;

  Storage dat(h, d, w);

  for(int t = 0; t < h; ++t)
    for(int p = 0; p < d; ++p)
      for(int q = 0; q < w; ++q)
	dat(t, p, q) = (t + 1) * 100 + (p + 1) * 10 + (q + 1);

  cout << "storage: " << endl << dat << endl << endl;

}

void work_1(){
  cout.precision(5);
  cout<<scientific;

  int n=10;

  double rho=5.96e3;
  double a=0.05;//апертура в метрах
  double f=100e6;//частота в герцах

  Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  Tensor t=tt.rotation_for_VB_picture(9.0/180*M_PI);

  Vector3 force(0.2,0.3,0.4);
  force.normalize();
   
  ofstream wavesLog("waves_vica.log");

  try{
    WaveMatrix waves=create_wave_matrix(n, a, f, t,force, rho);
    

    matrixfftw amat=pic_to_mat("fp.png");
    matrixfftw amatf(amat.height(),amat.width());
    plan ap(amat, amatf, FFTW_FORWARD,  FFTW_ESTIMATE);
    plan bp(amat, amatf, FFTW_BACKWARD, FFTW_ESTIMATE);
    ap.exec();
    cout<<endl<<"  furie"<<endl;
    /* for (int i=0; i<amatf.height(); i++){
       for (int j=0; j<amatf.width(); j++){
       cout<<" "<<i<<" "<<j<<endl;
       cout<<amatf(i,j)<<endl<<endl;
       }
       }*/
    waves.loadFFTW(amatf);
    //cout<<waves<<endl;

    waves.logState(wavesLog);

    Storage dat=waves.getStorage();
    //cout<<dat<<endl;
    Storage transform=layerTransform(dat,amat,amatf,bp);
    // cout<<transform<<endl;
    SpacialMatrix spaceMat=getSpaceMatrix(transform);
    cout  << spaceMat << endl;
  }catch(string msg){cout<<"error:"<<msg<< endl;}
}

void test_composit_wave(){
  Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  Tensor t=tt.rotation_for_VB_picture(9.0/180*M_PI);
  double rho=5.96e3;
  Vector3 force(0.2,0.3,0.4);
  force.normalize();
  try{
    CompositWave cv(0.0, 0.0, t,force, rho, 2*M_PI*1e8 );
    cout<<endl;
    cout<<cv<<endl;
  }catch(string msg){cout<<"error: "<<msg<<endl;}

}


void testPol(){
  Vector3 a(0, 0, 1);
  Vector3 b(1/sqrt(2), 1/sqrt(2), 0);
  Vector3 c(0.5, 0.5, 1/sqrt(2));

  Matrix3 Matr(a,b,c);
  Matrix3 Matrr(a,a,c);
  Matrix3 Matrr1(a,b,b);
  Matrix3 Matrr2(b,c,c);
  Matrix3 Matrr3(a,b,a);
  cout<<Matr.calc_pol()<<endl<<endl;
  cout<<Matrr.calc_pol()<<endl<<endl;
  cout<<Matrr1.calc_pol()<<endl<<endl;
  cout<<Matrr2.calc_pol()<<endl<<endl;
  cout<<Matrr3.calc_pol()<<endl<<endl;
}


int main(int argc, char *argv[])
{// Tensor t = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  work_1();
  // testStorage();
  // testPol();
  // test_composit_wave();
  //getch();
  return 0;

}
