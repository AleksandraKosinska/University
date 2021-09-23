#include <iostream>
#include "zad3_c.hpp"

using namespace std;

string int_to_roman(int number)
{
    const vector<pair<int, string>> rzym = 
    {
        {1000, "M"},
        {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
        {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string roman = "";
    for(int i = 0; i < rzym.size(); i++)
    {
        while(number >= rzym[i].first)
        {
            roman += rzym[i].second;
            number -= rzym[i].first;
        }
    }
    return roman;
}

bool is_number(string number)
{
    for(int i = 0; i < number.size(); i++)
    {
        if(!isdigit(number[i]))
        {
            return false;
        }
    }
    return true;
}

bool wrong_range(string decimal)
{
    if(decimal.size() > 4)
    {
        return true;
    }
    int number = stoi(decimal);
    return (number < 1 || 3999 < number);
}

void decimal_to_roman(string decimal)
{
    if(is_number(decimal))
    {
        if(wrong_range(decimal))
        {
            clog << "number out of range [1, 3999]" << endl;
        }
        else
        {
            int number = stoi(decimal);
            cout << decimal << ":   ";
            cout << int_to_roman(number) << endl;
        }
    }
    else
    {
        clog << "not a number" << endl;
    }
}
