import java.util.ArrayList;
import java.util.List;
import java.io.*; 
import java.util.*;


public class Armia<Szeregowy> implements Collection<Szeregowy>, Iterable<Szeregowy>
{


    class IterArmia implements Iterator<Szeregowy>
    {
        private Integer index = 0;
        
        public boolean hasNext() {
            return index < size();
        }

        public Szeregowy next() {
            return jednostki.get(index++);
        }
        
        public void remove() {
            throw new UnsupportedOperationException("not supported yet");
        }

    }

    private List<Szeregowy> jednostki = new ArrayList<Szeregowy>();

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
        do_szeregu();
        jednostki.add(mieso);
    }

    //Pawel
    public boolean add(Szeregowy o){
        
        return jednostki.add(o);        
    }
    //Pawel
    public boolean addAll(Collection c){
    return jednostki.addAll(c); 

    }
    //Pawel
    public void clear() {
    jednostki.clear();
    }
    //Pawel
    public boolean contains(Object o){
    return jednostki.contains(o);

    }

    public boolean removeAll(Collection c)
    {
        return jednostki.removeAll(c);
    }

    public boolean remove(Object o)
    {
        return jednostki.remove(o);
    }

    //Ola
    public boolean containsAll(Collection<?> o){
        return jednostki.containsAll(o);
    }

    public boolean equals(Object c){
    return jednostki.equals(c);
    }

    public int hashcode(){
    return jednostki.hashCode();
    }

    public boolean isEmpty(){
    return jednostki.isEmpty();
    }


    //Herr Troska
    public Iterator<Szeregowy> iterator(){
        //System.out.println("public Iterator<Szeregowy> iterator();");
        return new IterArmia();
    }

    public boolean retainAll(Collection o){
        return jednostki.retainAll(o); 
    }

    // Czarek
    public int size(){
        return jednostki.size(); 
    }
    // Czarek
    public Object[] toArray(){
        return jednostki.toArray();
    }
    // Czarek
    public <Object> Object[] toArray(Object[] a){
        return jednostki.toArray(a); 
    }
}