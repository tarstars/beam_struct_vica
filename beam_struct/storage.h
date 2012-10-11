#ifndef STORAGE_H
#define STORAGE_H
#include <vector>
#include "types.h"
#include <iostream>

class Storage
{
    int h;
    int d;
    int w;
    std:: vector<CD> dat;
public:
    Storage();
    Storage(int a, int b, int c);
    CD& operator() (int k, int i,int j){return dat.at(k*d*w+i*w+j);}
    const CD& operator() (int k, int i, int j)const{return dat.at(k*d*w+i*w+j);}
    std::ostream& operator>>(std::ostream& os)const;
    int height()const{return h;}
    int depth()const{return d;}
    int width()const{return w;}

};
std::ostream& operator<<(std::ostream& os, const Storage& r);
#endif // STORAGE_H
