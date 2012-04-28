#ifndef POLINOM_H
#define POLINOM_H
#include "types.h"

#include <vector> // несколько чисел из бибиотетки стандартных шаблонов

class RetVal{
public:
    CD val, vald, valdd;
    RetVal(const CD& xval, const CD& xvald, const CD& xvaldd): val(xval), vald(xvald), valdd(xvaldd){}
};
std::ostream& operator<<(std::ostream&, const RetVal& r);



class Polinom
{
    std::vector<CD> dat;
public:
    Polinom();
    Polinom(const CD& a0);
    Polinom(const CD& a0, const CD&a1);
    Polinom(const CD& a0, const CD&a1, const CD& a2);
    Polinom(const CD& a0, const CD&a1, const CD& a2, const CD& a3);
    Polinom(const CD& a0, const CD&a1, const CD& a2, const CD& a3, const CD& a4);

    static Polinom byDegree(int n){Polinom ret; ret.dat.resize(n+1); return ret;}
    Polinom operator *(const Polinom& a)const;
    Polinom operator +(const Polinom& a)const;
    Polinom operator -(const Polinom& a)const;
    RetVal count (const CD& x)const;
    std::vector<CD> all_roots()const;
    CD root() const;
    int deg() const;
    Polinom bez_u(const CD&) const;
      std::ostream& operator>>/*выводим направо*/(std::ostream& os)const/*когда выводим обьект не меняем*/;
};
std::ostream& operator<<(std::ostream& os, const Polinom& r);
#endif // POLINOM_H
