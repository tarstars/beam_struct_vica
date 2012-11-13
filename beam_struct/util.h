#ifndef UTIL_H
#define UTIL_H

#include "tensor.h"
#include "matrixFFTW.h"
#include "wavematrix.h"
#include <QImage>
#include <string.h>


class Tensor;
class matrixfftw;
class Storage;
class plan;
class SpacialMatrix;
class matrix;

std::vector <CD> image_part(std::vector<CD>) ;
std::vector <double> real_part(std::vector<CD>);

Tensor make_material_tensor (double, double, double, double, double, double);
std::ostream& operator<<(std::ostream& os, const std::vector<CD>& a);
std::ostream& operator<<(std::ostream& os, const std::vector<double>& a);
std::ostream& get_log();

WaveMatrix create_wave_matrix(int n, double a, double f,const Tensor& t,const Vector3& force, double rho);
Matrix3 create_tensor_S(const Vector3& k, const Vector3& q);
Matrix3 create_tensor_T (const Matrix3& S, const Tensor& t);

matrixfftw pic_to_mat(std::string flnm);

Storage layerTransform(const Storage& stor,matrixfftw&a,matrixfftw&b, plan& pl);

SpacialMatrix getSpaceMatrix(const Storage& stor);

std::ostream& getLog();

void saveAsPicture(const matrix& a, std::string flnm, double gamma);
void saveAsPictureFFTW(const matrixfftw& a, std::string flnm);


#endif // UTIL_H
