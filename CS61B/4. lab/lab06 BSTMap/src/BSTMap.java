package src;
import java.util.*;

public class BSTMap<K extends Comparable<K>, V> implements Map61B<K, V> {
    //root
    private BSTNode root;
    private int size = 0;

    //initialize the node
    private class BSTNode {
        K key;
        V value;
        BSTNode left;
        BSTNode right;

        BSTNode(K key, V value) {
            this.key = key;
            this.value = value;
            left = null;
            right = null;
        }
    }


    @Override
    public void put(K key, V value) {
        if (key == null)
            throw new IllegalArgumentException("key can not be null!");
        root = put_helper(root, key, value);
    }

    //helper function
    private BSTNode put_helper(BSTNode node, K key, V value) {
        if (node == null) {
            size++;
            return new BSTNode(key, value);
        }
        int cmp = key.compareTo(node.key);
        if (cmp < 0) {
            node.left = put_helper(node.left, key, value);
        } else if (cmp > 0) {
            node.right = put_helper(node.right, key, value);
        } else {
            node.value = value;
        }
        return node;
    }

    @Override
    public V get(K key) {
        if (key == null)
            throw new IllegalArgumentException("key can not be null!");
        return get_helper(root, key);
    }

    private V get_helper(BSTNode node, K key) {
        if (node == null) // Return null if node is null to prevent NullPointerException
            return null;
        int cmp = key.compareTo(node.key);
        if (cmp < 0)
            return get_helper(node.left, key);
        else if (cmp > 0)
            return get_helper(node.right, key);
        else
            return node.value;
    }

    @Override
    public boolean containsKey(K key) {
        //a common pitfall: return get(key) != null; this won't work well when value is null
        if (key == null)
            throw new IllegalArgumentException("key can not be null!");
        return containsKey_helper(root, key);
    }

    private boolean containsKey_helper(BSTNode node, K key) {
        if (node == null)
            return false;
        int cmp = node.key.compareTo(key);
        if (cmp < 0)
            return containsKey_helper(node.left, key);
        else if (cmp > 0)
            return containsKey_helper(node.right, key);
        else
            return true;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    @Override
    public Set<K> keySet() {
        Set<K> set = new HashSet<>();
        collectKeys(root, set); // Collect all keys into a HashSet
        return set;
    }

    private void collectKeys(BSTNode node, Set<K> set) {
        if (node != null) {
            set.add(node.key);
            collectKeys(node.left, set);
            collectKeys(node.right, set);
        }
    }

    @Override
    public V remove(K key) {
        if (key == null)
            throw new IllegalArgumentException("key can not be null!");
        //find the key
        BSTNode parent = null;
        BSTNode current = root;
        // Find the node to remove
        while (current != null) {
            int cmp = key.compareTo(current.key);
            if (cmp < 0) {
                parent = current;
                current = current.left;
            } else if (cmp > 0) {
                parent = current;
                current = current.right;
            } else {
                break;
            }
        }

        if (current == null)
            return null; //can't find the key
        V value = current.value;
        //case1: no child
        if (current.left == null && current.right == null) {
            if (parent == null)
                root = null;
            else {
                int cmp2 = current.key.compareTo(parent.key);
                if (cmp2 < 0)
                    parent.left = null;
                else
                    parent.right = null;
            }
            size--;
        }
        //case2: 1 child
        else if (current.left == null) {
            if (parent == null)
                root = current.right;
            if (parent.left == current)
                parent.left = current.right;
            else
                parent.right = current.right;
            size--;
        } else if (current.right == null) {
            if (parent == null)
                root = current.right;
            if (parent.right == current)
                parent.right = current.left;
            else parent.left = current.left;
            size--;
        }
        //case3: 2 child
        else {
            BSTNode successor = findMin(current.right);
            //remove and get successor's value
            V successorValue = remove(successor.key);
            current.key = successor.key;
            ;
            current.value = successorValue;
        }
        return value;
    }

    private BSTNode findMin(BSTNode node) {
        while (node.left != null)
            node = node.left;
        return node;
    }


    /**
     * iterates over the keys of the BST
     */
    @Override
    public Iterator<K> iterator() {
        return new BSTIterator();
    }

    private class BSTIterator implements Iterator<K> {
        private Stack<BSTNode> stack = new Stack<>();

        BSTIterator() {
            pushLeft(root);
        }

        private void pushLeft(BSTNode node) {
            while (node != null) {
                stack.push(node);
                node = node.left;
            }
        }

        @Override
        public boolean hasNext() {
            return !stack.isEmpty();
        }

        @Override
        public K next() {
            if (!hasNext())
                throw new NoSuchElementException();
            BSTNode popped_node = stack.pop();
            pushLeft(popped_node.right);
            return popped_node.key;
        }
    }
}