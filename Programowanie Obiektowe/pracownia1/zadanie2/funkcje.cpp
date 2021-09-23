#include <iostream>
#include <stdexcept>
#include "nazwy.hpp"

using namespace std;

int64_t NWD(int64_t a, int64_t b)
{
    int pom;
	while(b!=0)
    {
		pom = b;
		b = a%b;
		a = pom;	
	}
    if(a < 0) a *= -1;
    return a;
}
int64_t NWW(int64_t a, int64_t b)
{
    return (a*b)/NWD(a,b);
}

Ulamek* nowy_ulamek(int64_t liczba1, int64_t liczba2)
{
    if(liczba2 == 0)
    {
        throw invalid_argument("dzielenie przez 0");
    }
    int64_t nwd = NWD(liczba1, liczba2);
    Ulamek* wynik = new Ulamek;
    if(liczba2 < 0)
    {
        liczba1 *= -1;
        liczba2 *= -1;
    }
    wynik->licznik = liczba1 / nwd;
    wynik->mianownik = liczba2 / nwd;
    return wynik;
}

Ulamek* dodaj(Ulamek* u1, Ulamek* u2)
{
    int64_t nww = NWW(u1->mianownik, u2->mianownik);
    int64_t liczba2 = nww;
    int64_t liczba1 = (u1->licznik * (nww / u1->mianownik)) + (u2->licznik * (nww / u2->mianownik));
    Ulamek* wynik = new Ulamek;
    wynik = nowy_ulamek(liczba1, liczba2);
    return wynik;
}
Ulamek* odejmij(Ulamek* u1, Ulamek* u2)
{
    int64_t nww = NWW(u1->mianownik, u2->mianownik);
    int64_t liczba2 = nww;
    int64_t liczba1 = (u1->licznik * (nww / u1->mianownik)) - (u2->licznik * (nww / u2->mianownik));
    Ulamek* wynik = new Ulamek;
    wynik = nowy_ulamek(liczba1, liczba2);
    return wynik;
}
Ulamek* razy(Ulamek* u1, Ulamek* u2)
{
    Ulamek* wynik = new Ulamek;
    wynik = nowy_ulamek(u1->licznik * u2->licznik, u1->mianownik * u2->mianownik);
    return wynik;
}
Ulamek* przez(Ulamek* u1, Ulamek* u2)
{
    if(u2->mianownik == 0)
    {
        throw invalid_argument("dzielenie przez 0");
    }
    Ulamek* wynik = new Ulamek;
    wynik = nowy_ulamek(u1->licznik * u2->mianownik, u1->mianownik * u2->licznik);
    return wynik;
}


void dodaj_2(Ulamek* u1, Ulamek* &u2)
{
    int64_t nww = NWW(u1->mianownik, u2->mianownik);
    int64_t liczba2 = nww;
    int64_t liczba1 = (u1->licznik * (nww / u1->mianownik)) + (u2->licznik * (nww / u2->mianownik));
    delete u2;
    u2 = nowy_ulamek(liczba1, liczba2);
}
void odejmij_2(Ulamek* u1, Ulamek* &u2)
{
    int64_t nww = NWW(u1->mianownik, u2->mianownik);
    int64_t liczba2 = nww;
    int64_t liczba1 = (u1->licznik * (nww / u1->mianownik)) - (u2->licznik * (nww / u2->mianownik));
    u2 = nowy_ulamek(liczba1, liczba2);
}
void razy_2(Ulamek* u1, Ulamek* &u2)
{
    u2 = nowy_ulamek(u1->licznik * u2->licznik, u1->mianownik * u2->mianownik);
}
void przez_2(Ulamek* u1, Ulamek* &u2)
{
    if(u2->mianownik == 0)
    {
        throw invalid_argument("dzielenie przez 0");
    }
    u2 = nowy_ulamek(u1->licznik * u2->mianownik, u1->mianownik * u2->licznik);
}
void wypisz(Ulamek* u)
{
    cout << u->licznik << " / " << u->mianownik << endl;
}