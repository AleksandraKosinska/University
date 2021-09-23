#include <iostream>
#include "nazwy.hpp"

using namespace std;


Element* nowa_tablica()
{
    Element* e = new Element;
    return e;

}

void dodaj(Element* e, int ind, int val)
{
    if(!e->index)
    {
        e->index = ind;
        e->value = val;
    }
    else
    {
        Element* pom = new Element;
        pom = e;
        int64_t licznik = pom->index;
        while(licznik < ind)
        {
            if(!pom->index)
            {
                pom->index = licznik;
            }
            if(pom->next == NULL)
            {
                Element* pom2 = new Element;
                pom -> next = pom2;
                pom2->prev=pom;
            }
            pom = pom -> next;
            licznik ++;
            
        }
        while(licznik > ind)
        {
            if(!pom->index)
            {
                pom->index = licznik;
            }
            if(pom->prev == NULL)
            {
                Element* pom2 = new Element;
                pom->prev = pom2;
                pom2->next = pom;
            }
            pom = pom -> prev;
            licznik --;
            
        }
        pom->index = ind;
        pom->value = val;

    }
}
void indeks(Element* e, int64_t ind)
{
    while(e->index < ind)
    {
        e = e->next;
        if(e == NULL)
        {
            throw invalid_argument("poza tablica");
        }
    }
    while(e->index > ind)
    {
        e = e->prev;
        if(e == NULL)
        {
            throw invalid_argument("poza tablica");
        }
    }
    cout << e->value << endl;
}
void wypis(Element* e)
{
    while(e->prev != NULL)
    {
        e = e->prev;
    }
    while(e != NULL)
    {
        cout << e->index << " " << e->value << endl;
        e = e->next;
    }
}