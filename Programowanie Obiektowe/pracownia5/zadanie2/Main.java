
public class Main {
    public static void main(String[] args)
    {
        System.out.println("nowy element dodaj(odejmij(7, 3), 2): ");
        Dodaj d = new Dodaj(new Odejmij(new Stala(7), new Stala(3)), new Stala(2));
        System.out.println(d);
        System.out.println("jego wartosc: " + d.oblicz());
        Odejmij o = new Odejmij(new Stala(3), new Zmienna("x"));
        System.out.println("nowy element odejmij(3, 'x'): ");
        System.out.println(o);
        Pomnoz p = new Pomnoz(new Stala(4), new Zmienna("z", 3));
        System.out.println("nowy element pomnoz(4, 'z' o wartosci 3): ");
        System.out.println(p);
        System.out.println("jego wartosc: " + p.oblicz());
    }

}