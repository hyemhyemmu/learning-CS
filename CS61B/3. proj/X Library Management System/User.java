import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;

public class User {
    private String userId;
    private String name;
    private List<BorrowRecord> currentBorrows;
    private List<BorrowRecord> borrowHistory;
    private static final int MAX_BORROW_LIMIT = 5;
    private int borrowedBookNum;

    //constructor
    public User(String userId, String name) {
        this.userId = userId;
        this.name = name;
        currentBorrows = new LinkedList<>();
        borrowHistory = new LinkedList<>();
        borrowedBookNum = 0;
    }

    //should be less than 5 book borrowed
    public boolean canBorrow() {
        return currentBorrows.size() < MAX_BORROW_LIMIT;
    }

    //add a new borrow record to user's account
    public void addBorrowRecord(BorrowRecord record) {
        currentBorrows.add(record);
    }

    public void returnBook(String isbn) {
        //symbols whether the returning is successful or not
        boolean returned = false;
        for (BorrowRecord record : currentBorrows) {
            if (record.getIsbn().equals(isbn)) {
                currentBorrows.remove(record);
                borrowHistory.add(record);
                returned = true;
            }
        }
        if (!returned)
            throw new IllegalStateException("No such book exists!");
    }



    @Override
    public String toString() {
        return String.format("User{userId='%s',name='%s',currentBorrows=%d}", userId, name, borrowedBookNum);
    }


    public String getUserId() {
        return userId;
    }

    public boolean isCurrentBorrowsEmpty(){
        return currentBorrows.isEmpty();
    }


    public boolean hasBorrowed(String isbn){
        for (BorrowRecord record :currentBorrows){
            if (record.getIsbn().equals(isbn))
                return true;
        }
        return false;
    }

    public BorrowRecord getBorrowRecord(String isbn){
        for (BorrowRecord record:currentBorrows){
            if (record.getIsbn().equals(isbn))
                return record;
        }
        return null;
    }

    public List<BorrowRecord> getBorrowRecord(){
        return currentBorrows;
    }
    public List<BorrowRecord> getBorrowHistory(){
        return borrowHistory;
    }


    @Override
    public int hashCode() {
        return getUserId().hashCode();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (this.getClass() != o.getClass()) return false;
        User user = (User) o;
        return this.getUserId().equals(user.getUserId());
    }

}