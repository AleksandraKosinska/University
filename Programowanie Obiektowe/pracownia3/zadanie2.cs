using System;

namespace l2z2_classes
{

    public class LinkedList <T>
    {
        private class Element
        {
            public int idx;
            public T value;
            public Element next;
            public Element prev;

            public Element(int i)
            {
                this.idx = i;
            }
        }

        private Element front;
        private Element back;

        public LinkedList(int start, int end)
        {
            if (end < start)
                throw new System.ArgumentException("Wrong indexes");

            this.front = new Element(start);
            Element aux = this.front;

            for (int i = start+1; i < end; i++)
            {
                Element next_a = new Element(i);
                aux.next = next_a;
                next_a.prev = aux;
                aux = next_a;
            }

            if (start != end)
            {
                Element next_a = new Element(end);
                aux.next = next_a;
                next_a.prev = aux;
                this.back = next_a;
            }
            else
                this.back = this.front;
        }

    }
}