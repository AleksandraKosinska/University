#include <iostream>
#include "tabbit.hpp"

using namespace std;

int sufit(int liczba1, int liczba2)
{
    return ceil((float) liczba1/ (float) liczba2);
}
int podloga(int liczba1, int liczba2)
{
    return floor((float) liczba1/ (float) liczba2);
}
uint64_t potega(int liczba, int p)
{
    uint64_t wynik = 1;
    for(int i = 0; i < p; i++)
    {
        wynik *= liczba;
    }
    return wynik;
}

string dec_to_bin(uint64_t liczba)
{
    string wynik = "";
    int i = 0;
    if(liczba == 0)
    {
        wynik += "0";
    }
    while (liczba > 0) 
    {
        wynik = to_string(liczba % 2) + wynik;
        liczba = liczba / 2;
        i++;
    }
    return wynik;
}

int64_t bin_to_dec(string napis)
{
    uint64_t wynik = 0;
    int p = 0;
    for(int i = napis.size() - 1; i >= 0; i --)
    {
        int bit = (int) napis[i] - 48;
        wynik += bit * potega(2, p);
        p++;
    }
    return wynik;
}

tab_bit::~tab_bit()
{
    delete[] tab;
}

istream & operator >> (istream &we, tab_bit &tb)
{
    string liczba;
    we >> liczba;
    if(liczba.size() > tb.dl)
    {
        throw invalid_argument("the number of given bits is higher than tab_bit");
    }
    int index = sufit(tb.dl, tb.rozmiarSlowa) - 1;
    for(int i = liczba.size(); i >= 0; i = i - tb.rozmiarSlowa)
    {
        string pomoc = liczba.substr(max(0, i - tb.rozmiarSlowa), i);
        tb.tab[index] = bin_to_dec(pomoc);
        index --;
    }

}
ostream & operator << (ostream &wy, const tab_bit &tb)
{
    string pomoc = dec_to_bin(tb.tab[0]);
    for(int i = 1; i < sufit(tb.dl, tb.rozmiarSlowa); i++)
    {
        string pomoc2 = dec_to_bin(tb.tab[i]);
        while(pomoc2.size() != tb.rozmiarSlowa)
        {
            pomoc2 = "0" + pomoc2;
        }
        pomoc += pomoc2;
    }
    while(pomoc.size() != tb.dl)
    {
        pomoc = "0" + pomoc;
    }
    wy << pomoc;
    return wy;
}

tab_bit::tab_bit(int rozm):
    dl(rozm), 
    tab(new slowo[(slowo) sufit(rozm, rozmiarSlowa)])
{
    for(slowo i = 0; i < sufit(rozm, rozmiarSlowa); i++)
    {
        tab[i] = 0;
    }
}
tab_bit::tab_bit (slowo tb):
    dl(sizeof(uint64_t)*8),
    tab(new slowo[1])
{
    tab[0] = tb;
}
tab_bit::tab_bit (unsigned long long tb):
    dl((sizeof(uint64_t)*8)),
    tab(new slowo[1])
{
    tab[0] = tb;
}

tab_bit::tab_bit (const tab_bit &tb):
    dl(tb.dl),
    tab(new slowo[(slowo) sufit(dl, rozmiarSlowa)])
{
    for(int i = 0; i < sufit(dl, rozmiarSlowa); i++)
    {
        tab[i] = tb.tab[i];
    }
}

tab_bit::tab_bit (tab_bit &&tb):
    dl(tb.dl),
    tab(tb.tab)
{
}

tab_bit &tab_bit::operator = (const tab_bit &tb)
{
    if(this == &tb)
    {
        return *this;
    }
    delete[] tab;
    dl = tb.dl;
    tab = new slowo[(slowo) sufit(dl, rozmiarSlowa)];
    for(int i = 0; i < sufit(dl, rozmiarSlowa); i++)
    {
        tab[i] = tb.tab[i];
    }
    return *this;
}

tab_bit &tab_bit::operator = (tab_bit &&tb)
{
    if(this == &tb)
    {
        return *this;
    }
    delete[] tab;
    dl = tb.dl;
    tab = tb.tab;
    return *this;
}

bool tab_bit::czytaj(int i) const
{
    int k = i % rozmiarSlowa;
    uint64_t liczba = tab[podloga(i, rozmiarSlowa)];
    return (liczba >> k) & 1;
}

void tab_bit::pisz (int i, bool b)
{
    int k = i % rozmiarSlowa;
    uint64_t liczba = tab[podloga(i, rozmiarSlowa)];
    liczba = liczba & ~((uint64_t)1 << k);
    tab[podloga(i, rozmiarSlowa)] = (liczba | ((uint64_t)b << k));
}

