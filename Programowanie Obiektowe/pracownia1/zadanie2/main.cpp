#include <iostream>
#include <stdexcept>
#include "nazwy.hpp"

using namespace std;

int main()
{
    Ulamek* u1;
    Ulamek* u2;
    Ulamek* u;
    u1 = nowy_ulamek(2, 100);
    u2 = nowy_ulamek(1, 3);
    u = przez(u1, u2);
    wypisz(u1);
    wypisz(u2);
    wypisz(u);
    przez_2(u1, u2);
    wypisz(u2);
    
    delete u1, u2, u;
    return 0;
}