#include "tensor.h"
#include "util.h"
#include <iostream>
#include "polymatrix.h"

using namespace std;
Tensor:: Tensor(){
    for (int i = 0; i<3 ;++i)
        for (int j = 0; j<3; ++j)
            for (int k = 0; k<3; ++k)
                for (int l = 0; l<3; l++)
                    dat[i][j][k][l]=0;
}


ostream& operator<<(ostream& os, const Tensor& r){
    return r >> os;

}

ostream&
Tensor::operator>>(ostream& os)const{
    for (int j=0; j<3; ++j){
        for (int l=0; l<3; ++l){
            for (int i=0; i<3; ++i){
                for (int k=0; k<3; ++k)
                   // if (abs(dat[j][l][i][k]) > 1)
                    os<<" "<< dat[j][l][i][k]<<"  ";
                    os<<"\t";
            }
            os<<endl;
        }
       os<< endl;
    }
    return os;
}

  Matrix3
  Tensor::make_cristoffel(const Vector3& n)const{
      Matrix3 ret;
      for (int i=0; i<3; ++i){
          for (int l=0; l<3; ++l){
              for (int j=0; j<3; ++j){
                  for (int k=0; k<3; ++k){
                      double val = dat[i][j][k][l]*n(j)*n(k);
                      ret(i,l)+= val;
                  }
              }
          }
      }
      return ret;
  }

  PolyMatrix Tensor::make_polyMatrix(/*Tensor c,*/ double p, double s_1, double s_2)const{
      double s[]={s_1,s_2};
     PolyMatrix dat;
      for (int i=0;i<3; i++){//closed
          for (int k=0; k<3;k++){
               double f=0;
              for (int j=0; j<2;j++){//closed
                  for (int l=0; l<2;l++){

                      f+=(*this)(i,j,k,l)*s[j]*s[l];
                     // cout<<c(i,j,k,l)<<" "<<s[j]<<" "<<s[i]<<endl;

                  }
              }
             double a0=f;
            // cout<<a0<<endl;
              double d=0;
              for (int j=0; j<2; j++){d+=(*this)(i,j,k,2)*s[j];}
              for (int l=0;l<2; l++){d+=(*this)(i,2,k,l)*s[l];}
              double a1=d;
              double a2=(*this)(i,2,k,2);
              if(i==k){a0+=(-p);};
              dat(i,k)=Polinom(a0,a1,a2);

      }
  }
      return dat;
  }

  Tensor
  Tensor:: rotation( double phi, char p){
      Matrix3 m;
      Tensor res;
  if (p=='x'){
      m(0,0)=1;
      m(0,1)=0;
      m(0,2)=0;
      m(1,0)=0;
      m(1,1)=cos(phi);
      m(1,2)= - sin(phi);
      m(2,0)=0;
      m(2,1)=sin(phi);
      m(2,2)=cos(phi);}

  if (p=='y'){
      m(0,0)=cos(phi);
      m(0,1)=0;
      m(0,2)=sin(phi);
      m(1,0)=0;
      m(1,1)=1;
      m(1,2)=0;
      m(2,0)=-sin(phi);
      m(2,1)=0;
      m(2,2)=cos(phi);}

  if (p=='z'){
      m(0,0)=cos(phi);
      m(0,1)=-sin(phi);
      m(0,2)=0;
      m(1,0)=sin(phi);
      m(1,1)=cos(phi);
      m(1,2)=0;
      m(2,0)=0;
      m(2,1)=0;
      m(2,2)=1;}


  for (int p=0; p<3; p++)
  {
    for (int q=0; q<3; q++)
    {
      for (int r=0; r<3; r++)
      {
        for (int s=0; s<3; s++)
        {
          for( int i=0; i<3; i++)
          {
            for (int j=0; j<3; j++)
            {
              for (int k=0; k<3; k++)
              {
                for (int l=0; l<3; l++)
                {
                  res(p,q,r,s)+=dat[i][j][k][l]*m(i,p)*m(j,q)*m(k,r)*m(l,s);
                }
              }
            }
          }
        }
      }
    }
  }
   return res;
  }

  Tensor
  Tensor:: rotation_for_VB_picture_chang( double phi)
  {
    Matrix3 m;
    Tensor res;

    m(1,0)=sin(phi)/(sqrt(2));
    m(1,1)=sin(phi)/(sqrt(2));
    m(1,2)=cos(phi);
    m(0,0)=-1/(sqrt(2));
    m(0,1)=1/(sqrt(2));
    m(0,2)=0;
    m(2,0)=cos(phi)/(sqrt(2));
    m(2,1)=cos(phi)/(sqrt(2));
    m(2,2)=-sin(phi);


      for (int p=0; p<3; p++)
      {
        for (int q=0; q<3; q++)
        {
          for (int r=0; r<3; r++)
          {
            for (int s=0; s<3; s++)
            {
              for( int i=0; i<3; i++)
              {
                for (int j=0; j<3; j++)
                {
                  for (int k=0; k<3; k++)
                  {
                    for (int l=0; l<3; l++)
                    {
                       res(p,q,r,s)+=dat[i][j][k][l]*m(p,i)*m(q,j)*m(r,k)*m(s,l);
                    }
                  }
                }
              }
            }
          }
        }
      }
   return res;
  }

  Tensor
  Tensor:: rotation_for_VB_picture_z( double phi)
  {
    Matrix3 m;
    Tensor res;
    m(1,0)=0;
    m(1,1)=0;
    m(1,2)=1;
    m(0,0)=cos(phi);
    m(0,1)=sin(phi);
    m(0,2)=0;
    m(2,0)=-sin(phi);
    m(2,1)=cos(phi);
    m(2,2)=0;


    for (int p=0; p<3; p++){
      for (int q=0; q<3; q++){
          for (int r=0; r<3; r++){
              for (int s=0; s<3; s++){
                 // res(p,q,r,s)=0;
                  for( int i=0; i<3; i++){
                      for (int j=0; j<3; j++){
                          for (int k=0; k<3; k++){
                              for (int l=0; l<3; l++){
          res(p,q,r,s)+=dat[i][j][k][l]*m(p,i)*m(q,j)*m(r,k)*m(s,l);}
      }
      }
      }
      }
      }
      }
  }
   return res;
  }

