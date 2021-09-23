#ifndef tabbit_hpp
#define tabbit_hpp

#include <iostream>
#include <cmath>

using namespace std;

string dec_to_bin(uint64_t);
int sufit(int, int);
int podloga(int, int);
uint64_t potega(int liczba, int p);
int64_t bin_to_dec(string napis);

class tab_bit
{
    typedef uint64_t slowo;
    static const int rozmiarSlowa = (sizeof(slowo) * 8);

    friend istream & operator >> (istream &we, tab_bit &tb);
    friend ostream & operator << (ostream &wy, const tab_bit &tb);

    class ref
    {
        protected:
        tab_bit& tab;
        int index;
        bool value;
        public: 
        ref(tab_bit& t, int ind, bool val):
           tab(t), index(ind), value(val)
        {
        }
        friend ostream & operator << (ostream &we, const ref &r)
        {
            return we << r.value;
        }
        ref & operator = (bool v);
        ref & operator = (const tab_bit::ref &);
        operator int() const
        {
            return value;
        }
    };
    

    protected:
    int dl;
    slowo *tab;

    public:
    explicit tab_bit (int rozm);
    explicit tab_bit (slowo tb);
    explicit tab_bit (unsigned long long);
    tab_bit (const tab_bit &tb);
    tab_bit (tab_bit &&tb);
    tab_bit & operator = (const tab_bit &tb);
    tab_bit & operator = (tab_bit &&tb);
    ~tab_bit ();

    private:
    bool czytaj (int i) const;
    void pisz (int i, bool b);

    public:
    slowo get_tab_size();
    bool operator[] (int i) const;
    ref operator[] (int i);
    inline int rozmiar () const
    {
        return dl;
    };

    public:
    tab_bit operator | (tab_bit &tb);
    tab_bit &operator |= (tab_bit &tb);
    tab_bit operator & (tab_bit &tb);
    tab_bit &operator &= (tab_bit &tb);
    tab_bit operator ^ (tab_bit &tb);
    tab_bit & operator ^= (tab_bit &tb);
    tab_bit & operator ~ ();
};

istream & operator >> (istream &we, tab_bit &tb);
ostream & operator << (ostream &wy, const tab_bit &tb);


#endif