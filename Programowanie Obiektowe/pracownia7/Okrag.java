import java.io.Serializable;

public class Okrag extends Figura implements Serializable
{
    private static final long serialVersionUID = 1L;
    private Double promien;
    private Double pi = Math.PI;
    public String nazwa;

    public Okrag(Double r)
    {
        promien = r;
        pole = pi * r * r;
        obwod = 2 * pi * r;
        nazwa = "okrag";
    }

    public Double get_promien()
    {
        return promien;
    }

    @Override
    public String toString()
    {
        return nazwa + " Pole: " + pole + ",  Obwod: " + obwod;
    }

}