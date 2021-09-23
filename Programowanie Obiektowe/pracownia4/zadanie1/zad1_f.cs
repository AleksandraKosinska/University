//Współpraca Ola Kosińska, Cezary Stajszczyk, Cezary Troska
using System;
using System.Collections;

namespace L4Z1_c
{

    public class MyEnumerator:IEnumerator
    {
        
        private int position;
        private int size;
        private int[] resource;

        public MyEnumerator(int[] list, int s)
        {
            position = -1;
            resource = list;
            size = s;
        }

        public bool MoveNext()
        {
            position++;
            return (position<size);
        }

        public void Reset()
        {
            position = -1;
        }

        public object Current
        {
            get
            {
                return resource[position];
            }
        }

    }

    interface IHotDog
    {
        int this[int key]{get;}
        void populate();
        int NextMember(int number);
    }


    public class PrimeCollection : IEnumerable, IHotDog
    {
        public int Length{    get;}

        int[] resource;
        private MyEnumerator MyEnu;
        
        public override string ToString(){
            string output = "";
            foreach(int s in resource){
                output+=s.ToString()+" ";
            }
            return output;
        }
        public PrimeCollection(int s = 100)
        {
            Length = s;
            resource = new int[Length];
            populate();
            MyEnu = new MyEnumerator(resource,Length);
        }


        public void populate()
        {
            for(int i = 0; i<Length;i++)
            {
                if(i==0)
                    resource[i] = 2;
                else
                    resource[i] = NextMember(resource[i-1]);
            }
        }

        private bool IfPrime(int number)
        {
            if (number < 2)
            {
                return false;
            }
            if (number % 2 == 0)
            {
                return (number == 2);
            }
            if (number % 3 == 0)
            {
                return (number == 3);
            }
            for (int i = 5; i <= number/i; i += 6)
            {
                if (number % i == 0 || number % (i + 2) == 0)
                {
                    return false;
                }
            }
            return true;
        }

        public int NextMember(int number)
        {
            do
            {
                number++;
            } while (!IfPrime(number));

            return number;
        }

        public int this[int key]
        {
            get
            {
                return resource[key];
            }
        }
        
        IEnumerator IEnumerable.GetEnumerator()
        {
            return MyEnu;
        }
    }

    public class EvenCollection : IEnumerable, IHotDog
    {
        public int size;
        int[] resource;
        MyEnumerator MyEnu;
        

        public EvenCollection(int s = 100)
        {
            size = s;
            resource = new int[size];
            populate();
            MyEnu = new MyEnumerator(resource,size);
        }

        public int NextMember(int number)
        {
            return number*2;
        }

        public void populate()
        {
            for(int i = 0; i<size;i++)
                resource[i] = i*2;
        }

        public int this[int key]
        {
            get
            {
                return resource[key];
            }
        }
        
        IEnumerator IEnumerable.GetEnumerator()
        {
            return MyEnu;
        }
    }

}