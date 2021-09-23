import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class In_Out {
    public static void save_figura(Object obj, String filename){
        try{
            FileOutputStream file_out = new FileOutputStream(filename);
            ObjectOutputStream out = new ObjectOutputStream(file_out);

            out.writeObject(obj);

            out.close();
            file_out.close();

            System.out.println("Objekt został zapisany");
        }
        catch(IOException ex){
            System.out.println("Error: Nie można zapisać obiektu");
            System.out.println(ex);
        }
    }

    public static Object read_figura(String filename){
        try{
            FileInputStream file_in = new FileInputStream(filename);
            ObjectInputStream in = new ObjectInputStream(file_in);

            Object output = in.readObject();

            System.out.println("Obiekt został wczytany");

            in.close();
            file_in.close();

            return output;
        }
        catch(IOException ex){
            System.out.println("Nie można wczytać obiektu");
        }

        catch(ClassNotFoundException ex){
            System.out.println("Nie znaleziono klasy");
        }
        return null;
    }


}
