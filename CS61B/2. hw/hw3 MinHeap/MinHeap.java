public class MinHeap<T extends Comparable<T>> {

    /* Array to store heap elements */
    private T[] heap;

    /* Current size of the heap */
    private int size;

    /* Default initial capacity */
    private static final int DEFAULT_CAPACITY = 10;


    /**
     * Creates an empty MinHeap with default capacity.
     */
    @SuppressWarnings("unchecked")
    public MinHeap() {
        heap = (T[]) new Comparable[DEFAULT_CAPACITY];
        size = 0;
    }

    /**
     * Creates an empty MinHeap with specified capacity.
     *
     * @param capacity Initial capacity of the heap
     */
    @SuppressWarnings("unchecked")
    public MinHeap(int capacity) {
        heap = (T[]) new Comparable[capacity];
        size = 0;
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

    /**
     * Ensures the heap has enough capacity.
     * Doubles the size of the array if necessary.
     */
    @SuppressWarnings("unchecked")
    private void ensureCapacity() {
        if (size == heap.length) {
            T[] newHeap = (T[]) new Comparable[heap.length * 2]; // Double the size
            System.arraycopy(heap, 0, newHeap, 0, heap.length);
            heap = newHeap;
        }
    }

    /**
     * Bubbles up the element at the given index to maintain heap property.
     *
     * @param index Index of the element to bubble up
     */
    private void bubbleUp(int index) {
        while (index > 0) {
            int parentIdx = parent(index);
            if (heap[parentIdx].compareTo(heap[index]) <= 0) {
                break;
            }
            swap(index, parentIdx);
            index = parentIdx;
        }
    }

    /**
     * Bubbles down the element at the given index to maintain heap property.
     *
     * @param index Index of the element to bubble down
     */
    private void bubbleDown(int index) {
        while (true) {
            int leftIdx = leftChild(index);
            int rightIdx = rightChild(index);

            // Check if both children are out of bounds
            if (leftIdx >= size) break;

            // Find the smaller child
            int smallerChildIdx = leftIdx;
            if (rightIdx < size && heap[rightIdx].compareTo(heap[leftIdx]) < 0) {
                smallerChildIdx = rightIdx;
            }

            // If the current node is smaller than the smallest child, we are done
            if (heap[index].compareTo(heap[smallerChildIdx]) <= 0) {
                break;
            }

            // Swap with the smaller child and continue
            swap(index, smallerChildIdx);
            index = smallerChildIdx;
        }
    }

    /**
     * Inserts a new element into the heap.
     *
     * @param item Element to insert
     */
    public void insert(T item) {
        if (item == null)
            throw new NullPointerException("input item can't be null!");
        ensureCapacity();
        heap[size] = item;
        bubbleUp(size);
        size++;
    }

    /**
     * Removes and returns the minimum element from the heap.
     *
     * @return The minimum element
     * @throws IllegalStateException if heap is empty
     */
    public T removeMin() {
        if (size == 0) {
            throw new IllegalStateException("Heap is empty");
        }
        T minItem = heap[0];  // Root is the minimum
        heap[0] = heap[size - 1]; // Move the last element to the root
        size--;
        if (size > 0) {
            bubbleDown(0); // Restore heap property
        }
        return minItem;
    }

    /**
     * Returns the minimum element without removing it.
     *
     * @return The minimum element
     * @throws IllegalStateException if heap is empty
     */
    public T peek() {
        if (size == 0) {
            throw new IllegalStateException("Heap is empty");
        }
        return heap[0];  // The root is always the minimum
    }

    /**
     * Returns the current size of the heap.
     *
     * @return Number of elements in the heap
     */
    public int size() {
        return size;
    }

    /**
     * Checks if the heap is empty.
     *
     * @return true if heap is empty, false otherwise
     */
    public boolean isEmpty() {
        return size == 0;
    }
}
