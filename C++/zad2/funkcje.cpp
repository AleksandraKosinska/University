#include <iostream>
#include <cmath>
#include "klasy.h"

using namespace std;


Wektor::Wektor(double x, double y):
    dx(x),
    dy(y)
{   
};
Wektor::Wektor(const Wektor& w):
    dx(w.dx),
    dy(w.dy)
{
};

Wektor sklad (Wektor w1, Wektor w2)
{
    double wx = w1.dx + w2.dx;
    double wy = w1.dy + w2.dy;
    Wektor wynik(wx, wy);
    return wynik;
}

Punkt::Punkt(double sx, double sy):
    x(sx),
    y(sy)
{
};
Punkt::Punkt(Punkt p, Wektor w):
    x(p.x + w.dx),
    y(p.y + w.dy)
{
};

Prosta::Prosta(Punkt p1, Punkt p2)
{
    c = ((p2.y - p1.y)*p1.x) - ((p2.x - p1.x) * p1.y);
    a = -1 * (p2.y - p1.y);
    b = (p2.x - p1.x);
    normalizacja();
}
Prosta::Prosta(Wektor w)
{
    Punkt p1(0, 0);
    Punkt p(p1, w);
    a = w.dx;
    b = w.dy;
    c = -1 * (a * p.x) - (b * p.y);
    normalizacja();
}
Prosta::Prosta(double na, double nb, double nc)
{
    if(na == 0 && nb == 0)
    {
        throw invalid_argument("A i B sa rowne 0");
    }
    a = na;
    b = nb;
    c = nc;
    normalizacja();
}
Prosta::Prosta(Prosta* p, Wektor w)
{
    double y1 = ((-1 * p->a) * 1 - p->c) / p->b;
    double y2 = ((-1 * p->a) * 2 - p->c) / p->b;
    Prosta wynik(Punkt(1, y1), Punkt(2, y2));
    a = wynik.daj_a();
    b = wynik.daj_b();
    c = wynik.daj_c();
}
void Prosta::normalizacja()
{
    double czynnik;
    if(c <= 0)
    {
        czynnik = (1 / (sqrt(a*a + b*b)));
    }
    else
    {
        czynnik = (-1 / (sqrt(a*a + b*b)));
    }
    a = czynnik * a;
    b = czynnik * b;
    c = czynnik * c;
}
bool Prosta::czy_prostopadly(Wektor w)
{
    double kw = w.dx/w.dy;
    double ka = -1 * (a / b);
    return(kw * ka == (-1));
}
bool Prosta::czy_rownolegly(Wektor w)
{
    double ka = -1 * (a / b);
    double kw = w.dx/w.dy;
    return(ka == kw || ka == (-1 * kw));
}
bool Prosta::czy_lezy_na_prostej(Punkt p)
{
    double x = p.x;
    double sy = ((-1 * a) * x - c) / b;
    return (sy == p.y);
}
double Prosta::daj_a(){return a;}
double Prosta::daj_b(){return b;}
double Prosta::daj_c(){return c;}

bool czy_proste_rownolegle(Prosta *p1, Prosta *p2)
{
    double a1 = p1->daj_a();
    double b1 = p1->daj_b();
    double a2 = p2->daj_a();
    double b2 = p2->daj_b();
    return(a1 * b2 == a2 * b1);
}
bool czy_proste_prostopadle(Prosta *p1, Prosta *p2)
{
    double a1 = p1->daj_a();
    double b1 = p1->daj_b();
    double a2 = p2->daj_a();
    double b2 = p2->daj_b();
    return(a1 * a2 == (-1) * b1 * b2);
}
Punkt punkt_przeciecia(Prosta *p1, Prosta *p2)
{
    double a1 = p1->daj_a();
    double b1 = p1->daj_b();
    double c1 = p1->daj_c();
    double a2 = p2->daj_a();
    double b2 = p2->daj_b();
    double c2 = p2->daj_c();
    if(a1 * b2 == a2 * b1)
    {
        throw invalid_argument("proste rownolegle");
    }
    double w = a1 * b2 - a2 * b1;
    double wx = (-1) * c1 * b2 - (-1) * c2 * b1;
    double wy = a1  * (-1) * c2 - (-1) * c1 * a2;
    return Punkt(wx/w, wy/w);

}