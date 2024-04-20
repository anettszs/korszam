#include <iostream>
#include "polinom.h"
#include "polinom.cpp"

using namespace std;

int main() 
{
    //letrehozom az objektumokat
    Polynomial p1, p2;
    cout << "Elso polinom:\n";
    cin>>p1;

    cout << "Masodik polinom:\n";
    cin>>p2;

    //kiprobalom az ossze muveletet amit ertelmeztem rajta

    cout<<endl<<"A billentyuzetrol beolvasott elso polinom:"<<endl<<p1<<endl;
    cout<<"A billentyuzetrol beolvasott masodik polinom:"<<endl<<p2<<endl;
    cout<<endl<<"Kiprobaljuk a definialt muveleteket."<<endl<<endl;
    cout<< "Osszeg:"<<endl<<p1+p2<<endl<<endl;
    cout<<"Kulonbseg:"<<endl<<p1-p2<<endl<<endl;
    cout<<"Szorzat:"<<endl<<p1*p2<<endl<<endl;
    cout<<"Az elso polinom derivaltja:"<<endl<<p1.deriv()<<endl;
    cout<<"A masodik polinom derivaltja:"<<endl<<p2.deriv()<<endl;
    cout<<endl<<"Az elso polinom integralja:"<<endl<<p1.integral()<<endl;
    cout<<"A masodik polinom integralja:"<<endl<<p2.integral()<<endl;
    return 0;
}
