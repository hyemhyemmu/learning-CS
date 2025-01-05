import java.util.List;
import java.util.ArrayList;

public class User {
    private String userId;
    private String name;
    private List<BorrowRecord> currentBorrows;
    private List<BorrowRecord> borrowHistory;
    private static final int MAX_BORROW_LIMIT=5;
    private int borrowedBookNum;

    //constructor
    public User(String userId, String name) {
        this.userId=userId;
        this.name=name;
        currentBorrows=new ArrayList<>();
        borrowHistory=new ArrayList<>();
        borrowedBookNum=0;
    }

    //should be less than 5 book borrowed
    public boolean canBorrow() {
        return currentBorrows.size()<MAX_BORROW_LIMIT;
    }

    //add a new borrow record to user's account
    public void addBorrowRecord(String isbn){
        BorrowRecord newRecord=new BorrowRecord(isbn,userId);
        currentBorrows.add(newRecord);
    }

    public void returnBook(String isbn){
        //symbols whether the returning is successful or not
        boolean returned=false;
        for (BorrowRecord record:currentBorrows){
            if (record.getIsbn().equals(isbn)){
                currentBorrows.remove(record);
                returned=true;
            }
        }
        if (!returned)
            throw new IllegalStateException("No such book exists!");
    }

    //TODO:需要完成一个追踪结束数量的函数和变量

    @Override
    public String toString(){
        return String.format("User{userId='%s',name='%s',currentBorrows=%d}",userId,name,borrowedBookNum);
    }

}