import java.time.LocalDate;

//borrow record per book per user
public class BorrowRecord {
    private String isbn;
    private String userId;
    private LocalDate borrowDate;
    private LocalDate dueDate;
    private LocalDate returnDate;
    private boolean renewed;
    private static final int BORROW_PERIOD_DAYS = 30;

    // constructor
    public BorrowRecord(String isbn, String userId) {
        this.isbn = isbn;
        this.userId = userId;
        borrowDate = LocalDate.now();
        dueDate = borrowDate.plusDays(BORROW_PERIOD_DAYS);
        renewed = false;
        returnDate = null;
    }

    //check if the book is already due
    public boolean isOverdue() {
        if (returnDate != null)
            return returnDate.isAfter(dueDate);
        return LocalDate.now().isAfter(dueDate);
    }

    public boolean canRenew() {
        return !renewed && !isOverdue() && returnDate == null;
    }

    public void renew() {
        if (!canRenew()) {
            throw new IllegalStateException("Sorry but you have already renewed once.");
        }
        dueDate = dueDate.plusDays(BORROW_PERIOD_DAYS);
        renewed = true;
    }


    @Override
    public String toString() {
        return "BorrowRecord{" +
                "isbn='" + isbn + '\'' +
                ", userId='" + userId + '\'' +
                ", borrowDate=" + borrowDate +
                ", dueDate=" + dueDate +
                ", returnDate=" + returnDate +
                ", renewed=" + renewed +
                '}';
    }

    public String getIsbn() {
        return isbn;
    }
}