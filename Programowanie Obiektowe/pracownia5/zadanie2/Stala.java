
public class Stala implements obliczanie{
    Integer stala;
    public Stala(int a)
    {
        stala = a;
    }

    @Override
    public int oblicz() {
        return stala;
    }

    @Override
    public String toString()
    {
        return stala.toString();
    }

}