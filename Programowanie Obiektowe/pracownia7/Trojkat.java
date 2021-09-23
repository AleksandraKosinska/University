import java.io.Serializable;

public class Trojkat extends Figura implements Serializable
{
    private static final long serialVersionUID = 1L;
    public Double bok1;
    public Double bok2;
    public Double bok3;
    public String nazwa;

    public Trojkat(Double a, Double b, Double c)
    {
        bok1 = a;
        bok2 = b;
        bok3 = c;
        Double p = (a + b + c) / 2;
        pole = Math.sqrt(p * (p-a) * (p- b) * (p-c));
        obwod = a + b + c;
        nazwa = "trojkat";
    }

    public Boolean is_triangle()
    {
        if((bok1+bok2)>bok3 && (bok1+bok3)>bok2 && (bok2+bok3)>bok1)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

}