//Współpraca Ola Kosińska, Cezary Stajszczyk, Cezary Troska
using System;
using L4Z2_c;

namespace L4Z2
{
  class MainClass
  {
    static void Main () 
    { 
      PrimeCollection pc = new PrimeCollection();
      Console.WriteLine("wypisanie liczb pierwszych:");
      foreach (int p in pc)
      {
        Console.Write(p);
        Console.Write("  ");
      }
    } 
  } 
}