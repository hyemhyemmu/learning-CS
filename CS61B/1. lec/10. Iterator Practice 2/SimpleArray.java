import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class SimpleArray<T> implements Iterable<T> {
    private static final int INITIAL_CAPACITY = 10;
    private Object[] elements;
    private int size;
    private int modCount;

    public SimpleArray() {
        elements = new Object[INITIAL_CAPACITY];
        size = 0;
        modCount = 0;
    }

    public void add(T element) {
        if (size == elements.length) {
            Object[] newElements = new Object[elements.length * 2];
            System.arraycopy(elements, 0, newElements, 0, elements.length);
            elements = newElements;
        }
        elements[size++] = element;
        modCount++;
    }

    @Override
    public Iterator<T> iterator() {
        return new SimpleArrayIterator();
    }

    private class SimpleArrayIterator implements Iterator<T> {
        private int cursor;
        private int expectedModCount;
        private int lastRet = -1;

        SimpleArrayIterator() {
            cursor = 0;
            expectedModCount = modCount;
        }

        @Override
        public boolean hasNext() {
            return cursor < size;
        }

        @SuppressWarnings("unchecked")
        @Override
        public T next() {
            checkForComodification();
            if (cursor >= size) {
                throw new NoSuchElementException();
            }
            lastRet = cursor;
            return (T) elements[cursor++];
        }

        @Override
        public void remove() {
            if (lastRet < 0) {
                throw new IllegalStateException();
            }
            checkForComodification();

            System.arraycopy(elements, lastRet + 1, elements, lastRet, size - lastRet - 1);
            elements[--size] = null;
            cursor = lastRet;
            lastRet = -1;
            expectedModCount = ++modCount;
        }

        private void checkForComodification() {
            if (modCount != expectedModCount) {
                throw new ConcurrentModificationException();
            }
        }
    }
}

// Usage example
class main {
    public static void main(String[] args) {
        SimpleArray<String> array = new SimpleArray<>();
        array.add("First");
        array.add("Second");
        array.add("Third");

        Iterator<String> iterator = array.iterator();
        while (iterator.hasNext()) {
            String element = iterator.next();
            if (element.equals("Second")) {
                iterator.remove();
            }
        }

        // Print remaining elements
        for (String element : array) {
            System.out.println(element);
        }
    }
}