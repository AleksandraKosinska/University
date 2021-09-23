using System;
using System.Collections.Generic; 

namespace L1Z2
{
  class MainClass
  {
    public static void Main (string[] args) 
    {
        Array arr = new Array(4,15);
        Console.WriteLine("prezentacja(index: wartosc): ");
        Console.WriteLine("lista od 4 do 15:");
        arr.print();
        Console.WriteLine("lista z elementem o wartosci 56 na pozycji 10:");
        arr.set(10, 56);
        arr.print();
        Console.WriteLine("lista po usunieciu ostatniego elementu:");
        arr.pop_back();
        arr.print();
        Console.WriteLine("lista po dodaniu elementu 12 na poczatek;");
        arr.push_front(12);
        arr.print();
    }
  }

  class Element
  {
      public int index;
      public int val;
      public Element next;
      public Element prev;

      public Element(int ind, int val=0)
      {
          this.index = ind;
          this.val = val;
      }
  }

  class Array
  {
    public Element head;
    public Element tail;
    public Array(int start, int end)
    {
        this.head = new Element(start);
        Element h = this.head;
        for(int i=start+1; i<end; i++)
        {
            Element new_e = new Element(i);
            h.next = new_e;
            new_e.prev = h;
            h = new_e;
        }
        this.tail = new Element(end);
        h.next = this.tail;
        this.tail.prev = h;
    }
    public int get(int ind)
    {
        if(ind < this.head.index || ind > this.tail.index)
        {
            throw new ArgumentException("out of range");
        }
        if(ind - this.head.index < this.tail.index)
        {
            Element e = this.head;
            while(e.index != ind)
            {
                e = e.next;
            }
            return e.val;

        }
        else
        {
            Element e = this.tail;
            while(e.index != ind)
            {
                e = e.prev;
            }
            return e.val;
        }
    }
    public void set(int ind, int val)
    {
        if(ind < this.head.index || ind > this.tail.index)
        {
            throw new ArgumentException("out of range");
        }
        if(ind - this.head.index < this.tail.index - ind)
        {
            Element e = this.head;
            while(e.index != ind)
            {
                e = e.next;
            }
            e.val = val;
        }
        else
        {
            Element e = this.tail;
            while(e.index != ind)
            {
                e = e.prev;
            }
            e.val = val;
        }
    }
    public void push_front(int val)
    {
        Element e = new Element(this.head.index - 1);
        head.prev = e;
        e.next = this.head;
        this.head = e;
        e.val = val;
    }
    public void push_back(int val)
    {
        Element e = new Element(this.tail.index + 1);
        tail.next = e;
        e.prev = this.tail;
        this.tail = e;
        e.val = val;
    }
    public int pop_front()
    {
        int ret = head.val;
        head = head.next;
        head.prev = null;
        return ret;
    }
    public int pop_back()
    {
        int ret = tail.val;
        tail = tail.prev;
        tail.next = null;
        return ret;
    }
    public void print()
    {
        Element e = this.head;
        while(e != null){
            Console.Write(e.index);
            Console.Write(": ");
            Console.WriteLine(e.val);
            e = e.next;
        }
    }
  }
}