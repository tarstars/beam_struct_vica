#ifndef CRITERIA_FOR_HOMOGENIOUS_H
#define CRITERIA_FOR_HOMOGENIOUS_H
#include "criteria.h"
#include "planewave_c.h"

class Criteria_For_Homogenious: public criteria
{
public:
    Criteria_For_Homogenious();
    ~Criteria_For_Homogenious(){}
    bool needEliminate(const PlaneWave_C& Pw);
};

#endif // CRITERIA_FOR_HOMOGENIOUS_H
