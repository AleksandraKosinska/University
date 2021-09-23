import java.io.*; 

public class Szeregowy implements java.lang.Comparable<Szeregowy>, Serializable
{
    private static final long serialVersionUID = 129348938L;

    Integer wartoscbojowa;
    Integer ranga;
    String imie;

    Szeregowy(String i, Integer wartosc)
    {
        wartoscbojowa = wartosc;
        imie = i;
        ranga = 0;
    }

    public void strzela()
    {
        System.out.println("PifPaf");
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
