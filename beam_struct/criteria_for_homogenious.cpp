#include "criteria_for_homogenious.h"
#include "cmath"


Criteria_For_Homogenious::Criteria_For_Homogenious()
{
}

bool Criteria_For_Homogenious::needEliminate(const PlaneWave_C& Pw)
{
    if (std::abs(std::imag(Pw.slow(3))) > 1e-7 ) return true;
    return false;
}
