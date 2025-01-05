import java.util.Set;
import java.util.List;

public interface LibraryMap<K, V> extends Iterable<K> {
    // 基本操作
    void put(K key, V value);
    V get(K key);
    boolean containsKey(K key);
    int size();
    void clear();
    Set<K> keySet();
    V remove(K key);



    // 图书查询操作
    Set<V> searchByISBN(String isbn);
    Set<V> searchByCategory(String category);
    Set<V> searchByAuthor(String author);
    Set<V> searchByTitle(String titlePart);
    Set<V> searchCombined(String author, String category);
    List<V> getTopBorrowed(int k);  // 获取借阅次数最多的k本书

    // 借阅相关操作
    boolean borrowBook(String isbn, String userId);
    boolean returnBook(String isbn, String userId);
    boolean renewBook(String isbn, String userId);
}