package src;

import java.util.ArrayList;

import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class LinkedListDeque61B<T> implements Deque61B<T> {
    //define class Node
    private class Node {
        T item;
        Node prev;
        Node next;

        //node constructor
        Node(Node prev, T item, Node next) {
            this.prev = prev;
            this.item = item;
            this.next = next;
        }

    }

    //users should not modify these elements
    private Node sentinel;
    private int size;

    //constructor - initialize
    public LinkedListDeque61B() {
        sentinel = new Node(null, null, null);
        sentinel.next = sentinel;
        sentinel.prev = sentinel;
        size = 0;
    }


    @Override
    public void addFirst(T x) {
        Node newNode = new Node(sentinel, x, sentinel.next);
        sentinel.next.prev = newNode;
        sentinel.next = newNode;
        size++;
    }

    @Override
    public void addLast(T x) {
        Node newNode = new Node(sentinel.prev, x, sentinel);
        sentinel.prev.next = newNode;
        sentinel.prev = newNode;
        size++;
    }

    @Override
    public List<T> toList() {
        ArrayList<T> returnList = new ArrayList<>();
        Node current = sentinel.next;

        while (current != sentinel) {
            returnList.add(current.item);
            current = current.next;
        }
        return returnList;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public T removeFirst() {
        if (isEmpty())
            return null;
        Node removed = sentinel.next;
        sentinel.next.next.prev = sentinel;
        sentinel.next = sentinel.next.next;
        size--;
        return removed.item;
    }

    @Override
    public T removeLast() {
        if (isEmpty())
            return null;
        Node removed = sentinel.prev;
        sentinel.prev.prev.next = sentinel;
        sentinel.prev = sentinel.prev.prev;
        size--;
        return removed.item;
    }

    @Override
    public T get(int index) {
        if (index < 0 || index > size) {
            return null;
        }
        Node current = sentinel.next;
        for (int i = 0; i < index; i++) {
            current = current.next;
        }
        return current.item;
    }

    @Override
    public T getRecursive(int index) {
        if (index < 0 || index >= size) { // 检查索引合法性
            return null;
        }
        return getRecursiveHelper(sentinel.next, index);
    }

    // 辅助递归方法
    private T getRecursiveHelper(Node current, int index) {
        if (index == 0) { // 基本情况：找到目标节点
            return current.item;
        }
        return getRecursiveHelper(current.next, index - 1);
    }

    @Override
    public Iterator<T> iterator() {
        return new LinkedListIterator();
    }

    private class LinkedListIterator implements Iterator<T> {
        private int pos;

        LinkedListIterator() {
            pos = 0;
        }

        @Override
        public boolean hasNext() {
            return pos < size;
        }

        @Override
        public T next() {
            T returnItem = get(pos);
            pos++;
            return returnItem;
        }

    }

    @SuppressWarnings("unchecked")
    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }
        if (other instanceof LinkedListDeque61B otherSet) {
            //check the size
            if (this.size != otherSet.size) {
                return false;
            }
            //check every element
            for (int i = 0; i < this.size; i++) {
                T thisElement = this.get(i);
                T otherElement = (T) otherSet.get(i);
                if (!Objects.equals(thisElement, otherElement)) {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    @Override
    public String toString() {
        return toList().toString();
    }


}
