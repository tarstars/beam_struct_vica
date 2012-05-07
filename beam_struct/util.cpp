#include "util.h"
#include "math.h"
#include "matrixFFTW.h"
#include "storage.h"
#include "plan.h"
#include "spacialmatrix.h"

#include<iostream>
#include<fstream>

using namespace std;

int ind_conv(int a, int b) {
    int mass[3][3]={
    { 0, 5, 4},
    { 5, 1, 3},
    { 4, 3, 2}
   };

   return mass[a][b];
}

ostream&
operator<<(ostream& os, const vector<CD>& a){
    for (int t = 0; t < int(a.size()); ++t)
        os << a[t] << " ";
    return os;
}

ostream&
operator<<(ostream& os, const vector<double>& a){
    for (int t = 0; t < int(a.size()); ++t)
        os << a[t] << " ";
    return os;
}


Tensor make_material_tensor (double c11, double c12, double c13, double c33, double c66, double c44){

    double mat[][6]={
        {c11, c12, c13,    0,     0,     0},
        {c12, c11, c13,    0,     0,     0},
        {c13, c13, c33,    0,     0,     0},
        {0,    0,    0,    c44,   0,      0},
        {0,    0,    0,    0,     c44,   0},
        {0,    0,    0,    0,     0,     c66}
    };


    Tensor ret;

    for (int i = 0; i < 3 ;++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                for (int l = 0; l < 3; l++)
                    ret(i, j, k, l) = mat[ ind_conv(i, j)][ ind_conv(k, l)];

    return ret;
}

double multiplic (int i) {
       double mat3[3][3]= {
           { 1, 2, 1},
           { 0, 3, 0},
           { 1, 2, 3}
       };
       double B3[1][3] = {
           { 1, 1, 1}
       };
       for (int i=0; i<3; ++i)
       B3[i][1] = mat3[1][i]*B3[i][1] + mat3[2][i]*B3[i][1] + mat3[3][i]*B3[i][1];


       return B3[1][3];
}

ostream& get_log(){
   static ofstream flog("log.txt");
   return flog;
}

vector<double> real_part(vector <CD> f){
    vector<double> d;
    int j=0;
    for (int i=0; i<int(f.size()); i++){
        if (((abs(imag(f[i]))<1e-5))&&(abs(real(f[i]))>(1e-15))){
        d.resize(j+1);
        d[j]=real(f[i]);
        j++;
    }
}
    return d;
}

vector <CD> image_part(vector <CD> f){
    vector <CD> d;
    int j=0;
    for (int i=0; i<int(f.size()); i++){
        if (imag(f[i])>1e-5){
        d.resize(i+1);
        d[j]=f[i];
        j++;
    }
}
 return d;
}

/*ostream& getLog(){
static ofstream ret("sz.txt");
return ret;
}*/

WaveMatrix create_wave_matrix(int n, double a, double f,const Tensor& t,const Vector3& force, double rho){

  WaveMatrix ret(n);
  
  double omega(2*M_PI*f);

  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      double s_1=0;//i - vert
      double s_2=0;//j - hor

      if (i<(n/2)){
	s_1=(1/a/f)*i;
      }
      else { 
	s_1=+(1/a/f)*i-2*(1/a/f)*(n/2);
      }

      if (j<(n/2)){
	s_2=(1/a/f)*j;
      }
      else {
	s_2=+(1/a/f)*j-2*(1/a/f)*(n/2);
      }

      ret(i,j)=WaveElement(s_1, s_2, t,force, rho, omega);
    }
    //getLog()<<endl;
  }
  
return ret;
}

Matrix3 create_tensor_S(const Vector3& k,const Vector3& q){
    Matrix3 res;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            res(i,j)=1./2*(q(i)*k(j)+q(j)*k(i));
        }
    }
    return res;
};

Matrix3 create_tensor_T (const Matrix3& S, const Tensor& t){
    Matrix3 res;
    for (int i=0; i<3; i++){
       for (int j=0; j<3; j++){
          for (int k=0; k<3; k++){
              for (int l=0; l<3; l++){
              res(i,j)+=t(i,j,k,l)*S(k,l);}
          }
       }
    }
    return res;

}


matrixfftw pic_to_mat(string flnm){
    QImage im1(flnm.c_str());

    double w1=im1.width();
    double h1=im1.height();
    if ((w1==0)||(h1==0)){throw(string ("pic_to_mat::empty picture"));}
matrixfftw Mat1(h1,w1);
    for (int i=0; i<h1; i++){
        for (int j=0; j<w1; j++){
            Mat1(i,j)=(qGray(im1.pixel(j,i)))/255;
        }
    }
    return Mat1;}

Storage layerTransform(const Storage& stor,matrixfftw& a,matrixfftw& b, plan& pl){
    Storage stor_res(stor.height(),stor.depth(),stor.width());
    for (int i=0; i<(PlaneWave::getDimensions()); i++){
        for (int p=0; p<(stor.depth()); p++){
            for (int q=0; q<(stor.width()); q++){
                a(p,q)=stor(i,p,q);
            }
        }
        pl.exec();
        for (int p=0; p<(stor.depth()); p++){
            for (int q=0; q<(stor.width()); q++){
                stor_res(i,p,q)=b(p,q)/double(stor.depth()*stor.width());
            }
        }

    }
    return stor_res;
}

SpacialMatrix getSpaceMatrix(const Storage& stor){
    if(stor.width()!=stor.depth())
        throw (string ("getSpaceMatrix: dimensions in storage are mismatched"));

    SpacialMatrix result(stor.width());
    for (int p = 0; p < stor.depth(); p++){
        for (int q = 0; q < stor.depth(); q++){
            result(p, q).takeFromStorage(p, q, stor);
        }
    }


    return result;
}
