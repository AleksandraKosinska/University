
public class Zmienna implements obliczanie{

    String zmienna;
    static Integer wartosc;

    public Zmienna(String z)
    {
        zmienna = z;
        wartosc = 0;
    }

    public Zmienna(String z, Integer w)
    {
        zmienna = z;
        wartosc = w;
    }

    @Override
    public int oblicz() {
        return wartosc;
    }
    
    @Override
    public String toString()
    {
        return zmienna;
    }

}