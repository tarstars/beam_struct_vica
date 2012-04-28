#ifndef WAVEMATRIX_H
#define WAVEMATRIX_H
#include "waveelement.h"
#include <vector>
using namespace std;
class WaveMatrix
{
    int n;
    vector <WaveElement> dat;
public:
    WaveMatrix(int n);
    WaveElement& operator() (int i, int j){return dat[i*n+j];};
    const WaveElement& operator() (int i, int j)const{return dat[i*n+j];};
};

#endif // WAVEMATRIX_H
