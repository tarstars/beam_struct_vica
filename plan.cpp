#include "plan.h"
#include "types.h"
#include "matrixfftw.h"

plan::plan(matrixfftw& a,matrixfftw& b,int dir, int mode){
    p=fftw_plan_dft_2d(a.h, a.w ,a.in, b.in, dir, mode);
};
void
plan::exec(){
    fftw_execute(p);
}

plan::~plan(){
    fftw_destroy_plan(p);
}
