using System;

namespace L3Z2
{
  class MainClass
  {
    static void Main (string[] args) 
    { 
        Console.WriteLine("prezentacja:");
        Console.WriteLine("slownik elementemi klucze to nazwy zwierzat a wartosci to liczby:");
        L3Z2_c.Slownik<string, int> slownik = new L3Z2_c.Slownik<string,int>();
        slownik.add("pies", 7);
        slownik.add("kot", 3);
        slownik.add("krolik", 5);
        slownik.add("surykatka", 10);
        slownik.add("delfin", 8);
        slownik.print();
        Console.WriteLine();
        Console.WriteLine("slownik po usunieciu elementu o kluczu 'krolik':");
        slownik.remove("krolik");
        slownik.print();
        Console.WriteLine();
        Console.WriteLine("wartosc po wyszukaniu klucza 'surykatka':");
        Console.WriteLine(slownik.search("surykatka"));

    } 
  } 
}