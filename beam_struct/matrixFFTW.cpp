#include "matrixFFTW.h"
#include <fftw3.h>
#include <complex>
#include "types.h"
#include <cstring>
using namespace std;

matrixfftw::matrixfftw(int hh, int ww):h(hh),w(ww)
{
    in=(fftw_complex*)fftw_malloc(h*w*sizeof(fftw_complex));
}

matrixfftw::matrixfftw(const matrixfftw & r):h(r.h),w(r.w){
    in=(fftw_complex*)fftw_malloc(h*w*sizeof(fftw_complex));
    memcpy(in, r.in, (h*w*sizeof(fftw_complex)));
}

std::ostream& operator <<(std::ostream& os,const matrixfftw& r){
for (int i=0; i<r.h; i++){
     for (int j=0; j<r.w; j++){
      os<<r(i,j);
     }
     }
return os;
}

void
matrixfftw::pd(ostream& os)const{
    os << h << " " << w << endl;
}


matrixfftw::~matrixfftw()
{
    fftw_free(in);
}
