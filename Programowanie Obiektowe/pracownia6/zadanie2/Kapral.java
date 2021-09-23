public class Kapral extends Szeregowy
{
    public Kapral(String i, Integer wartosc)
    {
        super(i, wartosc);
        ranga = 1;
    }

    public int compareTo(Szeregowy o)
    {
        if(o.ranga > ranga)
            return -1;
        if(o.ranga < ranga)
            return 1;
        if(o.wartoscbojowa > wartoscbojowa)
            return -1;
        if(o.wartoscbojowa < wartoscbojowa)
            return 1;
        return 0;
    }

}