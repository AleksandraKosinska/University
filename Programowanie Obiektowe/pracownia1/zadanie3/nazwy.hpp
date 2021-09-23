#ifndef nazwy_hpp
#define nazwy_hpp
#include <stdint.h>


struct Element
{
    Element *next = nullptr;
    Element *prev = nullptr;
    int index;
    int value;
};


Element* nowa_tablica();
void dodaj(Element* e, int ind, int val);
void indeks(Element* e, int64_t ind);
void wypis(Element* e);

#endif