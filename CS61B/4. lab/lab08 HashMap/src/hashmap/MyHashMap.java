package hashmap;

import edu.princeton.cs.algs4.In;

import java.util.*;

/**
 * A hash table-backed Map implementation.
 * <p>
 * Assumes null keys will never be inserted, and does not resize down upon remove().
 *
 * @author Fei Mo
 */
public class MyHashMap<K, V> implements src.hashmap.Map61B<K, V> {

    /**
     * Protected helper class to store key/value pairs
     * The protected qualifier allows subclass access
     */
    public class Node {
        K key;
        V value;

        Node(K k, V v) {
            key = k;
            value = v;
        }
    }

    /* Instance Variables */
    private Collection<Node>[] buckets;
    private int size;
    private int capacity;
    private static final int INITIAL_CAPACITY = 16;
    private static final double LOAD_FACTOR = 0.75;
    private double loadFactor;

    /**
     * Constructors
     */
    public MyHashMap() {
        size = 0;
        capacity = INITIAL_CAPACITY;
        loadFactor = LOAD_FACTOR;
        buckets = initializeBuckets(INITIAL_CAPACITY);
    }

    public MyHashMap(int initialCapacity) {
        size = 0;
        capacity = initialCapacity;
        loadFactor = LOAD_FACTOR;
        buckets = initializeBuckets(initialCapacity);
    }

    /**
     * MyHashMap constructor that creates a backing array of initialCapacity.
     * The load factor (# items / # buckets) should always be <= loadFactor
     *
     * @param initialCapacity initial size of backing array
     * @param loadFactor      maximum load factor
     */
    public MyHashMap(int initialCapacity, double loadFactor) {
        size = 0;
        capacity = initialCapacity;
        this.loadFactor = loadFactor;
        buckets = initializeBuckets(initialCapacity);
    }

    /**
     * Returns a data structure to be a hash table bucket
     * <p>
     * The only requirements of a hash table bucket are that we can:
     * 1. Insert items (`add` method)
     * 2. Remove items (`remove` method)
     * 3. Iterate through items (`iterator` method)
     * Note that that this is referring to the hash table bucket itself,
     * not the hash map itself.
     * <p>
     * Each of these methods is supported by java.util.Collection,
     * Most data structures in Java inherit from Collection, so we
     * can use almost any data structure as our buckets.
     * <p>
     * Override this method to use different data structures as
     * the underlying bucket type
     * <p>
     * BE SURE TO CALL THIS FACTORY METHOD INSTEAD OF CREATING YOUR
     * OWN BUCKET DATA STRUCTURES WITH THE NEW OPERATOR!
     */
    protected Collection<Node> createBucket() {
        return new LinkedList<>();
    }

    @SuppressWarnings("unchecked")
    private Collection<Node>[] initializeBuckets(int capacity) {
        Collection<Node>[] bucket = (Collection<Node>[]) new Collection[capacity];
        for (int i = 0; i < capacity; i++) {
            buckets[i] = createBucket();
        }
        return bucket;
    }

    private void checkCapacity() {
        int N = this.size;
        int M = this.capacity;
        if ((double) N / M >= this.loadFactor) {
            Collection<Node>[] newBucket = initializeBuckets(capacity *2);

            //reassign into new bucket
            for (Collection<Node> bucket : buckets) {
                for (Node node : bucket) {
                    int newIndex = Math.floorMod(node.key.hashCode(), capacity);
                    newBucket[newIndex].add(node);
                }
            }
            capacity = capacity * 2;
            buckets = newBucket;
        }
    }

    //methods from MAP61B interface
    @Override
    public void put(K key, V value) {
        if (key == null)
            throw new IllegalArgumentException("key cannot be null!");
        checkCapacity();
        Node node = new Node(key, value);
        int index = Math.floorMod(key.hashCode(), capacity);
        buckets[index].add(node);
        size++;
    }

    @Override
    public V get(K key) {
        if (key == null)
            throw new IllegalArgumentException("key cannot be null!");
        if (size == 0)
            return null;
        int index = Math.floorMod(key.hashCode(), capacity);
        for (Node node : buckets[index]) {
            if (node.key.equals(key)) {
                return node.value;
            }
        }
        return null;
    }

    @Override
    public boolean containsKey(K key) {
        if (key == null)
            throw new IllegalArgumentException("key cannot be null!");
        if (size == 0)
            return false;
        int index = Math.floorMod(key.hashCode(), capacity);
        for (Node node : buckets[index]) {
            if (node.key.equals(key)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void clear() {
        size = 0;
        capacity = INITIAL_CAPACITY;
        loadFactor = LOAD_FACTOR;
        buckets = initializeBuckets(INITIAL_CAPACITY);
    }

    @Override
    public Set<K> keySet() {
        Set<K> result = new HashSet<>();
        for (Collection<Node> bucket : buckets) {
            for (Node node : bucket) {
                result.add(node.key);
            }
        }
        return result;
    }

    @Override
    public V remove(K key) {
        if (key == null)
            throw new IllegalArgumentException("key cannot be null!");
        if (size == 0)
            return null;
        int index = Math.floorMod(key.hashCode(), capacity);
        for (Node node : buckets[index]) {
            if (node.key.equals(key)) {
                buckets[index].remove(node); // Correctly remove from the right bucket
                size--;
                return node.value;
            }
        }
        return null;
    }

    @Override
    public Iterator<K> iterator() {
        return keySet().iterator();
    }


}
