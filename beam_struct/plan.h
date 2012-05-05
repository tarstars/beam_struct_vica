#ifndef PLAN_H
#define PLAN_H
#include <fftw3.h>
#include "types.h"
class matrixfftw;
class plan
{
    fftw_plan p;
    fftw_complex *in;
    fftw_complex *out;
public:
    plan(matrixfftw& a,matrixfftw& b,int dir, int mode);
    void exec();
    ~plan();

};

#endif // PLAN_H?
