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
#include "polinom.h"
#include "criteria_for_homogenious.h"
#include "criteria_for_nonhomogenious.h"
#include <sstream>


using namespace std;

void Print_For_Python(const Storage& dat)
{
    ofstream StorageForPython;
    StorageForPython.precision(3);
    StorageForPython.open("result_matrix.txt");
    StorageForPython<<"[";
    for (int p=0; p<15; p++)
    {
        StorageForPython<<endl<<p<<" [ "<<endl;
        for (int q=0; q<dat.depth(); q++)
        {
            StorageForPython<<"  [ ";
            for (int r=0; r<dat.width(); r++)
            {
               // StorageForPython<<" ("<<real(dat(p,q,r))<<" + "<<imag(dat(p,q,r))<<"j), ";
                StorageForPython<<" "<<real(dat(p,q,r))<<"\t";
            }
            StorageForPython<< " ], "<<endl;
        }
        StorageForPython<<" ], "<<endl<<endl;
    }
    StorageForPython<<"]";
    StorageForPython<<endl;
}

/*void Print_For_Python_Wave_Matrix(const WaveMatrix& Wm)
{
    ofstream StorageForPython;
    StorageForPython.open("result_matrix.txt");
    StorageForPython<<"[";
    for (int p=0; p<15; p++)
    {
        StorageForPython<<endl<<" [ "<<endl;
        for (int q=0; q<dat.depth(); q++)
        {
            StorageForPython<<"  [ ";
            for (int r=0; r<dat.width(); r++)
            {
                StorageForPython<<" ("<<real(dat(p,q,r))<<" + "<<imag(dat(p,q,r))<<"j), ";
            }
            StorageForPython<< " ], "<<endl;
        }
        StorageForPython<<" ], "<<endl<<endl;
    }
    StorageForPython<<"]";
}*/

