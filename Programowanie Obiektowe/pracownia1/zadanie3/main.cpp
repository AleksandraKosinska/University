#include <iostream>
#include "nazwy.hpp"

using namespace std;


int main()
{
    Element* e;
    e = nowa_tablica();
    dodaj(e, 10, 6);
    dodaj(e, 13, 3);
    dodaj(e, 7, 14);
    dodaj(e, 9, 13);
    //wypis(e);
    indeks(e, 10);
    delete e;
    return 0;
}