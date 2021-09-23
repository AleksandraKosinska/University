#include <iostream>
#include "tabbit.hpp"

using namespace std;

int main()
{
    cout << "prezentacja: " << endl;
    cout << "tablica 46-bitowa (zainicjalizowana zerami): "<< endl;
    tab_bit t(46);
    cout << t << endl;
    cout << "tablica po ustawieniu 45-tego, 23-iego i 0-ego bitu na true: " << endl;
    t[45] = true;
    t[23] = true;
    t[0] = true;
    cout << t << endl;
    cout << "tablica skopiowana z poprzedniej tablicy: " << endl;
    tab_bit v(t);
    cout << v << endl;
    cout << "odczytanie  23-iego bitu w tablicy: " << endl;
    cout << v[23] << endl;
    cout << "tablica 64-bitowa (sizeof(uint64_t)*8) o wartosci 1099511595008: " << endl;
    tab_bit u(1099511595008ull);
    cout << u << endl;
    cout << "odczytanie bitu 1-ego do zmiennej typu bool: " << endl;
    bool b = u[1];
    cout << b << endl;
    cout << "przepisanie bitu 1-ego do bitow 63-ego, 33-ego i 20-ego: " << endl;
    u[63] = u[33] = u[20] = u[1];
    cout << u << endl;
    cout << "tablica pierwsza | tablica druga: " << endl;
    tab_bit r = t | u;
    cout << r << endl;
    cout << "zanegowane: " << endl;
    cout << ~r << endl;
}