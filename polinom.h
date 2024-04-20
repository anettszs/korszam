#ifndef POLINOM_H
#define POLINOM_H

#include <iostream>
#include <vector>

using namespace std;


struct Polynomial 
{
    vector<double> coefficients;

    //konstruktorok inicializalasa
    Polynomial(vector<double> coeffs);
    Polynomial();

    //osszeg
    Polynomial operator+(const Polynomial& other) const;
    //kulonbseg
    Polynomial operator-(const Polynomial& other) const;
    //szorzat
    Polynomial operator*(const Polynomial& other) const;
    //dervialt
    Polynomial deriv() const;
    //integral
    Polynomial integral() const;

};

// a pelda feladathoz hasonloan en is deifinialtam a kiiratas es beolvasas operatorokat
ostream& operator<<(ostream& os, const Polynomial& poly);
istream& operator>>(istream& is, Polynomial& poly);

#endif /* POLYNOMIAL_H */