#include <iostream>

using namespace std;


class Wektor
{
    public:

    const double dx;
    const double dy;

    Wektor() = default;
    Wektor(double, double);
    Wektor(const Wektor&);
};
Wektor sklad (Wektor w1, Wektor w2);
class Punkt
{
    public:

    const double x;
    const double y;

    Punkt() = default;
    Punkt(double, double);
    Punkt(Punkt, Wektor);
    Punkt(const Punkt& p) = default;
    Punkt & operator=(const Punkt&) = delete;

};

class Prosta
{
    double a;
    double b;
    double c;

    public:
    Prosta(const Prosta&) = delete;
    Prosta & operator=(const Prosta&) = delete;
    Prosta(Punkt, Punkt);
    Prosta(Wektor);
    Prosta(double, double, double);
    Prosta(Prosta*, Wektor);
    void normalizacja();
    bool czy_prostopadly(Wektor);
    bool czy_rownolegly(Wektor);
    bool czy_lezy_na_prostej(Punkt);
    double daj_a();
    double daj_b();
    double daj_c();

};
bool czy_proste_rownolegle(Prosta* p1, Prosta* p2);
bool czy_proste_prostopadle(Prosta* p1, Prosta* p2);
Punkt punkt_przeciecia(Prosta* p1, Prosta* p2);