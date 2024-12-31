package src;

import java.lang.Math;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class ArrayDeque61B<T> implements Deque61B<T> {
    private T[] lst;
    public static final int DEFAULT_SIZE = 8;
    private int capacity;
    private int size;
    private int front;
    private int back;


    //constructor
    @SuppressWarnings("unchecked")
    public ArrayDeque61B() {
        lst = (T[]) new Object[DEFAULT_SIZE];
        capacity = DEFAULT_SIZE;
        size = 0;
        front = 0;
        back = 0;
    }


    /**
     * in case the array is full, and we may need to resize it.
     */
    @SuppressWarnings("unchecked")
    public void checkCapacity() {
        if (size == capacity) {
            int newCapacity = capacity * 2;
            T[] temp = (T[]) new Object[newCapacity];
            for (int i = 0; i < size; i++) {
                temp[i] = lst[Math.floorMod(front + i, capacity)];
            }
            capacity = newCapacity;
            lst = temp;
            front = 0;
            back = size;
        }
    }


    @Override
    public void addFirst(T x) {
        this.checkCapacity();
        //index of front if one element is added
        front = Math.floorMod(front - 1, capacity);
        lst[front] = x;
        size++;

    }

    @Override
    public void addLast(T x) {
        checkCapacity();
        lst[back] = x;
        back = Math.floorMod(back + 1, capacity);
        size++;
    }

    @Override
    public List<T> toList() {
        List<T> returnList = new ArrayList<>();
        if (size == 0)
            return returnList;
        for (int i = 0; i < size; i++)
            returnList.add(lst[Math.floorMod(front + i, capacity)]);
        return returnList;
    }

    @Override
    public boolean isEmpty() {
        return (size == 0);
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public T removeFirst() {
        if (size == 0)
            return null;
        T removed = lst[front];
        lst[front] = null;
        front = Math.floorMod(front + 1, capacity);
        size--;
        return removed;
    }

    @Override
    public T removeLast() {
        if (size == 0)
            return null;
        back = Math.floorMod(back - 1, capacity);
        T removed = lst[back];
        lst[back] = null;
        size--;
        return removed;
    }

    @Override
    public T get(int index) {
        if (index < 0 || index >= size) {
            return null;
        }
        return lst[(front + index) % capacity];
    }

    @Override
    public T getRecursive(int index) {
        if (index < 0 || index >= size) {
            return null;
        }
        return getRecursiveHelper(index, front);
    }

    private T getRecursiveHelper(int index, int currentIndex) {
        if (index == 0) {
            return lst[currentIndex];
        }
        int nextIndex = Math.floorMod(currentIndex + 1, capacity);
        return getRecursiveHelper(index - 1, nextIndex);
    }

    @Override
    public Iterator<T> iterator() {
        return new ArraySetIterator();
    }

    @SuppressWarnings("unchecked")
    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other instanceof ArrayDeque61B<?> otherSet) {
            //check the size
            if (this.size != otherSet.size) {
                return false;
            }
            //check every element
            int thisIndex = this.front;
            int otherIndex = otherSet.front;
            for (int i = 0; i < this.size; i++) {
                T thisElement = this.lst[Math.floorMod(thisIndex, this.capacity)];
                T otherElement = (T) otherSet.lst[Math.floorMod(otherIndex, otherSet.capacity)];
                if (!Objects.equals(thisElement, otherElement)) {
                    return false;
                }
                thisIndex++;
                otherIndex++;
            }
            return true;
        }

        return false;
    }


    private class ArraySetIterator implements Iterator<T> {
        private int pos;

        ArraySetIterator() {
            pos = 0;
        }

        @Override
        public boolean hasNext() {
            return pos < size;
        }

        @Override
        public T next() {
            T returnItem = lst[Math.floorMod(front + pos, capacity)];
            pos++;
            return returnItem;
        }
    }

    @Override
    public String toString() {
        return toList().toString();
    }

    public static void main(String[] args) {
        Deque61B<String> lld1 = new LinkedListDeque61B<>();

        lld1.addLast("front");
        lld1.addLast("middle");
        lld1.addLast("back");

        System.out.println(lld1);

    }


}
