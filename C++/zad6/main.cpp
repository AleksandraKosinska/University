#include <iostream>
#include "wyrazenia_arytmetyczne.hpp"

using namespace std;

int main()
{
    /*
    a) ((x-1)*x)/2
    b) (3+5)/(2+x*7)
    c) 2+x*7-(y*3+5) dla y=1
    d) cos((x+1)*x)/e^x^2
    */

    Wyrazenie *a = new Dziel(
        new Mnoz(
            new Odejmij(
                new Zmienna("x"),
                new Liczba(1)
            ),
            new Zmienna("x")
        ),
        new Liczba(2)
    );


    Wyrazenie *b = new Dziel(
        new Dodaj(
            new Liczba(3),
            new Liczba(5)
        ),
        new Dodaj(
            new Liczba(2),
            new Mnoz(
                new Zmienna("x"),
                new Liczba(7)
            )
        )
    );

    Wyrazenie *c = new Odejmij(
        new Dodaj(
            new Liczba(2),
            new Mnoz(
                new Zmienna("x"),
                new Liczba(7)
            )
        ),
        new Dodaj(
            new Mnoz(
                new Zmienna("y", 1),
                new Liczba(3)
            ),
            new Liczba(5)
        )
    );

    Wyrazenie *d = new Dziel(
        new Cos(
            new Mnoz(
                new Dodaj(
                    new Zmienna("x"),
                    new Liczba(1)
                ),
                new Zmienna("x")
            )
        ),
            new Potega(
                new E(),
                new Potega(
                    new Zmienna("x"),
                    new Liczba(2)
                )
            )
    );

    for (double i = 0; i < 1; i+=0.01)
    {
        a->set_value("x", i);
        cout<< a->opis()<< " = " << a->oblicz()<<endl;
        cout<< b->opis()<< " = " << b->oblicz()<<endl;
        cout<< c->opis()<< " = " << c->oblicz()<<endl;
        cout<< d->opis()<< " = " << d->oblicz()<<endl;
    }

    delete a, b, c, d;

    return 0;
}