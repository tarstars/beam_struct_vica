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
#include <sstream>


using namespace std;

void work_1(){
  ofstream dest("ыыыыы.txt");
  cout.precision(5);
  cout<<scientific;

  int n=100;
  int nz=100;//количество шагов


  double rho=5.96e3;

  double a=0.015;//апертура в метрах
  double f=50e6;//частота в герцах
  double dz=a/n;// 5 milimeters

  Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  for (double g=0; g<180; g+=1){
  Tensor t=tt.rotation_for_VB_picture_1(g/180*M_PI);
  PolyMatrix p;
  matrix mat(n,n);
         for (int i=0; i<n; i++){
             for (int j=0; j<n; j++){
                 double s_1=-0.002+(0.004/n)*i;
                 double s_2=-0.002+(0.004/n)*j;
                 p= t.make_polyMatrix(rho,s_1,s_2);
                 Polinom d;
                 d=p.Determinant();
                 vector<CD> f;
                 f=d.all_roots();
                 vector <double> freal;
                 vector <CD> fimage;
                 freal=real_part(f);
                 fimage=image_part(f);
                 mat(i,j)=freal.size();
             }
         }
         cout<<mat;
        saveAsPicture(mat, "mapa.png",1);
        matrixfftw amat=pic_to_mat("D:\\backup\\progs\\horrible_tenzor-rar\\beam_struct_vica\\beam_struct\\fp_1.png");
        matrixfftw amatf(amat.height(),amat.width());
        plan ap(amat, amatf, FFTW_FORWARD,  FFTW_ESTIMATE);
        ap.exec();
        for (int p=0;p<n;p++){
            for (int q=0; q<n; q++){

                if (p<(n/2)&&q<(n/2)) {amatf(p,q)=amatf(p+n/2,q+n/2);}
                 if (p<(n/2)&&q>(n/2)) {amatf(p,q)=amatf(p+n/2,q-n/2);}
                 if (p>(n/2)&&q>(n/2)) {amatf(p,q)=amatf(n/2+n-p,n/2+n-q);}
                 if (p>(n/2)&&q<(n/2)) {amatf(p,q)=amatf(n/2+n-p,n/2-q);}
            }
        }
        saveAsPictureFFTW(amatf, "furie_trancduser.png");

  Vector3 force(1,0,0);
  force.normalize();
   
  ofstream wavesLog("waves_vica.log");

  try{
    WaveMatrix waves=create_wave_matrix(n, a, f, t,force, rho);

    matrixfftw amat=pic_to_mat("D:\\backup\\progs\\horrible_tenzor-rar\\beam_struct_vica\\beam_struct\\fp_1.png");
    matrixfftw amatf(amat.height(),amat.width());
    plan ap(amat, amatf, FFTW_FORWARD,  FFTW_ESTIMATE);
    plan bp(amat, amatf, FFTW_BACKWARD, FFTW_ESTIMATE);
    ap.exec();
    waves.loadFFTW(amatf);
    //cout<<waves<<endl;

    //waves.logState(wavesLog);

    Storage AmplitudeSquare(nz,n,n);
    for (int i=0; i<nz; i++) {
        cout<<"  "<<i<<endl;
        waves.makeShift(dz);
        Storage dat=waves.getStorage();
        Storage transform=layerTransform(dat,amat,amatf,bp);
        SpacialMatrix spaceMat=getSpaceMatrix(transform);
       // cout << endl<< "Sm" << endl << spaceMat << endl;
        spaceMat.fillSliceWithV(i,AmplitudeSquare);
    }

  /*  for (int h=0;h<n;h++){  //это делает дольки
    matrix res(nz,n);
    for (int i=0; i<nz; i++){
        for (int j=0; j<n; j++){
            res(i,j)=real(AmplitudeSquare(i,j,h));
        }
    }
    stringstream dest;
    double gamma=3.5;
    dest<<"picture"<<h<<".png ";
    saveAsPicture(res, dest.str(),gamma);
    }
*/
    matrix res(nz,n);   //поворот
    for (int i=0; i<nz; i++){
        for (int j=0; j<n; j++){
            res(i,j)=real(AmplitudeSquare(i,51,j));
        }
    }
    stringstream dest;
    dest<<"xy//picture"<<g<<".png";
    saveAsPicture(res, dest.str(),1);

   /* int nz=10;
    Storage volume(nz+1,n,n);

    for (int t=0; t<=nz; t++){
    waves.makeZShift(t*dz);
    Storage dat=waves.getStorage();
    Storage transform = layerTransform(dat,amat,amatf,bp);
    SpacialMatrix spaceMat = getSpaceMatrix(transform);
   // spaceMat.printv(cout);
    spaceMat.fillSlice(t, volume);

    cout<<endl<<endl;


    }
   dest<< "volume Stor is" << endl<< volume<<endl;*/


  }catch(string msg){cout<<"error:"<<msg<< endl;}
  }
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
{ // Tensor t = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
    work_1();
  // testStorage();
  // testPol();
  // test_composit_wave();
 // getch();
  return 0;

}
