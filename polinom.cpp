#include "polinom.h"
#include <cmath>
#include <iostream>
//#include <gsl/gsl_poly.h>
using namespace std;

ostream&
Polinom::operator>>(ostream& os)const{
    for (int i=0; i<int(dat.size()); ++i){
    os << dat[i]<<"  ";
    }
    return os;
}
 ostream&
 operator<<(ostream& os, const Polinom& r){
     return r>>os;

 }
ostream&
operator<<(ostream& os, const RetVal& r){
    return os<<r.val<<" "<< r.vald <<" "<<r.valdd;
}

Polinom::Polinom(){
}

Polinom::Polinom(const CD& a0,const CD& a1):dat(2){
    dat[1]=a1;
    dat[0]=a0;

}

Polinom::Polinom(const CD& a0):dat(1){
    dat[0]=a0;
}

Polinom::Polinom(const CD& a0, const CD& a1, const CD& a2):dat(3){
    dat[2]=a2;
    dat[1]=a1;
    dat[0]=a0;

}

Polinom::Polinom(const CD& a0,const CD& a1, const CD& a2, const CD& a3, const CD& a4):dat(5){
    dat[4]=a4;
    dat[3]=a3;
    dat[2]=a2;
    dat[1]=a1;
    dat[0]=a0;
}

Polinom::Polinom(const CD& a0,const CD& a1, const CD& a2, const CD& a3):dat(4){
    dat[3]=a3;
    dat[2]=a2;
    dat[1]=a1;
    dat[0]=a0;
}

RetVal
Polinom::count(const CD &x) const{
    CD ret=0;
    CD retd=0;
    CD retdd=0;
    CD p(1,0);

    for (int t = int(dat.size()) - 1; t>=0; --t) {
        retdd = retdd*x + retd;
        retd=retd*x+ret;
        ret = ret*x+dat[t];
    }
    retdd*=2;

    return RetVal(ret, retd,retdd);
}

Polinom
Polinom::bez_u(const CD & x) const{
    Polinom ret=byDegree(deg()-1);
    CD s=0;
    for (int i =0; i<deg(); i++){
        s=s*x+dat[deg()-i];
        ret.dat[deg()-1-i]=s;
    }

    return ret;
}

vector<CD>
Polinom::all_roots() const{
    vector<CD> ret(deg());
    Polinom tmp=*this;
    for (int i=0; i< deg(); i++){
        CD rt=tmp.root();
        ret[i]=rt;
        tmp=tmp.bez_u(rt);
    }

    return ret;
}

/*vector <CD>
Polinom::all_roots()const{
  vector <CD> ret(deg());
  vector<double> coeff(dat.size());
  for(int t = 0; t < int(dat.size()); ++t)
    coeff[t] = real(dat[t]);

  vector<double> res(2 * deg());

  gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc(dat.size());

  gsl_poly_complex_solve(&coeff[0], dat.size(), w, &res[0]);

  gsl_poly_complex_workspace_free(w);

  for(int t = 0; t < int(deg()); ++t){
    ret[t] = complex<double>(res[2 * t], res[2 * t + 1]);
  }

  return ret;
}*/


int
Polinom::deg() const{
    int n=dat.size() - 1;
    return n;
}



CD
Polinom::root() const{
        //cerr << "polinom::root" << endl;
    CD x = 1;
    CD a = 1.5;
    for (int k=0; k<1000 && abs(a) > 1e-14; ++k){

        RetVal rv=count(x);
        if(abs(rv.val) < 1e-14)
           return x;

        int n = deg();
        CD g = rv.vald / rv.val;
        CD h = g * g - rv.valdd / rv.val;
        CD ddenum = sqrt((n - 1.0) * (h * double(n) - g * g));
        CD denum1 = g + ddenum;
        CD denum2 = g - ddenum;
        CD denum = 0;
        if(abs(denum1) > abs(denum2))
            denum = denum1;
        else
            denum = denum2;
        a = double(n)/denum;
        x-=a;
    }
   // cout << "\tk = " << k << " x = "
    return x;
}

Polinom Polinom::operator *(const Polinom &b)const{
    Polinom c=byDegree(deg()+b.deg());
    for (int i=0; i<int(dat.size()); i++){
        for (int j=0; j<int(b.dat.size()); j++){
            c.dat[i+j]+=dat[i]*b.dat[j];
        }
    }
    return c;
}

Polinom Polinom::operator +(const Polinom &b)const{
    int maxi=0;
    int mini=0;
    if (deg()>b.deg()){
        maxi=dat.size();
        mini =b.dat.size();}
    else{ maxi=b.dat.size();
        mini=dat.size();}
    Polinom c=byDegree(maxi-1);
    for (int i=0; i<maxi; i++){
        if (i<mini)
            c.dat[i]=dat[i]+b.dat[i];
        else{
            if (deg()>b.deg()) {c.dat[i]=dat[i];}
            else c.dat[i]=b.dat[i];
        }
    }
   return c;
}
Polinom Polinom::operator -(const Polinom &b)const{
    int maxi=0;
    int mini=0;
    if (deg()>b.deg()){
        maxi=dat.size();
        mini =b.dat.size();}
    else{ maxi=b.dat.size();
        mini=dat.size();}
    Polinom c=byDegree(maxi-1);
    for (int i=0; i<maxi; i++){
        if (i<mini)
            c.dat[i]=dat[i]-b.dat[i];
        else{
            if (deg()>b.deg()) {c.dat[i]=dat[i];}
            else c.dat[i]=-b.dat[i];
        }
    }
   return c;

}
