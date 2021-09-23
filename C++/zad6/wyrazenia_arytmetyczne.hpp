#ifndef wyrazenia_arytmetyczne_hpp
#define wyrazenia_arytmetyczne_hpp

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


class Wyrazenie
{
    public:
    virtual ~Wyrazenie() {};
    virtual double oblicz() = 0;
    virtual string opis() = 0;
    void set_value(string, double);
};

class Liczba : public Wyrazenie
{
    double value;

    public:
    Liczba(double val);
    double oblicz();
    string opis();
};

class Pi : public Liczba
{
    public:
    Pi();
};

class E : public Liczba
{
    public:
    E();
};

class Fi : public Liczba
{
    public:
    Fi();
};

class Zmienna : public Wyrazenie
{
    string nazwa;
    static vector<pair<string, double>> tab_zmiennych;
    static double velue;
    
    public:
    Zmienna(string n);
    Zmienna(string n, double val);
    double oblicz();
    string opis();
    static double value(string n);
};

class Operator2arg : public Wyrazenie
{
    protected:
    Wyrazenie *w1;
    Wyrazenie *w2;
    public:
    ~Operator2arg();
    Operator2arg(Wyrazenie *x, Wyrazenie *y);
};


class Dodaj : public Operator2arg
{
    public:
    Dodaj(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Odejmij : public Operator2arg
{
    public:
    Odejmij(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Mnoz : public Operator2arg
{
    public:
    Mnoz(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Dziel : public Operator2arg
{
    public:
    Dziel(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Logarytm : public Operator2arg
{
    public:
    Logarytm(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Modulo : public Operator2arg
{
    public:
    Modulo(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Potega : public Operator2arg
{
    public:
    Potega(Wyrazenie *x, Wyrazenie *y) : Operator2arg(x, y) {};
    double oblicz() override;
    string opis() override;
};

class Operator1arg : public Wyrazenie
{
    protected:
    Wyrazenie *w;
    public:
    ~Operator1arg();
    Operator1arg(Wyrazenie *x);
};

class Sin : public Operator1arg
{
    public:
    Sin(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

class Cos : public Operator1arg
{
    public:
    Cos(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

class Exp : public Operator1arg
{
    public:
    Exp(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

class Ln : public Operator1arg
{
    public:
    Ln(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

class Bezwzgl : public Operator1arg
{
    public:
    Bezwzgl(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

class Odwrot : public Operator1arg
{
    public:
    Odwrot(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

class Przeciw : public Operator1arg
{
    public:
    Przeciw(Wyrazenie *x) : Operator1arg(x){};
    double oblicz() override;
    string opis() override;
};

#endif