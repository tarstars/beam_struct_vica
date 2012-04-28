#include "wavecomposit.h"
#include "polymatrix.h"
#include "matrix3.h"
#include "util.h"
#include "storage.h"
#include <algorithm>
#include <iostream>
#include <fstream>


using namespace std;
CompositWave::CompositWave()
{
}
CompositWave::CompositWave(double s_1, double s_2, const Tensor& t, double rho,double omega)
{   //cout<<"from composite wave"<<"  "<<s_1<<"  "<<s_2<<endl;
    PolyMatrix p=t.make_polyMatrix(rho,s_1,s_2);
    Polinom d;
    d=p.Determinant();
    vector<CD> f;
    f=d.all_roots();
    double eps=1e-6;
    vector<double> fplus;
    for (int i=0; i<int(f.size()); i++){
        if (abs(imag(f[i]))>=eps) {
            stringstream dest;
            dest<<"imaginary root in compvawe ("<<s_1<<","<<s_2<<")"<<endl;
            throw (string(dest.str()));}
        if (real(f[i])<0) {fplus.push_back(real(f[i]));}
    }
    if (fplus.size()!=3){
        stringstream dest;
        dest<<"ne 3 kornya"<<endl;
        throw (string(dest.str()));}
    ofstream ves;
    ves.open("weight.txt");
   // cout<<" "<<fplus<<"  eto korny"<<endl<<endl;
    //getLog() << *max_element(fplus.begin(), fplus.end())<<"  ";

    for (int r=0; r<3; ++r){
    pav[r]=PlaneWave(s_1,s_2, fplus[r], p, t, rho, omega);
    }

    Matrix3 work;
    for (int i=0; i<3; i++){
        Matrix3 help=pav[i].T;
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

Vector3 force;
force(0)=0.6;
force(1)=0.8;
force(2)=0;
double determ=work.det(work);

/*for (int i=0; i<3; i++){
    Matrix3 work_dop=work;
    for (int k=0; k<3; k++){
        work_dop(k,i)=force(k);}
    double det_dop=work_dop.det(work_dop);
  //  ves<<i<<"  dopolnit. opredelitel "<<det_dop<<endl;
    //ves<<" opredilitel "<<determ<<endl;
    weight(i)=det_dop/determ;
    //cout<<weight(i)<<endl;
    ves<<"x"<<i<<"=det_dop/determ= "<<weight(i)<<endl<<endl;
}
cout<<endl<<endl;*/


storage stor(10,10,15);

Matrix3 resul;
for(int i=0; i<3; ++i){
   // ves<<endl<<pav[i].T<<endl;
    resul=resul+pav[i].T*weight(i);
}
ves<<"pri slojenii s vesami 3-h T"<<endl;
ves<<resul<<endl<<endl;

Matrix3 resul_S;                             //прибираем S
for(int i=0; i<3; ++i){
    resul_S=resul_S+pav[i].S*weight(i);
}
ves<<"pri slojenii s vesami 3-h S"<<endl;
ves<<resul_S<<endl;

vector<double> s_vec(9);
int l=0;
for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
        s_vec.at(l)=resul_S(i,j);
        l++;
    }
}
for (int l=0; l<9;l++){
stor(1,0,l)=s_vec.at(l);
}

Vector3 resul_q;                        //прибираем q
for(int i=0; i<3; ++i){
    resul_q=resul_q+pav[i].q*weight(i);
}
ves<<"pri slojenii s vesami 3-h q"<<endl;
ves<<resul_q<<endl;

vector<double> q_vec(3);
for (int i=0; i<3; i++){
        q_vec.at(l)=resul_q(i);
        l++;
    }


for (int j=0; j<3; j++){
stor(1,0,j+9)=q_vec.at(j);
}

}
/*storage serialize (int p, int q){
    Matrix3 resul;
    for(int i=0; i<3; ++i){
        ves<<endl<<pav[i].T<<endl;
        resul=resul+pav[i].T*weight(i);
    }
    ves<<"pri slojenii s vesami 3-h T"<<endl;
    ves<<resul<<endl<<endl;

    Matrix3 resul_S;
    for(int i=0; i<3; ++i){
        ves<<endl<<pav[i].S<<endl;
        resul=resul+pav[i].S*weight(i);
    }
    ves<<"pri slojenii s vesami 3-h S"<<endl;
    ves<<resul_S<<endl;

}*/





/*Matrix3 Serialize(vector3 weight)
{
    Matrix3 resul;
    for(int i=0; i<3; ++i){
        resul+=pav[i].T*weight(i);
    }
}*/

std::ostream& operator<<(std::ostream& os, const CompositWave& r){
    os<<"composit wave:"<<endl;
    for(int t=0; t<3; ++t){
    os<<r.pav[t]<<endl;
    }

    return os;

};
