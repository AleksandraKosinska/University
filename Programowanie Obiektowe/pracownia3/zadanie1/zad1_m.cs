using System;

namespace L3Z1
{
    class MainClass
    {
        static void Main(string[] args)
        {
            Console.WriteLine("prezentacja: ");
            Console.WriteLine("List<int> o rozmiarze 5:");
            L3Z1_c.Lista <int> lista = new L3Z1_c.Lista<int>(5);
            lista.print();
            Console.WriteLine();
            Console.WriteLine("po dodaniu elementu o wartosci 90 na poczatku:");
            lista.push_front(90);
            lista.print();
            Console.WriteLine();
            Console.WriteLine("po usunieciu ostatnich 4 elementow:");
            lista.pop_back();
            lista.pop_back();
            lista.pop_back();
            lista.pop_back();
            lista.print();
            Console.WriteLine();
            Console.WriteLine("sprawdzenie czy jest pusta:");
            Console.WriteLine(lista.is_empty());

            Console.WriteLine();
            Console.WriteLine("List<string> o rozmiarze 2:");
            L3Z1_c.Lista <string> lista2 = new L3Z1_c.Lista<string>(2);
            lista2.print();
            Console.WriteLine();
            Console.WriteLine("po dodaniu elementu o wartosci 'napis' na koncu i 'napis_dwa' na poczatku:");
            lista2.push_back("napis");
            lista2.push_front("napis_dwa");
            lista2.print();
            Console.WriteLine();
            Console.WriteLine("po usunieciu pierwszych trzech elementow:");
            lista2.pop_front();
            lista2.pop_front();
            lista2.pop_front();
            lista2.print();
            Console.WriteLine();
            Console.WriteLine("sprawdzenie czy jest pusta:");
            Console.WriteLine(lista2.is_empty());
            Console.WriteLine("sprawdzenie czy jest pusta po usunieciu elementu:");
            lista2.pop_back();
            Console.WriteLine(lista2.is_empty());


        }
    }
}
