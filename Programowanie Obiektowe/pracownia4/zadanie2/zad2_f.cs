//Współpraca Ola Kosińska, Cezary Stajszczyk, Cezary Troska
using System;
using System.Collections;

namespace L4Z2_c
{
    
    public class PrimeCollection : IEnumerable
    {
        
        private class MyEumerator:IEnumerator
        {
            
            private int position;

            public MyEumerator()
            {
                position = 1;
            }

            public bool MoveNext()
            {
                return !(position == Int32.MaxValue);
            }

            public void Reset()
            {
                position = 1;
            }

            private static bool IfPrime(int number)
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

            public static int NextPrime(int number)
            {
                do
                {
                    number++;
                } while (!IfPrime(number));

                return number;
            }
            object IEnumerator.Current
            {
                get
                {
                    return Current;
                }
            }

            public int Current
            {
                get
                {
                    position = NextPrime(position);
                    return position;
                }
            }

        }

        public int this[int key]
        {
            get
            {
                int result = 2;
                for(int i = 0; i < key;i++)
                    result = MyEumerator.NextPrime(result);

                return result;
            }

        }
        

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new MyEumerator();
        }
    }
}