void work_1(){
  ofstream dest("ыыыыы.txt");
  cout.precision(5);
  cout<<scientific;

  int n=100;
  int nz=50;//количество шагов


  double rho=5.96e3;

  double a=0.001;//апертура в метрах
  double f=160e6;//частота в герцах
  double dz=a/n;// 0.15 milimeters

  Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  //for (double g=90; g<180; g+=5){ angle
  Tensor t=tt.rotation_for_VB_picture_chang(10.0/180.0*M_PI);
  PolyMatrix p;

  Vector3 force(0,0,1);
  force.normalize();
   
  ofstream wavesLog("waves_vica.log");

  try
  {
    WaveMatrix waves=create_wave_matrix(n, a, f, t,force, rho);
    matrixfftw amat=pic_to_mat("D:\\backup\\progs\\horrible_tenzor-rar\\beam_struct_vica\\beam_struct\\fp_1.png");
    matrixfftw amatf(amat.height(),amat.width());
    plan ap(amat, amatf, FFTW_FORWARD,  FFTW_ESTIMATE);
    plan bp(amat, amatf, FFTW_BACKWARD, FFTW_ESTIMATE);
    ap.exec();
    waves.loadFFTW(amatf);

    Storage AmplitudeSquare(nz,n,n);
    for (int i=0; i<nz; i++)
    {
        waves.makeShift(-dz);
        Storage dat=waves.getStorage();
        Storage transform=layerTransform(dat,amat,amatf,bp);
        SpacialMatrix spaceMat=getSpaceMatrix(transform);
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
  /*  ofstream matrixText;
    matrixText.open("result_matrix.txt");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
      {
        matrixText<<"  "<<AmplitudeSquare(0,i,j);
      }
      matrixText<<endl;
    }*/
    matrix res(nz,n);   //поворот
    for (int i=0; i<nz; i++){
        for (int j=0; j<n; j++){
            res(i,j)=real(AmplitudeSquare(i,j,50));
        }
    }
   // stringstream dest;
   // dest<<"xy_fz//picture"<<g<<".png";
    saveAsPicture(res, "tryComplexRoot//vertical_sechenye2.png",1);

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

  //} angle
  }catch(string msg){cout<<"error:"<<msg<< endl;}
}


void work_1_derived()
{

    int n=100;
    int nz=50;//количество шагов


    double rho=5.96e3;

    double a=0.001;//апертура в метрах
    double f=20e6;//частота в герцах
    double dz=a/n;// 0.15 milimeters

    Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
    Tensor t=tt.rotation_for_VB_picture_chang(10.0/180.0*M_PI);
    //for (double g=90; g<180; g+=5){ angle

    PolyMatrix p;

    Vector3 force(0,0,1);
    force.normalize();

    ofstream wavesLog("waves_vica.log");

    try
    {
      for (int w = 0; w<1; w++)
      {
        WaveMatrix waves=create_wave_matrix(n, a, f+w*10e6, t,force, rho);
        stringstream freq;
        freq<<f+w*10e6;
        WaveMatrix homWave = waves;
        WaveMatrix nonHomWave = waves;
        matrix RootMap = waves.getRootMap();
        Criteria_For_Homogenious CrHom;
        Criteria_For_Nonhomogenious CrNHom;
        saveAsPicture(RootMap, "ripples//" + freq.str() + "_map.png",1); //карта корней

        matrixfftw amat=pic_to_mat("D:\\backup\\progs\\horrible_tenzor-rar\\beam_struct_vica\\beam_struct\\fp_1.png");
        matrixfftw amatf(amat.height(),amat.width());
        plan ap(amat, amatf, FFTW_FORWARD,  FFTW_ESTIMATE);
        plan bp(amat, amatf, FFTW_BACKWARD, FFTW_ESTIMATE);
        ap.exec();
        homWave.loadFFTW(amatf);
        nonHomWave.loadFFTW(amatf);

        matrix resFurie(amat.height(),amat.width());
        for (int i=0; i<amat.height(); i++)
        {
          for (int j=0; j<amat.width(); j++)
          {
              resFurie(i,j)=abs(amatf(i,j));
          }
        }
        saveAsPicture(resFurie, "ripples//" + freq.str() + "_furie.png",1); //фурье-образ

        homWave.eliminate(CrHom);
        nonHomWave.eliminate (CrNHom);

        Storage AmplitudeSquare1(nz,n,n);
        for (int i=0; i<nz; i++)
        {
           homWave.makeShift(-dz);
           Storage dat=homWave.getStorage();
          //Print_For_Python(dat);
           Storage transform=layerTransform(dat,amat,amatf,bp);
           SpacialMatrix spaceMat=getSpaceMatrix(transform);
           spaceMat.fillSliceWithV(i,AmplitudeSquare1);
        }

        matrix resH1(nz,n);
        for (int i=0; i<nz; i++)
        {
          for (int j=0; j<n; j++)
          {
              resH1(i,j)=real(AmplitudeSquare1(i,j,50));
          }
        }
        saveAsPicture(resH1,"ripples//" + freq.str() +"_homogenious_x.png",1); //срез по x

        for (int i=0; i<nz; i++)
        {
          for (int j=0; j<n; j++)
          {
              resH1(i,j)=real(AmplitudeSquare1(i,50,j));
          }
        }
        saveAsPicture(resH1,"ripples//" + freq.str() +"_homogenious_y.png",1); //срез по y

        matrix resH2(n,n);
        for (int i=0; i<n; i++)
        {
          for (int j=0; j<n; j++)
          {
              resH2(i,j)=real(AmplitudeSquare1(0,i,j)); //горизонтальный срез
          }
        }
        saveAsPicture(resH2,"ripples//" + freq.str() +"_homogenious_horizontal.png",1);

        for (int i=0; i<n; i++)
        {
          for (int j=0; j<n; j++)
          {
              resH2(i,j)=real(AmplitudeSquare1(25,i,j)); //горизонтальный срез со сдвигом
          }
        }
        saveAsPicture(resH2, "ripples//" + freq.str() +"_homogenious_horizontal_dz.png",1);

        Storage AmplitudeSquare2(nz,n,n);          //неоднородные волны
        for (int i=0; i<nz; i++)
        {
          nonHomWave.makeShift(-dz);
          Storage dat=nonHomWave.getStorage();
          //Print_For_Python(dat);
          Storage transform=layerTransform(dat,amat,amatf,bp);
          SpacialMatrix spaceMat=getSpaceMatrix(transform);
          spaceMat.fillSliceWithV(i,AmplitudeSquare2);
        }

        matrix resN1(nz,n);
        for (int i=0; i<nz; i++)
        {
          for (int j=0; j<n; j++)
          {
              resN1(i,j)=real(AmplitudeSquare2(i,j,50));
          }
        }
        saveAsPicture(resN1,"ripples//" + freq.str() +"_nonhomogenious_x.png",1);

        for (int i=0; i<nz; i++)
        {
          for (int j=0; j<n; j++)
          {
              resN1(i,j)=real(AmplitudeSquare2(i,50,j));
          }
        }
        saveAsPicture(resN1, "ripples//" + freq.str() +"_nonhomogenious_y.png",1);

        matrix resN2(n,n);
        for (int i=0; i<n; i++)
        {
          for (int j=0; j<n; j++)
          {
              resN2(i,j)=real(AmplitudeSquare2(0,i,j)); //горизонтальный срез
          }
        }
        saveAsPicture(resN2,"ripples//" + freq.str() +"_nonhomogenious_horizontal.png",1);

        for (int i=0; i<n; i++)
        {
          for (int j=0; j<n; j++)
          {
              resN2(i,j)=real(AmplitudeSquare2(25,i,j)); //горизонтальный срез со сдвигом
          }
        }
        saveAsPicture(resN2, "ripples//" + freq.str() +"_nonhomogenious_horizontal_dz.png",1);

     }

    }catch(string msg){cout<<"error:"<<msg<< endl;}
}

void test_kolich_korney_chang10()
{
   int n = 1000;
   double rho = 5.96e3;
   double f = 1e8*2*M_PI;
   Vector3 force(0,0,1);
  Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  Tensor t=tt.rotation_for_VB_picture_chang(-10*M_PI/180);

  try
  {
  ofstream dest("povRey.txt");
         for (int i=0; i<n; i++)
         {
            for (int j=0; j<n; j++)
            {
               double s_1=-0.002+(0.004/n)*i;
               double s_2=-0.002+(0.004/n)*j;

             //  double s_1 = 0;
            //   double s_2 = -0.00044;

                  CompositWave MyCW (s_1, s_2, t, force, rho, f);


             }
          }

    }
  catch(string msg)
  {
     cout << msg;
  }
}


void test_composit_wave(){
  Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
  Tensor t=tt.rotation_for_VB_picture_chang(0.0/180*M_PI);
  double rho=5.96e3;
  Vector3 force(0,0,1);
  force.normalize();
  try
  {
    CompositWave cv(296e-6, 103e-6, t,force, rho, 2*M_PI*1e8 );
   // cout<<endl;
    cout<<cv<<endl;
    Vector3c column=cv.TSum();
    cout<<"force"<<endl<<column<<endl;
    cout<<"matrix "<<endl<<cv<<endl;
  }
  catch(string msg)
  {
    cout<<"error: "<<msg<<endl;
  }

}

void testPol1()
{
   Vector3c a(complex<double>(-1102.84,0), complex<double>(-4.0958e-13,0), complex<double>(1.24549e-13,0));
   Vector3c b(complex<double>(-5.84609e-15,0), complex<double>(14091.7,0), complex<double>(71.8375,0));
   Vector3c c(complex<double>(1.37198e-13,0), complex<double>(71.8375,0), complex<double>(0.366217,0));

   Matrix3_c Matr(a,b,c);

   Vector3c polariz = Matr.calc_pol();
   cout<<"matrix "<<Matr<<endl;
   cout<<"polarization "<<polariz<<endl;
   cout<<"vector "<<(Matr*polariz)<<endl;
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
{
// test_kolich_korney_chang10();
 // getch();
 work_1_derived();
 //   work_1();

  return 0;

}


void work_2_derived()
{

    int n=100;
    int nz=1;//количество шагов


    double rho=5.96e3;

    double a=0.001;//апертура в метрах
    double f=20e6;//частота в герцах
    double dz=0;//a/n;// 0.15 milimeters

    Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
    Tensor t=tt.rotation_for_VB_picture_chang(0.0/180.0*M_PI);
    //for (double g=90; g<180; g+=5){ angle

    PolyMatrix p;

    Vector3 force(0,0,1);
    force.normalize();

    ofstream wavesLog("waves_vica.log");

    try
    {
      WaveMatrix waves=create_wave_matrix(n, a, f, tt,force, rho);
      waves.setOneToAll();
      WaveMatrix homWave = waves;
      WaveMatrix nonHomWave = waves;
      Criteria_For_Homogenious CrHom;
      Criteria_For_Nonhomogenious CrNHom;
      homWave.eliminate(CrHom);
      nonHomWave.eliminate (CrNHom);

      Storage AmplitudeSquare1(nz,n,n);
      Storage dat1;
      for (int i=0; i<nz; i++)
      {
          homWave.makeShift(dz);
          dat1=homWave.getStorage();

         // Storage transform=layerTransform(dat,amat,amatf,bp);
       //   SpacialMatrix spaceMat=getSpaceMatrix(transform);
       //   spaceMat.fillSliceWithV(i,AmplitudeSquare);
      }
      Print_For_Python(dat1);

      matrix res(n,n);   //поворот
      for (int i=0; i<n; i++){
          for (int j=0; j<n; j++){
              res(i,j)=real(dat1(11,i,j));
          }
      }
     // stringstream dest;
     // dest<<"xy_fz//picture"<<g<<".png";
      saveAsPicture(res, "tryComplexRoot//homogenious.png",1);
      Storage dat2;
      Storage AmplitudeSquare2(nz,n,n);
      for (int i=0; i<nz; i++)
      {
          nonHomWave.makeShift(dz);
          dat2=nonHomWave.getStorage();

       //   Storage transform=layerTransform(dat,amat,amatf,bp);
       //   SpacialMatrix spaceMat=getSpaceMatrix(transform);
       //   spaceMat.fillSliceWithV(i,AmplitudeSquare);
      }
      matrix res2(n,n);
      for (int i=0; i<n; i++)
      {
          for (int j=0; j<n; j++)
          {
              res2(i,j)=real(dat2(11,i,j));
          }
      }
     // stringstream dest;
     // dest<<"xy_fz//picture"<<g<<".png";
      saveAsPicture(res2, "tryComplexRoot//nonhomogenious.png",1);
  //    Print_For_Python(dat2);

    }catch(string msg){cout<<"error:"<<msg<< endl;}
}
