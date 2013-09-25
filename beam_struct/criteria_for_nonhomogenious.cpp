#include "criteria_for_nonhomogenious.h"
#include "planewave.h"
#include "cmath"

Criteria_For_Nonhomogenious::Criteria_For_Nonhomogenious()
{
}

bool Criteria_For_Nonhomogenious::needEliminate(const PlaneWave_C& Pw)
{
    if (std::abs(std::imag(Pw.slow(3))) < 1e-7 ) return true;
    return false;
}
