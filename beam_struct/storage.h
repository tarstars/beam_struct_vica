#ifndef STORAGE_H
#define STORAGE_H
#include <vector>
#include "types.h"
#include <iostream>

class storage
{
    int h;
    int w;
    int d;
    std:: vector<CD> dat;
public:
    storage();
    storage(int a, int b, int c);
    CD& operator() (int i, int j,int k){return dat[k*h*w+i*w+j];};
    const CD& operator() (int i, int j, int k)const{return dat[k*h*w+i*w+j];};
    std::ostream& operator>>(std::ostream& os)const;
};
std::ostream& operator<<(std::ostream& os, const storage& r);
#endif // STORAGE_H
