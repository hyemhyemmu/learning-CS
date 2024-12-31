package src;

import java.lang.Math;
import java.util.ArrayList;
import java.util.List;

public class ArrayDeque61B<T> implements Deque61B<T> {
    private T[] lst;
    public static final int DEFAULT_SIZE = 8;
    public int capacity;
    public int size;
    public int front;
    public int back;


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
            System.arraycopy(lst, 0, temp, 0, size);
            capacity = newCapacity;
            lst = temp;
            front = 0;
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
        back = Math.floorMod(back + 1, capacity);
        lst[back] = x;
        size++;
    }

    @Override
    public List<T> toList() {
        List<T> returnList = new ArrayList<>();
        if (size == 0)
            return returnList;
        for (int i = 0; i < size; i++)
            returnList.add(lst[i]);
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
        return getRecursiveHelper(index, front);
    }

    private T getRecursiveHelper(int index, int currentIndex) {
        if (index == 0) {
            return lst[currentIndex];
        }
        // 否则递归调用，返回下一个位置的元素
        int nextIndex = Math.floorMod(currentIndex + 1, capacity);
        return getRecursiveHelper(index - 1, nextIndex);
    }

}
