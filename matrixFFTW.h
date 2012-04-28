#ifndef MATRIXFFTW_H
#define MATRIXFFTW_H

#include <complex>
#include <fftw3.h>
#include "types.h"

class matrixfftw
{
    fftw_complex *in;
    int h;
    int w;
    matrixfftw& operator =(const matrixfftw&){return *this;}
public:
    matrixfftw(int h, int w);
    matrixfftw(const matrixfftw&);
    CD& operator()(int i,int j) {return *((CD*)(in+i*w+j));}
    const CD& operator()(int i,int j)const {return *((CD*)(in+i*w+j));}
    int height(){return h;};
    int width(){return w;};
    ~matrixfftw();
    void pd(std::ostream&)const;
    friend class plan;
    friend std::ostream& operator <<(std::ostream& os, const matrixfftw& r);

};

std::ostream& operator <<(std::ostream& os,const matrixfftw& r);

#endif // MATRIX3_H
