using System;

namespace L3Z1_c
{
    public class Lista<T>
    {
        private class Element
        {
            public Element next;
            public Element prev;
            public int index;
            public T value;
            public Element(int ind, T val = default(T))
            {
                this.index = ind;
                this.value = val;
            }
            
        }

        Element head = new Element(0);
        Element tail;

        public Lista(int size = default(int))
        {
            if(size < 0)
            {
                throw new ArgumentException("negative number");
            }
            if(size == 0)
            {
                this.head = null;
            }
            else
            {
                Element h = this.head;
                for(int i = 1; i < size; i++)
                {
                    Element e = new Element(i);
                    h.next = e;
                    e.prev = h;
                    h = e;
                }
                this.tail = h;
            }
        }

        public void push_front(T val = default(T))
        {
            if(this.tail == null || this.head == null)
            {
                Element e = new Element(0, val);
                this.head = e;
                this.tail = e;
            }
            else
            {
                Element e = new Element(-1, val);
                head.prev = e;
                e.next = head;
                head = e;
                while(e != null)
                {
                    e.index = e.index + 1;
                    e = e.next;
                }
            }
            
        }

        public void push_back(T val = default(T))
        {
            if(this.tail == null || this.head == null)
            {
                Element e = new Element(0, val);
                this.head = e;
                this.tail = e;
            }
            else
            {
                Element e = new Element(tail.index + 1, val);
                tail.next = e;
                e.prev = tail;
                tail = e;
            }
        }
        public T pop_front()
        {
            if(this.head == this.tail)
            {
                T ret = this.head.value;
                this.head = null;
                this.tail = null;
                return ret;
            }
            else
            {
                T ret = this.head.value;
                head = head.next;
                head.prev = null;
                Element e = head;
                while(e != null)
                {
                    e.index = e.index - 1;
                    e = e.next;
                }
                return ret;
            }
        }
        public T pop_back()
        {
            if(this.head == this.tail)
            {
                T ret = this.head.value;
                this.head = null;
                this.tail = null;
                return ret;
            }
            else
            {
                T ret = this.tail.value;
                tail = tail.prev;
                tail.next = null;
                return ret;
            }
            
        }
        public bool is_empty()
        {
            return(this.tail == null || this.head == null);
        }
        public void print()
        {
            Element e = this.head;
            while(e != null)
            {
                Console.Write(e.index);
                Console.Write(": ");
                Console.Write(e.value);
                Console.Write(",  ");
                e = e.next;
            }
        }
    }
}
