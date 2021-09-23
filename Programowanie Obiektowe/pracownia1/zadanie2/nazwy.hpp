#ifndef nazwy_hpp
#define nazwy_hpp
#include <stdint.h>

using namespace std;

struct Ulamek
{
    int64_t mianownik;
    int64_t licznik;
};

int64_t NWD(int64_t a, int64_t b);
int64_t NWW(int64_t a, int64_t b);
Ulamek* nowy_ulamek(int64_t liczba1, int64_t liczba2);
Ulamek* dodaj(Ulamek* u1, Ulamek* u2);
Ulamek* odejmij(Ulamek* u1, Ulamek* u2);
Ulamek* razy(Ulamek* u1, Ulamek* u2);
Ulamek* przez(Ulamek* u1, Ulamek* u2);

void dodaj_2(Ulamek* u1, Ulamek* &u2);
void odejmij_2(Ulamek* u1, Ulamek* &u2);
void razy_2(Ulamek* u1, Ulamek* &u2);
void przez_2(Ulamek* u1, Ulamek* &u2);
void wypisz(Ulamek* u);

#endif
