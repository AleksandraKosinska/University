#include <iostream>
#include "zad3_c.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        clog << "no elements to convert" << endl;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            decimal_to_roman(argv[i]);
        }
    }
    return 0;
}