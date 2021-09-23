using System;

namespace L3Z2_c
{

    public class Slownik<K, V> where K : class
    {
        private class Element
        {
            public K key;
            public V value;
            public Element next;

            public Element(K k, V val = default(V))
            {
                this.key = k;
                this.value = val;
            }
        }
        private Element head;
        public Slownik(){}
        
        public void add(K k, V value)
        {
            if(this.head == null)
            {
                Element add = new Element(k,value);
                add.next = null;
                this.head = add;
            }
            else
            {
                Element e = this.head;
                while(e.next != null)
                {
                    if (e.key == k)
                    {
                        throw new ArgumentException("this key is already in use");
                    }
                    e = e.next;
                }
                Element add = new Element(k,value);
                add.next = null;
                e.next = add;
            }
        }

        public V search(K k)
        {
            Element e = this.head;
            while(e!= null)
            {
                if(e.key == k)
                {
                    return e.value;
                }
                e = e.next;
            }
            throw new ArgumentException("no such key");
        }

        public void remove(K k)
        {
            if(this.head == null)
            {
                throw new ArgumentException("slownik is empty");
            }
            if(head.key == k)
            {
                this.head = head.next;
            }
            else
            {
                Element e = this.head;
                while(e.next != null)
                {
                    if(e.next.key == k)
                    {
                        e.next = e.next.next;
                        break;
                    }
                    e = e.next;
                }
            }
        }

        public void print()
        {
            Element e = this.head;
            while(e != null)
            {
                Console.Write(e.key);
                Console.Write(": ");
                Console.Write(e.value);
                Console.Write(",  ");
                e = e.next;
            }
        }
    }
}