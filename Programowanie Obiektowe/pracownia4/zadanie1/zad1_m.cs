//Współpraca Ola Kosińska, Cezary Stajszczyk, Cezary Troska
using System;
using L4Z1_c;

namespace L4Z1
{
  class MainClass
  {

    static void Main () 
    { 
      PrimeCollection pc = new PrimeCollection(7);
      Console.WriteLine("prezentacja: ");
      Console.WriteLine("wypisanie wszystkich 7 liczb pierwszych z 'pc': ");
      foreach (int p in pc)
      {
        Console.Write(p);
        Console.Write("  ");
      }
          
      Console.WriteLine();
      Console.WriteLine("3 pierwsze liczby pierwsze z 'pc': ");

      for(int i=0; i<3; i++)
      {
        Console.Write(pc[i]);
        Console.Write("  ");

      }
      Console.WriteLine();

      EvenCollection ec = new EvenCollection(10);

      Console.WriteLine("wypisanie wszystkich 10 liczb parzystych z 'ec': ");
      foreach (int p in ec)
      {
        Console.Write(p);
        Console.Write("  ");
      }
          
      Console.WriteLine();
      Console.WriteLine("5 pierwszych liczb parzystych z 'ec': ");

      for(int i=0; i<5; i++)
      {
        Console.Write(ec[i]);
        Console.Write("  ");
      }
      Console.WriteLine();


    } 
  } 
}
