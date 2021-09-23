import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JSeparator;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class GUI implements ActionListener {
    String filename;
    String type;
    private JLabel label;
    private JFrame frame;
    private JPanel panel;
    private JLabel wynik;
    private JButton button1;
    private JButton button2;
    private JTextField bok1;
    private JTextField bok2;
    private JTextField bok3;

    public GUI(String file, String t) 
    {
        filename = file;
        type = t;
        frame = new JFrame();
        frame.setSize(600, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setTitle("Edycja obiektu " + type);

        panel = new JPanel();
        frame.add(panel);
        panel.setLayout(null);


        if(type.equals("Trojkat"))
        {
            
            Trojkat tr = (Trojkat)In_Out.read_figura(filename);
            label = new JLabel("Edytuj boki trojkata ponizej a nastepnie zatwierdz przyciekiem:");
            label.setBounds(10, 10, 700, 50);
            panel.add(label);
    
            bok1 = new JTextField(tr.bok1.toString());
            bok1.setBounds(10, 60, 30, 30);
            panel.add(bok1);
    
            bok2 = new JTextField(tr.bok2.toString());
            bok2.setBounds(50, 60, 30, 30);
            panel.add(bok2);
    
            bok3 = new JTextField(tr.bok3.toString());
            bok3.setBounds(90, 60, 30, 30);
            panel.add(bok3);
    
            button1 = new JButton("Save Trojkat");
            button1.setBounds(10, 100, 200, 30);
            panel.add(button1);
            button1.addActionListener(this);
            
            wynik = new JLabel("");
            wynik.setBounds(10, 140, 700, 50);
            panel.add(wynik);
        }
        else
        {
            Okrag o = (Okrag)In_Out.read_figura(filename);
            label = new JLabel("Edytuj promien okregu ponizej a nastepnie zatwierdz przyciekiem:");
            label.setBounds(10, 10, 700, 50);
            panel.add(label);
    
            bok1 = new JTextField(o.get_promien().toString());
            bok1.setBounds(10, 60, 30, 30);
            panel.add(bok1);
    
            button2 = new JButton("Save Okrag");
            button2.setBounds(10, 100, 200, 30);
            panel.add(button2);
            button2.addActionListener(this);
            
            wynik = new JLabel("");
            wynik.setBounds(10, 140, 700, 50);
            panel.add(wynik);
        }
        
        JSeparator separator = new JSeparator(JSeparator.HORIZONTAL);
        separator.setBounds(0, 188, 600, 4);
        panel.add(separator);

        frame.setVisible(true);

    }

    public static boolean isNumeric(String str) 
    {
        return str.matches("-?\\d+(\\.\\d+)?");
    }

    @Override
    public void actionPerformed(ActionEvent e) 
    {
        if (e.getSource() == button1) 
        {
            String s1 = bok1.getText();
            String s2 = bok2.getText();
            String s3 = bok3.getText();
            if(isNumeric(s1) && isNumeric(s2) && isNumeric(s3))
            {
                Double a = Double.parseDouble(s1);
                Double b = Double.parseDouble(s2);
                Double c = Double.parseDouble(s3);
                Trojkat t = new Trojkat(a, b, c);
                wynik.setText(t.toString());
                In_Out.save_figura(t, filename);

            }
            else
            {
                wynik.setText("Niepoprawne Dane");

            }
    
        }
        else if (e.getSource() == button2) 
        {
            String s1 = bok1.getText();
            if(isNumeric(s1))
            {
                Double r = Double.parseDouble(s1);
                Okrag o = new Okrag(r);
                wynik.setText(o.toString());
                In_Out.save_figura(o, filename);
            }
            else
            {
                wynik.setText("Niepoprawne Dane");
            }
        }
    }
}