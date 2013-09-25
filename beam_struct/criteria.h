#ifndef CRITERIA_H
#define CRITERIA_H
#include "planewave_c.h"


class criteria
{
public:
    virtual ~criteria(){}
    virtual bool needEliminate(const PlaneWave_C& Pw)=0;
};

#endif // CRITERIA_H
