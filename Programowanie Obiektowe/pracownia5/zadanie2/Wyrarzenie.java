
public class Wyrarzenie implements obliczanie{
    
    obliczanie w1;
    obliczanie w2;

    public Wyrarzenie(obliczanie a, obliczanie b)
    {
        w1 = a;
        w2 = b;
    }

    @Override
    public int oblicz() {

        return w1.oblicz();
    }

    @Override
    public String toString(){
        return (w1.toString() + "," + w2.toString()); 
    }

}