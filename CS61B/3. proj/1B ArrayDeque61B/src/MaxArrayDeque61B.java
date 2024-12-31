package src;

import java.util.Comparator;
import java.util.Iterator;

public class MaxArrayDeque61B<T> extends ArrayDeque61B{
    private Comparator<T> comparator;

    //constructor
    public MaxArrayDeque61B(Comparator<T> c){
        super();
        this.comparator=c;

    }

    public T max(){
        if (this.size()==0){return null;}
        T maxElement = null;
        Iterator<T> iterator = this.iterator();
        while (iterator.hasNext()) {
            T current = iterator.next();
            if (maxElement == null || comparator.compare(current, maxElement) > 0) {
                maxElement = current;
            }
        }
        return maxElement;

    }

    // Method to find the maximum element using a given comparator
    public T max(Comparator<T> c) {
        if (this.size() == 0) {
            return null;
        }
        T maxElement = null;
        Iterator<T> iterator = this.iterator();
        while (iterator.hasNext()) {
            T current = iterator.next();
            if (maxElement == null || c.compare(current, maxElement) > 0) {
                maxElement = current;
            }
        }
        return maxElement;
    }
}
