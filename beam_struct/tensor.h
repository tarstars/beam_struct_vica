#ifndef TENSOR_H
#define TENSOR_H

#include <iostream>

#include "matrix3.h"
#include "matrix3_c.h"

class PolyMatrix;

class Tensor{
    double dat[3][3][3][3];
public:
    Tensor();
    Matrix3 make_cristoffel(const Vector3&)const;
    double& operator() (int i, int  j , int k, int l){return dat[i][j][k][l];}
    const double& operator()(int i, int  j , int k, int l)const{return dat[i][j][k][l];}
    PolyMatrix make_polyMatrix(/*Tensor c,*/ double p, double s_1, double s_2)const;
    Tensor rotation(double phi, char p);
    Tensor rotation_for_VB_picture(double phi);
    Tensor rotation_for_VB_picture_1(double phi);
    std::ostream& operator>>(std::ostream& os)const;
};

std::ostream& operator<<(std::ostream& os, const Tensor& r);

#endif // TENSOR_H
