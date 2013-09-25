#ifndef CRITERIA_FOR_NONHOMOGENIOUS_H
#define CRITERIA_FOR_NONHOMOGENIOUS_H
#include "criteria.h"
#include "planewave_c.h"

class Criteria_For_Nonhomogenious:public criteria
{
public:
     Criteria_For_Nonhomogenious();
     ~Criteria_For_Nonhomogenious(){}
     bool needEliminate(const PlaneWave_C& Pw);
};

#endif // CRITERIA_FOR_NONHOMOGENIOUS_H
