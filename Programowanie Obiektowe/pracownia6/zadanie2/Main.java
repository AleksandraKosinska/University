// współpraca: Cezary Stajszczyk, Cezary Troksa, Aleksandra Kosińska, Paweł Drzycimski

import java.io.*; 

public class Main{
    public static void main(String[] args){
        Armia BPP = new Armia();
        BPP.NowyRekrut(new Szeregowy("Gump", 100));
        BPP.NowyRekrut(new Kapral("Wojtek", 40));
        BPP.NowyRekrut(new Major("Schaeffer", 200));
        BPP.NowyRekrut(new General("Rommel", 100));
        BPP.NowyRekrut(new Szeregowy("Ryan", 1));


        Armia Bubuntownicy = new Armia();
        Bubuntownicy.NowyRekrut(new Szeregowy("CzarekS", 100));
        Bubuntownicy.NowyRekrut(new Szeregowy("CzarekT", 100));
        Bubuntownicy.NowyRekrut(new Szeregowy("OlaK", 100));
        Bubuntownicy.NowyRekrut(new Szeregowy("PawelD", 100));
        Bubuntownicy.NowyRekrut(new Szeregowy("AntekD", 100));

        BPP.addAll(Bubuntownicy);

        for (var zolnierz : BPP) {
            System.out.println( ((Szeregowy)zolnierz).imie + " melduje się!");
        }

        System.out.println("czy zawiera Gump?");
        System.out.println(BPP.contains(new Szeregowy("Gump", 100)));
        System.out.println("czy jest równy z nową armią zawierającą tylko szeregowego Ryan?");
        Armia BPP_2 = new Armia();
        BPP_2.NowyRekrut(new Szeregowy("Ryan", 1));
        System.out.println(BPP.equals(BPP_2));


        System.out.println("Liczba biednych piechotników: "+BPP.size());
        System.out.println("Piechotnicy w tablicy: "+BPP.toArray());
        
        System.out.println("Jeden poległ...");
        BPP.remove(BPP.wystap());
        System.out.println("Liczba biednych piechotników: "+BPP.size());
        System.out.println("Piechotnicy w tablicy: "+BPP.toArray());
        
        System.out.println("Jeden poległ...");
        BPP.remove(BPP.wystap());
        System.out.println("Liczba biednych piechotników: "+BPP.size());

        System.out.println("Wracamy do domu!");
        BPP.removeAll(BPP);
        System.out.println("Liczba biednych piechotników: "+BPP.size());
    }
}
