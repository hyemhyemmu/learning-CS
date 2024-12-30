package src.deque;

import java.util.ArrayList;

import javax.swing.*;
import java.util.List;

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
        sentinel.next.next.prev = sentinel;
        sentinel.next = sentinel.next.next;
        size--;
        return null;
    }

    @Override
    public T removeLast() {
        if (isEmpty())
            return null;
        sentinel.prev.prev.next = sentinel;
        sentinel.prev = sentinel.prev.prev;
        size--;
        return null;
    }

    @Override
    public T get(int index) {
        if (index <= 0 || index >= size) {
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
}
