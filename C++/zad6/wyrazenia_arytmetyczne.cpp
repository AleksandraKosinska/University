#include <iostream>
#include "wyrazenia_arytmetyczne.hpp"

using namespace std;


//----------------------------------------------

void Wyrazenie::set_value(string nazwa, double val)
{
    Zmienna(nazwa, val);
}

//----------------------------------------------

Liczba::Liczba(double val)
    :value(val)
{
}

double Liczba::oblicz()
{
    return value;
}

string Liczba::opis()
{
    return to_string(value);
}

//----------------------------------------------

Pi::Pi()
    :Liczba(M_PI)
{
}

//----------------------------------------------

E::E()
    :Liczba(M_E)
{
}

//----------------------------------------------

Fi::Fi()
    :Liczba((1 + sqrt(5)) / 2)
{
}

//----------------------------------------------

vector<pair<string, double>> Zmienna::tab_zmiennych;

Zmienna::Zmienna(string n)
    :nazwa(n)
{
}

Zmienna::Zmienna(string n, double value)
    :nazwa(n)
{
    bool change = 0;
    for(int i = 0; i < tab_zmiennych.size(); i++)
    {
        if(tab_zmiennych[i].first == n)
        {
            tab_zmiennych[i].second = value;
            change = 1;
        }
    }
    if(change == 0)
    {
        tab_zmiennych.push_back(pair<string, double>(n, value));
    }
}

double Zmienna::value(string n)
{
    for(int i = 0; i < tab_zmiennych.size(); i++)
    {
        if(tab_zmiennych[i].first == n)
        {
            return tab_zmiennych[i].second;
        }
    }
    throw invalid_argument("zmienna nie ma przypisanej wartosci");
}

double Zmienna::oblicz()
{
    return value(nazwa);
}

string Zmienna::opis()
{
    return nazwa;
}

//-----------------------------------------------

Operator2arg::~Operator2arg()
{
    delete w1;
    delete w2;
}

Operator2arg::Operator2arg(Wyrazenie *x, Wyrazenie *y)
    :w1(x), w2(y)
{
}

//-----------------------------------------------

double Dodaj::oblicz()
{
    return w1->oblicz() + w2->oblicz();
}

string Dodaj::opis()
{
    return "(" + w1->opis() + " + " + w2->opis() + ")";
}

//-----------------------------------------------

double Odejmij::oblicz()
{
    return w1->oblicz() - w2->oblicz();
}

string Odejmij::opis()
{
    return "(" + w1->opis() + " - " + w2->opis() + ")";
}

//------------------------------------------------

double Mnoz::oblicz()
{
    return w1->oblicz() * w2->oblicz();
}

string Mnoz::opis()
{
    return "(" + w1->opis() + " * " + w2->opis() + ")";
}

//------------------------------------------------

double Dziel::oblicz()
{
    if(w2->oblicz() != 0)
    {
        return w1->oblicz() / w2->oblicz();
    }
    else
    {
        throw invalid_argument("dzielenie przez 0");
    }
}

string Dziel::opis()
{
    return "(" + w1->opis() + " / " + w2->opis() + ")";
}

//------------------------------------------------

double Logarytm::oblicz()
{
    return (log(w2->oblicz()) / log(w2->oblicz()));
}

string Logarytm::opis()
{
    return "(log(" + w1->opis() + ") " + w2->opis() + ")";
}

//------------------------------------------------

double Modulo::oblicz()
{
    int a = w1->oblicz();
    int b = w2->oblicz(); 
    if(a == w1->oblicz() && b == w2->oblicz())
    {
        return a%b;
    }
    else 
    {
        throw invalid_argument("podane liczby nie są całkowite");
    }
}

string Modulo::opis()
{
    return "(" + w1->opis() + "%" + w2->opis() + ")";
}

//------------------------------------------------

double Potega::oblicz()
{
    return (pow(w1->oblicz(), w2->oblicz()));
}

string Potega::opis()
{
    return "(" + w1->opis() + "^" + w2->opis() + ")";
}

//------------------------------------------------

Operator1arg::~Operator1arg()
{
    delete w;
}

Operator1arg::Operator1arg(Wyrazenie *x)
    :w(x)
{
}

//------------------------------------------------

double Sin::oblicz()
{
    return sin(w->oblicz());
}

string Sin::opis()
{
    return "(sin" + w->opis() + ")";
}

//------------------------------------------------

double Cos::oblicz()
{
    return cos(w->oblicz());
}

string Cos::opis()
{
    return "(cos" + w->opis() + ")";
}

//------------------------------------------------

double Exp::oblicz()
{
    return exp(w->oblicz());
}

string Exp::opis()
{
    return "(exp" + w->opis() + ")";
}

//------------------------------------------------

double Ln::oblicz()
{
    return log(w->oblicz());
}

string Ln::opis()
{
    return "(ln" + w->opis() + ")";
}

//------------------------------------------------

double Bezwzgl::oblicz()
{
    return abs(w->oblicz());
}

string Bezwzgl::opis()
{
    return "|" + w->opis() + "|";
}

//------------------------------------------------

double Przeciw::oblicz()
{
    return -1*(w->oblicz());
}

string Przeciw::opis()
{
    return "(-" + w->opis() + ")";
}

//------------------------------------------------

double Odwrot::oblicz()
{
    return 1/(w->oblicz());
}

string Odwrot::opis()
{
    return "(1/" + w->opis() + ")";
}

//------------------------------------------------