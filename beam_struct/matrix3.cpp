#include "matrix3.h"
#include <algorithm>
using namespace std;

     Matrix3::Matrix3(){
         for (int i = 0; i<3 ;++i)
             for (int j = 0; j<3; ++j)
                 dat[i][j]=0;
     }

     Matrix3::Matrix3(const Vector3 &a,const Vector3 &b, const Vector3 &c){
     for (int i=0; i<3; i++){
     dat[0][i]=a(i);
     }
     for (int i=0; i<3; i++){
     dat[1][i]=b(i);
     }
     for (int i=0; i<3; i++){
     dat[2][i]=c(i);
     }
     }


     ostream& operator<<(ostream& os, const Matrix3& r){
         return r >> os;

     }

     ostream&
     Matrix3::operator>>(ostream& os)const{
         for (int j=0; j<3; ++j){
             for (int i=0; i<3; ++i){
                 os<< dat[j][i]<<"\t";
             }
             os<<endl;
         }
         return os;
     }

      Vector3
      Matrix3::operator *( const Vector3& r )const{
          Vector3 ret;
          for (int k =0; k<3; ++k ){
              for (int j=0; j<3; ++j){
                  ret(k)+=dat[k][j]*r(j);   // a=a+b; a+=b;
              }
          }

          return ret;
      }

     double
     Matrix3::det(Matrix3 a) {
         double deter=a(0,0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1))-a(0,1)*(a(1,0)*a(2,2) - a(2,0)*a(1,2)) + a(0,2)*(a(1,0)*a(2,1)-a(2,0)*a(1,1));
         return deter;
}


      Polinom
      Matrix3::char_poly()const{
         const Matrix3& a=*this;//указатель на обьект для которого вызвана функция
         return Polinom(a(0,0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1))-
               a(0,1)*(a(1,0)*a(2,2) - a(2,0)*a(1,2)) +
               a(0,2)*(a(1,0)*a(2,1)-a(2,0)*a(1,1)),
               a(0,1)*a(1,0)-a(0,0)*a(1,1)-a(0,0)*a(2,2)+a(0,2)*a(2,0)-a(1,1)*a(2,2)+a(1,2)*a(2,1),
               a(0,0)+a(1,1)+a(2,2),
               -1);
}
      Vector3
      Matrix3::calc_pol()const{

          vector <double> alpha(3);

          Vector3 pol;

          Vector3 vec0;
          for (int i=0; i<3; i++){
              vec0(i)=dat[0][i];
          }

          vec0.normalize();


          Vector3 vec1;
          for (int i=0; i<3; i++){
              vec1(i)=dat[1][i];
          }

          vec1.normalize();


          Vector3 vec2;
          for (int i=0; i<3; i++){
              vec2(i)=dat[2][i];
          }

          vec2.normalize();


          Vector3 uno=vec0;
          Vector3 dos=vec1;

          for (int i=0; i<3; i++){
              alpha[0]+=vec0(i)*vec1(i);}

          for (int i=0; i<3; i++){
              alpha[1]+=vec1(i)*vec2(i);}

          for (int i=0; i<3; i++){
              alpha[2]+=vec2(i)*vec0(i);}

          for (int i=0; i<3; i++){
              alpha[i]=abs(alpha[i]);}

      int t=min_element(alpha.begin(),alpha.end())-alpha.begin();

      if(t==1){uno=vec1;dos=vec2;}
      if(t==2){uno=vec2;dos=vec0;}


      pol(0)=uno(1)*dos(2)-uno(2)*dos(1);
      pol(1)=dos(0)*uno(2)-uno(0)*dos(2);
      pol(2)=uno(0)*dos(1)-dos(0)*uno(1);

      pol.normalize();

      return pol;

      }

      Matrix3
      Matrix3::operator*(double v)const{
      Matrix3 res;
      for (int i=0; i<3; i++){
      for (int j=0; j<3; j++) {
      res(i,j)=dat[i][j]*v;
      }
      }
      return res;
      }
      Matrix3
      Matrix3::operator+ (const Matrix3& b)const{
          Matrix3 res;
          for (int i=0; i<3; i++){
          for (int j=0; j<3; j++) {
          res(i,j)=dat[i][j]*b(i,j);
          }
          }
          return res;

      }
