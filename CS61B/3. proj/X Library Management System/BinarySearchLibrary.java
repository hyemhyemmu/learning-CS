import java.util.*;
import java.util.function.Predicate;

public class BinarySearchLibrary<K extends Comparable<K>, V extends Book> implements BSLibraryMap<K, V> {
    private Node root;
    private int size;

    public BinarySearchLibrary() {
        root = null;
        size = 0;
    }

    @Override
    public void put(K key, V value) {
        if (key == null || value == null)
            throw new IllegalArgumentException("input can not be null!");
        root = put(root, key, value);
    }

    private Node put(Node node, K key, V value) {
        if (node == null) {
            node = new Node(key, value);
            size++;
        } else if (key.compareTo(node.key) > 0) {
            node.right = put(node.right, key, value);
        } else if (key.compareTo(node.key) < 0) {
            node.left = put(node.left, key, value);
        } else {
            node.value = value;
        }
        return node;
    }


    @Override
    public V get(K key) {
        if (key == null)
            throw new IllegalArgumentException("key can not be null!");
        Node node = get(root, key);
        //there may be case that we couldn't find the item
        return node == null ? null : node.value;
    }


    private Node get(Node node, K key) {
        if (node == null)
            return null;//can't find the book
        if (key.compareTo(node.key) > 0) {
            return get(node.right, key);
        } else if (key.compareTo(node.key) < 0) {
            return get(node.left, key);
        } else {
            return node;
        }
    }


    @Override
    public boolean containsKey(K key) {
        return get(key) != null;
    }

    @Override
    public int size() {
        return size(root);
    }

    // I try to take every care to make sure that it won't throw null out
    private int size(Node node) {
        return node == null ? 0 : node.size;
    }

    @Override
    public void clear() {
        root = null;
    }

    @Override
    public Set<K> keySet() {
        Set<K> keys = new TreeSet<>();
        if (size == 0)
            return keys;
        keyCollector(root, keys);
        return keys;
    }

    private void keyCollector(Node node, Set<K> keys) {
        //order: left,self,right
        if (node == null) return;
        keyCollector(node.left, keys);
        keys.add(node.key);
        keyCollector(node.right, keys);
    }

    @Override
    public V remove(K key) {
        if (key == null)
            throw new IllegalArgumentException("key can not be null!");
        V value = get(key);
        if (value != null)
            root = remove(root, key);
        size--;
        return value;
    }


    private Node remove(Node node, K key) {
        //find it
        if (node == null)
            return null;//can't find it
        int cmp = key.compareTo(node.key);
        if (cmp > 0) {
            node.right = remove(node.right, key);
        } else if (cmp < 0) {
            node.left = remove(node.left, key);
        }
        //process
        else {
            //when have only one child
            if (node.left == null) return node.right;
            if (node.right == null) return node.left;
            //two child -> take the smallest from the right as successor
            Node oriNode = node;
            node = min(oriNode.right);
            node.right = deleteMin(oriNode.right);
            node.left = oriNode.left;
        }
        return node;
    }

    private Node min(Node node) {
        //only return those that needs to be returned and ignore those need to be deleted
        // if not returned, will automatically recognize it as gone
        if (node.left == null) return node;
        return min(node.left);
    }

    private Node deleteMin(Node node) {
        if (node.left == null) return node.right;
        node.left = deleteMin(node.left);
        return node;
    }

    @Override
    public Set<V> searchByISBN(String isbn) {
        return searchByPredicate(book -> isbn.equals(book.getIsbn()));
    }

    @Override
    public Set<V> searchByCategory(String category) {
        return searchByPredicate(book -> category.equals(book.getCategory()));
    }

    //allow partly match
    @Override
    public Set<V> searchByAuthor(String author) {
        return searchByPredicate(book -> book.getAuthor().contains(author));
    }

    @Override
    public Set<V> searchByTitle(String titlePart) {
        return searchByPredicate(book -> book.getTitle().contains(titlePart));
    }

    @Override
    public Set<V> searchCombined(String author, String category) {
        return searchByPredicate(book -> book.getAuthor().contains(author) && category.equals(book.getCategory()));
    }


    public Set<V> searchByPredicate(Predicate<V> predicate) {
        //we don't care about order, but we do care about efficiency, that's why I choose hashset
        Set<V> result = new HashSet<>();
        searchByPredicate(root, predicate, result);
        return result;
    }

    private void searchByPredicate(Node node, Predicate<V> predicate, Set<V> result) {
        //not found
        if (node == null) return;
        //inorder traverse
        searchByPredicate(node.left, predicate, result);
        if (predicate.test(node.value))
            result.add(node.value);
        searchByPredicate(node.right, predicate, result);
    }


    //return list of top k most borrowed books
    @Override
    public List<V> getTopBorrowed(int k) {
        List<V> allBooks = new ArrayList<>();
        collectBooks(root, allBooks);
        allBooks.sort((v1,v2)->{
            if (v1 != null && v2 != null){
                return (((Book)v2).getBorrowCount()-((Book)v1).getBorrowCount());
            }
            return 0;
        });
        // careful! list may not have k items!
        return allBooks.subList(0,Math.min(k, allBooks.size()));
    }

    private void collectBooks(Node node, List<V> allBooks) {
        if (node==null) return;
        collectBooks(node.left,allBooks);
        allBooks.add(node.value);
        collectBooks(node.right,allBooks);
    }


    @Override
    public Iterator<K> iterator() {
        return keySet().iterator();
    }


    private class Node {
        K key;
        V value;
        Node left;
        Node right;
        int size;  // 子树大小

        Node(K key, V value) {
            this.key = key;
            this.value = value;
            this.size = 1;
        }
    }
}