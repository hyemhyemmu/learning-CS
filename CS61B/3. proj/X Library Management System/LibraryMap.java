import java.util.List;
import java.util.Map;
import java.util.Set;

public interface LibraryMap {
    //basic functions
    public void addBook(String isbn, Book book);
    public void removeBook(String isbn, Book book);
    public void addUser(String name);
    public void removeUser(String userId);

    //borrow related functions
    public BorrowRecord borrowBook(String userId, String isbn);
    public void returnBook(String userId, String isbn);
    public void renewBook(String userId, String isbn);

    //search functions
    public Set<Book> searchBooks(String query, String searchType);
    public List getPopularBooks(int k);
    public List<BorrowRecord> getOverdueBooks();
    public List<BorrowRecord> getUserBorrowHistory(String userId);

    //data methods
    public Map<String, Integer> getCategoryStatistics();
    public Map<String, Integer> getAvailabilityStatistics();

    //helper methods
    public Book getBook(String isbn);
    public User getUser(String userId);
    public int getTotalBooks();
    public int getTotalUsers();
}
