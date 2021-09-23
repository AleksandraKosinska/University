import java.util.ArrayList;
import java.util.List;
import java.io.*; 

public class Armia implements Serializable{
    private static final long serialVersionUID = 129348938L;

    List<Szeregowy> jednostki = new ArrayList<Szeregowy>();

    private void do_szeregu()
    {
        jednostki.sort(null);
    }

    public Szeregowy wystap()
    {
        do_szeregu();
        return jednostki.remove(0);
    }

    public void NowyRekrut(Szeregowy mieso)
    {
        jednostki.add(mieso);
    }

    public void prezentuj_bron()
    {
        do_szeregu();
        for (Szeregowy szeregowy : jednostki) {
            System.out.println("Imie: "+szeregowy.imie+"  ||  ranga: "+szeregowy.ranga+"  ||  wartosc bojowa:  "+szeregowy.wartoscbojowa);
        }
    }
}