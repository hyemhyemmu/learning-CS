import java.util.*;

public class Library<K, V> implements LibraryMap {
    private BinarySearchLibrary bookDatabase;
    private PopularityHeap popularBooks;
    private Map<String, User> users; // userId->user
    private Map<String, Integer> categoryStats; //category->count


    public Library() {
        bookDatabase = new BinarySearchLibrary<>();
        popularBooks = new PopularityHeap();
        users = new HashMap<>();
        categoryStats = new HashMap<>();
    }

    //basic methods
    @Override
    public void addBook(String isbn, Book book) {
        if (bookDatabase.containsKey(isbn))
            throw new IllegalArgumentException("The book already exist!");
        bookDatabase.put(isbn, book);
        String category = book.getCategory();
        int categoryTotal = categoryStats.getOrDefault(category, 0);
        categoryTotal++;
        categoryStats.put(category, categoryTotal);
        System.out.printf("%s added successfully!\n", book.getTitle());
    }

    @Override
    public void removeBook(String isbn, Book book) {
        if (!bookDatabase.containsKey(isbn)) throw new IllegalArgumentException("This book does not exist!");
        bookDatabase.remove(isbn);
        String category = book.getCategory();
        int categoryTotal = categoryStats.get(category);
        categoryTotal--;
        categoryStats.put(category, categoryTotal);
        System.out.printf("%s removed successfully!\n", book.getTitle());
    }

    @Override
    public void addUser(String name) {
        Random random = new Random();
        String userId = String.valueOf(random.nextInt(100));
        User newUser = new User(userId, name);
        users.put(userId, newUser);
        System.out.printf("%s added successfully!\n", name);
    }

    @Override
    public void removeUser(String userId) {
        User user = users.get(userId);
        if (user == null) throw new IllegalArgumentException("user does not exist!");
        if (!user.isCurrentBorrowsEmpty()) throw new IllegalStateException("User has unreturned books");
        users.remove(userId);
    }

    //borrow related methods
    @Override
    public BorrowRecord borrowBook(String userId, String isbn) {
        User user = users.get(userId);
        Book book = bookDatabase.get(isbn);
        if (user == null || book == null)
            throw new IllegalArgumentException("user or book does not exist!");
        if (!user.canBorrow() || !book.isAvailable()) {
            throw new IllegalStateException("Cannot borrow: user limit reached or book unavailable");
        }
        BorrowRecord record = new BorrowRecord(isbn, userId);
        user.addBorrowRecord(record);
        book.setAvailable(false);
        book.incrementBorrowCount();
        //see if it is popular enough
        popularBooks.insert(book);
        return record;
    }

    @Override
    public void returnBook(String userId, String isbn) {
        User user = users.get(userId);
        Book book = bookDatabase.get(isbn);
        if (user == null || book == null)
            throw new IllegalArgumentException("user or book does not exist!");
        if (!user.hasBorrowed(isbn))
            throw new IllegalArgumentException("user didn't borrow this book!");
        //return
        user.returnBook(isbn);
        book.setAvailable(true);
    }

    @Override
    public void renewBook(String userId, String isbn) {
        User user = users.get(userId);
        Book book = bookDatabase.get(isbn);
        if (user == null || book == null)
            throw new IllegalArgumentException("user or book does not exist!");
        if (!user.hasBorrowed(isbn))
            throw new IllegalArgumentException("user didn't borrow this book!");
        BorrowRecord record = user.getBorrowRecord(isbn);
        record.renew();
    }

    @Override
    public Set<Book> searchBooks(String keyword, String searchType) {
        return switch (searchType.toLowerCase()) {
            case "title" -> bookDatabase.searchByTitle(keyword);
            case "author" -> bookDatabase.searchByAuthor(keyword);
            case "category" -> bookDatabase.searchByCategory(keyword);
            case "combined" -> {
                //need one more argument here
                Scanner scanner = new Scanner(System.in);
                System.out.print("Enter category: ");
                String category = scanner.nextLine();
                yield bookDatabase.searchCombined(keyword, category);
            }
            default -> throw new IllegalArgumentException("Unknown search type: " + searchType);
        };
    }

    @Override
    public List getPopularBooks(int k) {
        return popularBooks.getTopK(k);
    }

    @Override
    public List<BorrowRecord> getOverdueBooks(){
        List<BorrowRecord> overdueRecords = new ArrayList<>();
        for (User user: users.values()){
            for (BorrowRecord record:user.getBorrowRecord()){
                if (record.isOverdue())
                    overdueRecords.add(record);
            }
        }
        return overdueRecords;
    }

    @Override
    public List<BorrowRecord> getUserBorrowHistory(String userId){
        User user = users.get(userId);
        if (user==null)
            throw new IllegalArgumentException("user does not exist!");
        return user.getBorrowHistory();
    }

    @Override
    public Map<String, Integer> getCategoryStatistics() {
        return new HashMap<>(categoryStats);
    }


    @Override
    public Map<String, Integer> getAvailabilityStatistics() {
        Map<String, Integer> stats = new HashMap<>();
        stats.put("total", bookDatabase.size());
        int count=0;
        for (Object isbn:bookDatabase.keySet()){
            if (bookDatabase.get((Comparable) isbn).isAvailable())
                count++;
        }
        stats.put("available",count);
        return stats;
    }

    @Override
    public Book getBook(String isbn) {
        Book book=bookDatabase.get(isbn);
        if (book==null)
            throw new IllegalArgumentException("book not exist!");
        return book;
    }

    @Override
    public User getUser(String userId) {
        User user=users.get(userId);
        if (user==null)
            throw new IllegalArgumentException("user not exist!");
        return user;
    }

    @Override
    public int getTotalBooks() {
        return bookDatabase.size();
    }

    @Override
    public int getTotalUsers() {
        return users.size();
    }


}
