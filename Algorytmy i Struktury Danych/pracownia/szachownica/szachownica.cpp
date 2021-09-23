#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <math.h>

using namespace std;


bool czy_poprawny(uint16_t wzorzec, uint16_t *zakazane, uint16_t p){
    // maski sprawdzajace poprawnosc
    uint16_t maska0 = 0b0111001110011100;
    uint16_t maska1 = 0b0011100111001110;
    uint16_t maska2 = 0b0001110011100111;

    for(uint8_t i = 0; i < p; i++){
        if((wzorzec & maska0) == zakazane[i]){
            return 0;
        }
        if((wzorzec & maska1) == (zakazane[i] >> 1)){
            return 0;
        }
        if((wzorzec & maska2) == (zakazane[i] >> 2)){
            return 0;
        }
    }
    return 1;
}

int main(){
    uint16_t n;
    uint16_t p;
    uint32_t m;
    scanf("%" SCNu16, &n);
    scanf("%" SCNu16, &p);
    scanf("%" SCNu32, &m);

    //tablica zakazanych wzorcow
    uint16_t zakazane[p] = {0};
    uint16_t *zp = zakazane;
    char znak;
    for(uint8_t i = 0; i < p; i++){
        for(uint8_t j = 14; j >= 12; j--){
            for(uint8_t k = 0; k <= 10; k += 5){
                scanf(" %c", &znak);
                zakazane[i] |= (znak == 'x') << (j - k);
            }
        }
    }

    // tablica zawierajaca ilosc rozwiazan dla danego klucza, ktorym sa dwie ostatnie kolumny
    uint64_t w[1024] = {0};
    uint64_t *wynik = w;

    // tablica zawierajaca informacje czy dany wzorzec 3x5 jest poprawny
    uint16_t poprawne[32768] = {0};
    for(uint16_t wzorzec = 0; wzorzec < 32768; wzorzec++){
        if(czy_poprawny(wzorzec, zp, p)){
            wynik[wzorzec & 0b0000001111111111]++;
            poprawne[wzorzec] = 1;
        }
    }

    // tymczasowa tablica zawierajaca wyniki kolejnych iteracji
    uint64_t t[1024] = {0};
    uint64_t *tmp = t;

    uint16_t kombinacja = 0;
    for(uint16_t i = 3; i < n; i++){
        for(uint16_t wzorzec = 0; wzorzec < 1024; wzorzec++){
            for(uint16_t kolumna = 0; kolumna < 32; kolumna++){
                kombinacja = ((wzorzec << 5) | kolumna);
                if(poprawne[kombinacja]){
                    tmp[kombinacja & 0b0000001111111111] += (wynik[wzorzec] % m);
                }
            }
            wynik[wzorzec] = 0;
        }
        uint64_t *tmp2 = wynik;
        wynik = tmp;
        tmp = tmp2;
    }

    uint64_t suma = 0;
    for(uint16_t i = 0; i < 1024; i++){
        suma += wynik[i];
    }
    suma %= m;

    printf("%ld\n", suma);
    return 0;
}
