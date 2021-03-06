#ifndef WAVEMATRIX_H
#define WAVEMATRIX_H

#include "waveelement.h"
#include "criteria.h"
#include "matrix.h"

#include <fstream>
#include <vector>

class Storage;

class WaveMatrix{

    int n;
    std::vector <WaveElement> dat;

public:

    WaveMatrix(int n);
    WaveElement& operator() (int i, int j){return dat[i*n+j];}

    const WaveElement& operator() (int i, int j)const{return dat[i*n+j];}

    void loadFFTW(const matrixfftw& r);

    Storage getStorage()const;

    matrix getRootMap() const;

    void logState(std::ostream&);
    void makeShift(double delta_z);

    void makeZShift (double);

    void eliminate (criteria& type);
    void setOneToAll ();

    friend std::ostream& operator<<(std::ostream& os, const WaveMatrix&);
};
std::ostream& operator<<(std::ostream& os, const WaveElement& r);

#endif // WAVEMATRIX_H
