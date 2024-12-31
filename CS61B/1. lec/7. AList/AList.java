import java.util.ArrayList;

/**
 * This is a fill in the blanks version of the SLList class
 * in case you want to try to figure out how to write it yourself.
 * After writing your methods, you can run the AListTest file.
 */
public class AList<T> { //type of parameter is T so that we can put in any data we want when declaring
    /**
     * Creates an empty list.
     */
    private int size; //set to private cuz we don't want it to be modified.
    private T[] items;
    public static final int DEFAULT_INC = 10;
    public static final int DEFAULT_LENGTH = 8;
    public int capacity;

    public AList() {
        //awkward syntax...
        items = (T[]) new Object[DEFAULT_LENGTH];
        size = 0;
        capacity = DEFAULT_LENGTH;
    }

    /**
     * Resize the List when needed
     */
    public void Resize() {
        T[] new_lst = (T[]) new Object[capacity + DEFAULT_INC];
        System.arraycopy(items, 0, new_lst, 0, capacity);
        capacity += DEFAULT_INC;
        items = new_lst; //reassigned the pointer so that we can process steps after this
    }

    /**
     * Inserts X into the back of the list.
     */
    public void addLast(T x) {
        //first we need to check whether if capacity full.
        if (size == capacity)
            this.Resize();
        items[size] = x;
        size++;
    }

    /**
     * Returns the item from the back of the list.
     */
    public T getLast() {
        if (size==0)
            return null;
        return items[size-1];
    }

    /**
     * Gets the ith item in the list (0 is the front).
     */
    public T get(int i) {
        return items[i];
    }

    /**
     * Returns the number of items in the list.
     */
    public int size() {
        return this.size;
    }

    /**
     * Deletes item from back of the list and
     * returns deleted item.
     */
    public T removeLast() {
        T removed=this.getLast();
        items[size]=null;
        size--;
        return removed;
    }
} 