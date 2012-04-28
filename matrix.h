#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
#include <iostream>
class matrix
{
    int h;
    int w;
   std::vector <double> dat;
public:
    matrix(int a, int b);
    matrix(){}
    double& operator() (int i, int j){return dat[i*w+j];};
    const double& operator() (int i, int j)const{return dat[i*w+j];};
    std::ostream& operator>>(std::ostream& os)const;
};
std::ostream& operator<<(std::ostream& os, const matrix& r);
#endif // MATRIX_H