tab_bit::slowo tab_bit::get_tab_size()
{
    return (slowo) sufit(dl, rozmiarSlowa);
}

bool tab_bit::operator[] (int i) const
{
    if(i > dl)
    {
        throw invalid_argument("index bigger than size of tab_bit");
    }
    return czytaj(i);
}

tab_bit::ref tab_bit::operator[] (int i)
{
    bool wartosc = czytaj(i);
    ref referencja(*this, i, wartosc);
    return referencja;
}

tab_bit::ref &tab_bit::ref::operator=(bool v)
{
    value = v;
    tab.pisz(index, v);
    return *this;
}

tab_bit tab_bit::operator | (tab_bit &tb)
{
    tab_bit wynik(max(dl, tb.dl));
    int i = get_tab_size() - 1;
    int j = tb.get_tab_size() - 1;
    if(i >= j)
    {
        while(j >= 0)
        {
            wynik.tab[i] = tab[i] | tb.tab[j];
            j--;
            i--;
        }
        while(i >= 0)
        {
            wynik.tab[i] = tab[i];
        }
    }
    else
    {
        while(i >= 0)
        {
            wynik.tab[j] = tab[i] | tb.tab[j];
            j--;
            i--;
        }
        while(j >= 0)
        {
            wynik.tab[j] = tb.tab[j];
        }
        
    }
    return wynik;
}
tab_bit &tab_bit::operator |= (tab_bit &tb)
{
    int i = get_tab_size() - 1;
    int j = tb.get_tab_size() - 1;
    if(i < j)
    {
        throw invalid_argument("tab_bit size is wrong");
    }
    while(j >= 0)
    {
        tab[i] = tab[i] | tb.tab[j];
        j--;
        i--;
    }
    return *this;
}
tab_bit tab_bit::operator & (tab_bit &tb)
{
    tab_bit wynik(max(dl, tb.dl));
    int i = get_tab_size() - 1;
    int j = tb.get_tab_size() - 1;
    if(i >= j)
    {
        while(j >= 0)
        {
            wynik.tab[i] = tab[i] & tb.tab[j];
            j--;
            i--;
        }
        while(i >= 0)
        {
            wynik.tab[i] = 0;
        }
    }
    else
    {
        while(i >= 0)
        {
            wynik.tab[j] = tab[i] & tb.tab[j];
            j--;
            i--;
        }
        while(j >= 0)
        {
            wynik.tab[j] = 0;
        }
        
    }
    return wynik;

}
tab_bit &tab_bit::operator &= (tab_bit &tb)
{
    int i = get_tab_size() - 1;
    int j = tb.get_tab_size() - 1;
    if(i < j)
    {
        throw invalid_argument("tab_bit size is wrong");
    }
    while(j >= 0)
    {
        tab[i] = tab[i] & tb.tab[j];
        j--;
        i--;
    }
    while(i >= 0)
    {
        tab[i] = 0;
    }
    return *this;

}
tab_bit tab_bit::operator ^ (tab_bit &tb)
{
    tab_bit wynik(max(dl, tb.dl));
    int i = get_tab_size() - 1;
    int j = tb.get_tab_size() - 1;
    if(i >= j)
    {
        while(j >= 0)
        {
            wynik.tab[i] = tab[i] ^ tb.tab[j];
            j--;
            i--;
        }
        while(i >= 0)
        {
            wynik.tab[i] = tab[i] ^ 0;
        }
    }
    else
    {
        while(i >= 0)
        {
            wynik.tab[j] = tab[i] ^ tb.tab[j];
            j--;
            i--;
        }
        while(j >= 0)
        {
            wynik.tab[j] = tb.tab[j] ^ 0;
        }
        
    }
    return wynik;
}
tab_bit &tab_bit::operator ^= (tab_bit &tb)
{
    int i = get_tab_size() - 1;
    int j = tb.get_tab_size() - 1;
    if(i < j)
    {
        throw invalid_argument("tab_bit size is wrong");
    }
    while(j >= 0)
    {
        tab[i] = tab[i] ^ tb.tab[j];
        j--;
        i--;
    }
    while(i >= 0)
    {
        tab[i] = tab[i] ^ 0;
    }
    return *this;
}

tab_bit &tab_bit::operator ~ ()
{
    for(int i = 0; i < get_tab_size(); i++)
    {
        tab[i] = ~tab[i];
    }
    return *this;
}

tab_bit::ref &tab_bit::ref::operator=(const tab_bit::ref &tb)
{
    value = tb.value;
    tab[index] = value;
    return *this;
}