import java.util.ArrayList;
import java.util.List;

public class PopularityHeap<T extends Comparable<T>> {
    private static final int INITIAL_CAPACITY = 8;
    private T[] heap;
    private int size;

    @SuppressWarnings("unchecked")
    public PopularityHeap() {
        heap = (T[]) new Comparable[INITIAL_CAPACITY];
        size = 0;
    }

    public void insert(T item) {
        checkCapacity();
        if (item == null)
            throw new NullPointerException("input item can't be null!");
        heap[size] = item;
        bubbleUp(size);
        size++;
    }

    private void bubbleUp(int index) {
        while (index > 0) {
            int parentIdx = parent(index);
            if (heap[parentIdx].compareTo(heap[index]) >= 0) break;
            swap(parentIdx, index);
            index = parentIdx;
        }
    }

    private void bubbleDown(int index) {
        while (true) {
            int leftIdx = leftChild(index);
            int rightIdx = rightChild(index);
            if (leftIdx >= size) break;

            int biggerIdx = leftIdx;
            if (rightIdx <= size && heap[rightIdx].compareTo(heap[leftIdx]) > 0)
                biggerIdx = rightIdx;
            if (heap[index].compareTo(heap[biggerIdx]) > 0) break;

            swap(index, biggerIdx);
            index = biggerIdx;
        }
    }

    public T delMax() {
        if (size == 0) return null;
        T max = heap[0];
        heap[0] = heap[size - 1];
        heap[size - 1] = null;
        bubbleDown(0);
        size--;
        return max;
    }

    public List<T> getTopK(int k) {
        // we can't simply iterate over the list because it may not guarantee to be in order
        if (k < 0) throw new IllegalArgumentException("K can't be negative!");
        List<T> result = new ArrayList<>();
        PopularityHeap<T> copy = new PopularityHeap<>();
        for (int i = 0; i < size; i++) {
            copy.insert(heap[i]);
        }
        for (int i = 0; i < k; i++) {
            result.add(copy.delMax());
        }
        return result;
    }

    @SuppressWarnings("unchecked")
    private void checkCapacity() {
        if (size == heap.length) {
            T[] newHeap = (T[]) new Comparable[heap.length * 2];
            System.arraycopy(heap, 0, newHeap, 0, heap.length);
            heap = newHeap;
        }
    }

    /**
     * Returns the index of the parent node.
     *
     * @param index Current node's index
     * @return Parent node's index
     */
    private int parent(int index) {
        return (index - 1) / 2; // Fix the parent index for 0-based array
    }

    /**
     * Returns the index of the left child.
     *
     * @param index Current node's index
     * @return Left child's index
     */
    private int leftChild(int index) {
        return 2 * index + 1; // Correct left child index for 0-based array
    }

    /**
     * Returns the index of the right child.
     *
     * @param index Current node's index
     * @return Right child's index
     */
    private int rightChild(int index) {
        return 2 * index + 2; // Correct right child index for 0-based array
    }

    /**
     * Swaps two elements in the heap.
     *
     * @param i Index of first element
     * @param j Index of second element
     */
    private void swap(int i, int j) {
        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

}