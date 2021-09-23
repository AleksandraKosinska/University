#include <iostream>
#include "zad4_c.hpp"
#include <unistd.h>

using namespace std;

int main()
{
    string wybor;
    cout << " '1' - bawic sie interaktywnie" << endl;
    cout << "            lub" << endl;
    cout << "'dowolny inny znak' -  uruchom gotowy test" << endl;
    cin >> wybor;
    if(wybor == "1")
    {
        int pojemnosc;
        cout << "jakiej pojemnosci ma byc stos?" << endl;
        cin >> pojemnosc;
        Stos stos(pojemnosc);
        int choice;
        string slowo;
        do
        {
            menu();
            cin >> choice;
            switch(choice)
            {
                case 0:
                    return 0;
                case 1:
                    cout <<"jakie slowo wlozyc na stos?" << endl;
                    cin >> slowo;
                    stos.wloz(slowo);
                    break;
                case 2:
                    cout <<"sciagniety element: " << stos.sciagnij() << endl;
                    break;
                case 3:
                    cout <<"element na gorze: " << stos.sprawdz() << endl;
                    break;
                case 4:
                    cout <<"ilosc elementow: " << stos.rozmiar() << endl;
                    break;
                case 5:
                    cout << "stos:" << endl;
                    stos.print();
                    break;
            }
            usleep(1500000);
        } while (choice != 0);
        
    }
    else
    {
        test();
    }
    return 0;
}