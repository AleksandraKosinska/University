#include <iostream>
#include "lista_n.hpp"

using namespace std;

int main()
{
    cout << "prezentacja: " << endl;
    List<int> lista;
    lista.push_back(1);
    lista.push_back(6);
    lista.push_back(3);
    lista.push_back(9);
    lista.push_back(8);
    lista.push_back(3);
    lista.push_back(2);
    lista.push_back(0);
    cout << "lista 1, 6, 3, 9, 8, 3, 2, 0: " << endl;
    lista.print();
    cout << "rozmiar listy: " << lista.length() << endl;
    lista.pop_back();
    lista.pop_back();
    cout << "rozmiar listy po usunieciu 2 elementow: " << lista.length() << endl;
    cout << "lista po usunieciu elementu o wartosci 6: " << endl;
    lista.remove(6);
    lista.print();
    cout << "sprawdzenie czy lista jest posortowana: " << check(lista) << endl;
    cout << "lista po posortowaniu: " << endl;
    sort(lista);
    lista.print();
    return 0;
}