#include "matrix3_c.h"
#include "util.h"

using namespace std;
typedef complex<double> CD;

Matrix3_c::Matrix3_c(){
    for (int i = 0; i<3 ;++i)
        for (int j = 0; j<3; ++j)
            dat[i][j]=0;
}

Matrix3_c::Matrix3_c(const Vector3c &a,const Vector3c &b, const Vector3c &c){
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

Vector3c
Matrix3_c::operator *( const Vector3c& r )const{
    Vector3c ret;
    for (int k =0; k<3; ++k ){
        for (int j=0; j<3; ++j){
            ret(k)+=dat[k][j]*r(j);   // a=a+b; a+=b;
        }
    }

    return ret;
}

std::complex<double>
Matrix3_c::det(Matrix3_c a) {
    std::complex<double> deter=a(0,0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1))-a(0,1)*(a(1,0)*a(2,2) - a(2,0)*a(1,2)) + a(0,2)*(a(1,0)*a(2,1)-a(2,0)*a(1,1));
    return deter;
}

Polinom Matrix3_c::char_poly()const
{
  const Matrix3_c& a=*this;//указатель на обьект для которого вызвана функция
  return Polinom(a(0,0)*(a(1,1)*a(2,2) - a(1,2)*a(2,1))-
                 a(0,1)*(a(1,0)*a(2,2) - a(2,0)*a(1,2)) +
                 a(0,2)*(a(1,0)*a(2,1)-a(2,0)*a(1,1)),
                 a(0,1)*a(1,0)-a(0,0)*a(1,1)-a(0,0)*a(2,2)+a(0,2)*a(2,0)-a(1,1)*a(2,2)+a(1,2)*a(2,1),
                 a(0,0)+a(1,1)+a(2,2),
                 -1);
}

/*Vector3c Matrix3_c::calc_pol_C()const
{
    Vector3c vec0;
    for (int i=0; i<3; i++)
    {
      vec0(i)=dat[0][i];
    }
    Vector3c vec1;
    for (int i=0; i<3; i++)
    {
      vec1(i)=dat[1][i];
    }
    Vector3c vec2;
    for (int i=0; i<3; i++)
    {
      vec2(i)=dat[2][i];
    }
    Vector3c result1=vecMultiplic(vec0,vec1);
    Vector3c result2=vecMultiplic(vec1,vec2);
    Vector3c result3=vecMultiplic(vec0,vec2);

    Vector3c module;
    module[0]=result1.abs();
    module[1]=result2.abs();
    module[2]=result3.abs();

}*/


Vector3c Matrix3_c::calc_pol()const
{
  vector <CD> alpha(3);
  Vector3c pol;
  Vector3c vec0;
  for (int i=0; i<3; i++)
  {
    vec0(i)=dat[0][i];
  }
  Vector3c vec1;
  for (int i=0; i<3; i++)
  {
    vec1(i)=dat[1][i];
  }
  Vector3c vec2;
  for (int i=0; i<3; i++)
  {
    vec2(i)=dat[2][i];
  }
  complex<double> l1=vec0.abs();
  complex<double> l2=vec1.abs();
  complex<double> l3=vec2.abs();
  if (min(min(real(l1),real(l2)),real(l3))<max(max(real(l1),real(l2)),real(l3))*1e-7)//смотрим есть ли 0-вой вектор, есть ли модуль вектора который равен 0
  {
    if(real(l1)<min(real(l2),real(l3)))
    {
      Vector3c pol;
      Vector3c uno=vec1;
      Vector3c dos=vec2;
      pol(0)=uno(1)*dos(2)-uno(2)*dos(1);
      pol(1)=dos(0)*uno(2)-uno(0)*dos(2);
      pol(2)=uno(0)*dos(1)-dos(0)*uno(1);
      pol.normalize();
      return pol;
    }
    if(real(l2)<min(real(l1),real(l3)))
    {
      Vector3c pol;
      Vector3c uno=vec0;
      Vector3c dos=vec2;
      pol(0)=uno(1)*dos(2)-uno(2)*dos(1);
      pol(1)=dos(0)*uno(2)-uno(0)*dos(2);
      pol(2)=uno(0)*dos(1)-dos(0)*uno(1);
      pol.normalize();
      return pol;
    }
    if (real(l3)<min(real(l2),real(l1)))
    {
      Vector3c pol;
      Vector3c uno=vec0;
      Vector3c dos=vec1;
      pol(0)=uno(1)*dos(2)-uno(2)*dos(1);
      pol(1)=dos(0)*uno(2)-uno(0)*dos(2);
      pol(2)=uno(0)*dos(1)-dos(0)*uno(1);
      pol.normalize();
      return pol;
    }
  }
  vec0.normalize();
  vec1.normalize();
  vec2.normalize();
  Vector3c uno=vec0;
  Vector3c dos=vec1;

  for (int i=0; i<3; i++)
  {
    alpha[0]+=vec0(i)*conj(vec1(i));
  }
  for (int i=0; i<3; i++)
  {
    alpha[1]+=vec1(i)*conj(vec2(i));
  }
  for (int i=0; i<3; i++)
  {
    alpha[2]+=vec2(i)*conj(vec0(i));
  }
  for (int i=0; i<3; i++)
  {
    alpha[i]=abs(alpha[i]);
  }
  vector <double> alphaReal=real_part(alpha);
  int t=min_element(alphaReal.begin(),alphaReal.end())-alphaReal.begin();
  if(t==1)
  {
    uno=vec1;dos=vec2;
  }
  if(t==2)
  {
    uno=vec2;dos=vec0;
  }

  pol(0)=uno(1)*dos(2)-uno(2)*dos(1);
  pol(1)=dos(0)*uno(2)-uno(0)*dos(2);
  pol(2)=uno(0)*dos(1)-dos(0)*uno(1);
  pol.normalize();
  return pol;
}

ostream& operator<<(ostream& os, const Matrix3_c& r){
    return r >> os;
}

Matrix3_c
Matrix3_c::operator*(complex<double> v)const{
    Matrix3_c res;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++) {
            res(i,j)=dat[i][j]*v;
        }
    }
    return res;
}

Matrix3_c
Matrix3_c::operator+ (const Matrix3_c& b)const{
    Matrix3_c res;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++) {
            res(i,j)=dat[i][j]*b(i,j);
        }
    }
    return res;

}

void
Matrix3_c::logState(ostream& os)const{
  for(int p = 0; p < 3; ++p)
    for(int q = 0; q < 3; ++q)
      os << (*this)(p,q) << " ";
}

ostream&
Matrix3_c::operator>>(ostream& os)const{
    for (int j=0; j<3; ++j){
        for (int i=0; i<3; ++i){
            os<< dat[j][i]<<"\t";
        }
        os<<endl;
    }
    return os;
}
