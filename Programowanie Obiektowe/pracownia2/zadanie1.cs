using System;
using System.Text;

namespace L1Z1
{
    class MainClass
    {
        public static void Main (string[] args)
        {
            Console.WriteLine("prezentacja:");
            Console.WriteLine("10 liczb pierwszych:");
            PrimeStream p = new PrimeStream();
            for(int i = 0; i < 10; i++)
            {
                Console.Write(p.next());
                Console.Write("  ");
            }
            Console.WriteLine();
            Console.WriteLine("5 liczb losowych:");
            RandomStream r = new RandomStream();
            for(int i = 0; i < 5; i++)
            {
                Console.Write(r.next());
                Console.Write("  ");
            }
            Console.WriteLine();
            Console.WriteLine("7 losowych stringow:");
            RandomWordStream rws = new RandomWordStream();
            for(int i = 0; i < 7; i++)
            {
                Console.Write(rws.next());
                Console.Write("  ");
            }
            Console.WriteLine();

        }
    }

    class IntStream
    {
        protected int value;
        public IntStream()
        {
            value = 0;
        }
        public bool eos()
        {
            if(value == int.MaxValue)
            {
                return true;
            }
            return false;
        }
        virtual public void reset()
        {
            value = 0;
        }
        virtual public int next()
        {
            if(!eos())
            {
                value++;
                return value-1;
            }
            reset();
            return value;
        }
    }
    class PrimeStream:IntStream
    {
        public PrimeStream()
        {
            value = 1;
        }
        override public void reset()
        {
            value = 1;
        }
        private bool prime(int number)
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
            int root = (int)Math.Sqrt((double)number);
            for (int i = 5; i <= root; i += 6)
            {
                if (number % i == 0 || number % (i + 2) == 0)
                {
                    return false;
                }
            }
            return true;
        }
        override public int next()
        {
            do
            {
                value ++;
            } while(!prime(value) && !eos());
            if(eos())
            {
                reset();
            }
            return value;
        }
    }
    class RandomStream:IntStream
    {
        private Random r;
        public RandomStream()
        {
            r = new Random();
        }
        override public int next()
        {
            value = r.Next(int.MaxValue);
            return value;
        }
    }
    class RandomWordStream
    {
        StringBuilder word;
        private int length;
        private PrimeStream p;
        private RandomStream random_letter;

        public RandomWordStream()
        {
            word = new StringBuilder();
            p = new PrimeStream();
            length = p.next();
            random_letter = new RandomStream(); 
        }
        public string next()
        {
            word = new StringBuilder();
            for (int i = 0; i < length; i++)
            {
                word.Append(Convert.ToChar((random_letter.next())%93 + 33));
            }  
            length = p.next();
            return word.ToString();
        }
    }
}