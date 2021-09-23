import java.io.File;

public class Main
{
    public static void main(String[] args)
    {
        if (args.length != 2)
        {
            System.out.println("Bledna liczba argumentow. Oczekiwano 2");
            return;
        }
        String file = args[0];
        String type = args[1];
        
        if(!type.equals("Okrag") && !type.equals("Trojkat"))
        {
            System.out.println("Nieznana klasa: "+type);
            System.exit(1);
        }
        if(!file.endsWith(".ser"))
        {
            System.out.println("Bledne rozszerzenie pliku: "+file);
            System.exit(1);
        }

        
        File newFile = new File(file);
        
        if(newFile.length() == 0)
        {
            if(type.equals("Okrag"))
            {
                Okrag o = new Okrag(0.0);
                In_Out.save_figura(o, file);
            }
            else
            {
                Trojkat t = new Trojkat(0.0, 0.0, 0.0);
                In_Out.save_figura(t, file);
            }
        }
        Figura k = (Figura)In_Out.read_figura(file);
        if(type.equals("Trojkat")  && k instanceof Okrag)
        {
            Trojkat t = new Trojkat(0.0, 0.0, 0.0);
            In_Out.save_figura(t, file);
        }
        if(type.equals("Okrag") && k instanceof Trojkat)
        {
            Okrag o = new Okrag(0.0);
            In_Out.save_figura(o, file);
        }

        new GUI(file, type);
    }
}