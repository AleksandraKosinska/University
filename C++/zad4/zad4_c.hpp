#ifndef zad4_c_hpp
#define zad4_c_hpp

#include <iostream>

using namespace std;

class Stos
{
    int pojemnosc;
    int ile;
    string *tab;
    public :
    ~Stos();
    Stos();
    Stos(int);
    Stos(initializer_list<string>);
    Stos(const Stos&);
    Stos(Stos&&);
    void wloz(string);
    string sciagnij();
    string sprawdz();
    int rozmiar();
    Stos odwroc();
    void print();
};

void menu();
void test();

#endif