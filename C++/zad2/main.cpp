#include <iostream>
#include "klasy.h"

using namespace std;

int main()
{
    Wektor w1(1, 3);
    Wektor w2(2, 5);
    Wektor w3 = sklad(w1, w2);
    cout << "wektor [1, 3] po zlozeniu z wektorem [2, 5]:    [" << w1.dx << ", " << w2.dy << "]" << endl;

    Punkt p1(6, 2);
    Punkt p2(p1, w1);
    cout << "punkt utworzony po przesunieciu punktu (6,2) o wektor [1,3]:   (" << p2.x << ", " << p2.y <<")" << endl;

    Prosta pr1(p1, p2);
    cout << "prosta przechodzaca przez punkty: (6, 2) i (7, 5):  " << pr1.daj_a() << "x + " << pr1.daj_b() <<"y + " << pr1.daj_c() << " = 0" << endl;

    Prosta pr2(Punkt(9,3), Punkt(4,7));

    cout << czy_proste_rownolegle(&pr1, &pr2) << endl;
    cout << czy_proste_prostopadle(&pr2, &pr1) << endl;

    pr1.czy_prostopadly(w1);

    return 0;
}