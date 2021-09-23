// współpraca: Cezary Stajszczyk, Cezary Troksa, Aleksandra Kosińska, Paweł Drzycimski
import java.io.*; 

public class Main{
    public static void main(String[] args){
        String filename = "koszary.txt";
        Armia BPP = new Armia();

        try{
            FileOutputStream file_out = new FileOutputStream (filename); 
            ObjectOutputStream out = new ObjectOutputStream (file_out); 

            BPP.NowyRekrut(new Szeregowy("Gump", 100));
            BPP.NowyRekrut(new Kapral("Wojtek", 40));
            BPP.NowyRekrut(new Major("Schaeffer", 200));
            BPP.NowyRekrut(new General("Rommel", 100));
            BPP.NowyRekrut(new Szeregowy("Ryan", 1));
            BPP.prezentuj_bron();

            out.writeObject(BPP); 
            out.close(); 
            file_out.close(); 

            BPP = null;
        }
        catch (IOException ex){ 
            System.out.println("Output Exception is caught"); 
            System.out.println(ex);
        } 

        System.out.println("\n\n");

        try{
            FileInputStream file_in = new FileInputStream (filename); 
            ObjectInputStream in = new ObjectInputStream (file_in); 

            BPP = (Armia)in.readObject(); 
            in.close(); 
            file_in.close(); 
            BPP.prezentuj_bron();
            BPP = null;
        }
        catch (IOException ex) { 
            System.out.println("Input Exception is caught"); 
            System.out.println(ex);
        } 

        catch (ClassNotFoundException ex) { 
            System.out.println("ClassNotFoundException is caught");
        }
    }
}
