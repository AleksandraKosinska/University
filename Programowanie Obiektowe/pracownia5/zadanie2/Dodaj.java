
public class Dodaj extends Wyrarzenie{
    public Dodaj(obliczanie w1, obliczanie w2)
    {
        super(w1, w2);
    }

    @Override
    public int oblicz()
    {
        return w1.oblicz() + w2.oblicz();
    }

    @Override
    public String toString()
    {
        return ("(" + w1.toString() + "+" + w2.toString() + ")");
    }
}