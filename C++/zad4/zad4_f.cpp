#include <iostream>
#include "zad4_c.hpp"

using namespace std;

Stos::~Stos()
{
    delete[] tab;
}

Stos::Stos():
    pojemnosc(1),
    ile(0),
    tab(new string[1])
{
}

Stos::Stos(int p):
    pojemnosc((p < 1 || 100 < p)? : p),
    ile((p < 1 || 100 < p)? : 0),
    tab((p < 1 || 100 < p) ? new string[0] : new string[pojemnosc])
{
    if(p < 1 || 100 < p)
    {
        throw invalid_argument("the given 'pojemnosc' is out of range");
    }
}

Stos::Stos(initializer_list<string> lista):
    pojemnosc(lista.size()),
    ile(pojemnosc),
    tab(new string[pojemnosc])
{
    if(lista.size() > 100)
    {
        throw invalid_argument("the given 'pojemnosc' is out of range");
    }
    else
    {
        for(int i = 0; i < pojemnosc; i++)
        {
            tab[i] = *(lista.begin() + i);
        }
    }
    
}

Stos::Stos(const Stos& s):
    pojemnosc(s.pojemnosc),
    ile(s.ile),
    tab(new string[pojemnosc])
{
    for(int i = 0; i < pojemnosc; i++)
    {
        tab[i] = s.tab[i];
    }
}

Stos::Stos(Stos&& s):
    pojemnosc(s.pojemnosc),
    ile(s.ile),
    tab(s.tab)

{
}

void Stos::wloz(string napis)
{
    if(pojemnosc == ile)
    {
        cerr << "Stos is full" << endl;
    }
    else
    {
        tab[ile] = napis;
        ile ++;
    }
    
}

string Stos::sciagnij()
{
    if(ile == 0)
    {
        cerr << "Stos is empty" << endl;
        return "";
    }
    else
    {
        ile --;
        string wynik = tab[ile];
        tab[ile] = "";
        return wynik;
    }
    
}

string Stos::sprawdz()
{
    if(ile == 0)
    {
        cerr << "Stos is empty" << endl;
        return "";
    }
    else
    {
        return tab[ile - 1];
    }
    
}

int Stos::rozmiar()
{
    return ile;
}

Stos Stos::odwroc()
{
    Stos wynik(pojemnosc);
    for(int i = pojemnosc - 1; i >= 0; i--)
    {
        wynik.wloz(tab[i]);
    }
    return wynik;
}

void Stos::print()
{
    for(int i = pojemnosc - 1; i >= 0; i--)
    {
        cout << tab[i] << "   ";
    }
    cout << endl;
}

void menu()
{
    cout << "0. ZAKONCZ PROGRAM" << endl;
    cout << "1. wloz element" << endl;
    cout << "2. sciagnij element" << endl;
    cout << "3. sprawdz co jest na gorze" << endl;
    cout << "4. podaj ile jest elementow w stosie" << endl;
    cout << "5. wypisz stos" << endl;
}

void test()
{
    Stos stos({"ala", "ma", "kota", "a", "kot", "ma", "ale"});
    cout << "stos utworzony z listy stringow:" << endl;
    stos.print();
    cout << endl;
    cout << "ilosc elementow na stosie:  " << stos.rozmiar() << endl;
    cout << endl;
    cout << "stos po zdjeciu slowa z gory:" << endl;
    stos.sciagnij();
    stos.print();
    cout << endl;
    cout << "stos po doaniu slowa 'surykatka':" << endl;
    stos.wloz("surykatka");
    stos.print();
    cout << endl;
    cout << "podejrzenie slowa na gorze stosu:  " << stos.sprawdz() << endl;
    cout << endl;
    cout << "utworzenie stosu odwrotnego:" << endl;
    Stos stos2 = stos.odwroc();
    stos2.print();
    cout << endl;
    cout << "stos utworzony po skopiowaniu stosu pierwszego: " << endl;
    Stos stos3(stos);
    stos3.print();
}