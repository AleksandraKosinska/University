
public class Podziel extends Wyrarzenie{
    public Podziel(obliczanie w1, obliczanie w2)
    {
        super(w1, w2);
    }

    @Override
    public int oblicz()
    {
        if (w2.oblicz() == 0)
        {
            throw new ArithmeticException("/ by zero");
        }
        return w1.oblicz() / w2.oblicz();
    }

    @Override
    public String toString()
    {
        return ("(" + w1.toString() + "/" + w2.toString() + ")");
    }

}