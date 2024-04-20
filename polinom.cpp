#include "polinom.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

//alapmuveletek

//alapertelmezett konstruktor, azaz a letrehozas
Polynomial::Polynomial(vector<double> coeffs) : coefficients(coeffs) {}

//ures konstruktor
Polynomial::Polynomial() {}

//a peldahoz hasonloan en is definialtam a << es >> muveleteket polinomra a strukturan kivul
//az egyszerubb kiiratas es beolvasas kedveert
ostream& operator<<(ostream& os, const Polynomial& poly) 
{
    bool isFirstTerm = true;

    for (int i = poly.coefficients.size() - 1; i >= 0; --i) {
        // ellenorizzuk, hogy nem nulla
        if (poly.coefficients[i] != 0) 
        {
            //csak akkor irja ki ha nem nulla a legelso tag
            if (!isFirstTerm) 
            {
                os << " + ";
            } else 
            {
                isFirstTerm = false;
            }

            // irja ki ha a szamot ha nem 1 
            if (i == 0 || poly.coefficients[i] != 1) 
            {
                os << poly.coefficients[i];
            }

            // irja ki ha nem 0
            if (i > 0) {
                os << "x";
                if (i > 1) {
                    os << "^" << i;
                }
            }
        }
    }
    return os;
}

//ez azert kell, hogy elleorizzuk, hogy szam-e a megadott bemenet mert ha nem akkor nem ertelmezett

istream& operator>>( istream& is, Polynomial& poly) {
    poly.coefficients.clear(); //eddigi egyutthatokat torolje ki
    
    int degree;
    string input;

    //olvassa be
    cout << "Add meg a polinom fokszamat: ";
    while (!(is >> degree)) {
        //ha nem szamot adtunk meg adjon hibauzenetet
        cout << "Ervenytelen bemenet, kerjuk adjon meg egy szamot: ";
        is.clear(); 
        is.ignore( numeric_limits< streamsize>::max()); // ervenytelen bemenetetet dobja ki
    }

    //a fokszamnak megfelelo vektort hoz letre tarolasra
    poly.coefficients.resize(degree + 1);

    // egyutthatok
    for (int i = degree; i >= 0; --i) {
        cout << "Add meg az x^" << i << " egyutthatojat: ";
        while (!(is >> poly.coefficients[i])) {
            //ervenytelen bemenet ha nem szam
            cout << "Ervenytelen bemenet, kerjuk adjon meg egy szamot: ";
            is.clear(); 
            is.ignore( numeric_limits< streamsize>::max()); 
        }
    }

    return is;
}


//matematikai muveletek

//osszeg
Polynomial Polynomial::operator+(const Polynomial& other) const 
{
    Polynomial result; //ot fogom visszateriteni
    //meret
    size_t maxSize = max(coefficients.size(), other.coefficients.size());
    result.coefficients.resize(maxSize);

    //osszeadjuk a megfelelo egyutthatokat
    for (size_t i = 0; i < maxSize; i++) 
    {
        double coeff1 = (i < coefficients.size()) ? coefficients[i] : 0.0;
        double coeff2 = (i < other.coefficients.size()) ? other.coefficients[i] : 0.0;
        result.coefficients[i] = coeff1 + coeff2;
    }

    return result;
}

//kulonbseg
Polynomial Polynomial::operator-(const Polynomial& other) const 
{
    //a legnagyobb fokszamot keresem a ket polinomban
    int maxDegree = max(coefficients.size(), other.coefficients.size());

    //vektor az egyutthatoknak
    vector<double> resultCoefficients(maxDegree, 0.0);

    //megfelelo tagokat vonjuk ki egymasbol
    for (size_t i = 0; i < coefficients.size(); i++) 
    {
        resultCoefficients[i] += coefficients[i];
    }
    for (size_t i = 0; i < other.coefficients.size(); i++) 
    {
        resultCoefficients[i] -= other.coefficients[i];
    }

    return Polynomial(resultCoefficients);
}

//szorzat
Polynomial Polynomial::operator*(const Polynomial& other) const 
{
    //az eredmeny polinom fokszamait szamoljuk ki
    int degree = coefficients.size() + other.coefficients.size() - 2;

    //vektor a fokszamok tarolasara
    vector<double> resultCoefficients(degree + 1, 0.0);

    //szorozzuk a matematikai muveleteknek megfeleloen
    for (size_t i = 0; i < coefficients.size(); i++) 
    {
        for (size_t j = 0; j < other.coefficients.size(); ++j) 
        {
            resultCoefficients[i + j] += coefficients[i] * other.coefficients[j];
        }
    }

    return Polynomial(resultCoefficients);
}

//derivalt
Polynomial Polynomial::deriv() const 
{
    if (coefficients.empty() || coefficients.size() == 1) 
    {
        //a derivalt nulla ha csak konstans tag van vagy nulla 
        return Polynomial({0.0});
    }

    vector<double> derivativeCoefficients(coefficients.size() - 1);

    for (size_t i = 1; i < coefficients.size(); i++) 
    {
        //x kovetkezo hatvanyaval szorzom meg
        derivativeCoefficients[i - 1] = coefficients[i] * i;
    }

    return Polynomial(derivativeCoefficients);
}

//integral
//csak akkor ertelmezett ha nincs benne nullaval valo osztas

Polynomial Polynomial::integral() const 
{
    //ha ures
    if (coefficients.empty()) 
    {
        //nullat terit vissza
        return Polynomial({0.0});
    }

    vector<double> integralCoefficients(coefficients.size() + 1);

    for (size_t i = 0; i < coefficients.size(); i++) 
    {
        //ellenorzi hogy 0-hoz ertunk-e
        if (i == 0) 
        {
            //ha igen akkor legyen az erteke a konstanssal
            integralCoefficients[i + 1] = coefficients[i];
        } 
        else 
        {
            //ha nem ertuk el meg odaig, akkor ossza el x hatvanykitevojevel, ez ellenorizze kozben, hogy nem 0
            if (i != 0) 
            {
                integralCoefficients[i + 1] = coefficients[i] / (i + 1);
            } 
            else 
            {
                //ha 0 akkor kezelje megfeleloen
                integralCoefficients[i + 1] = 0.0;
            }
        }
    }

    return Polynomial(integralCoefficients);
}
