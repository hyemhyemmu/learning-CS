public class Book implements Comparable<Book> {
    /**
     *  book class
     */
    private String isbn;
    private String title;
    private String author;
    private String category;
    private boolean isAvailable;
    private int borrowCount;

    public Book(String isbn, String title, String author, String category) {
        this.isbn = isbn;
        this.title = title;
        this.author = author;
        this.category = category;
        this.isAvailable = true;
        this.borrowCount = 0;
    }

    public String getIsbn() {
        return isbn;
    }

    public String getTitle() {
        return title;
    }


    public String getAuthor() {
        return author;
    }


    public String getCategory() {
        return category;
    }


    public boolean isAvailable() {
        return isAvailable;
    }

    public void setAvailable(boolean available) {
        isAvailable = available;
    }

    public int getBorrowCount() {
        return borrowCount;
    }

    public void incrementBorrowCount() {
        this.borrowCount++;
    }

    /**
     * compareTo method for Comparable interface,
     * based on the order of: ISBN;name;author
     *
     * @param other the object to be compared.
     * @return value
     */
    @Override
    public int compareTo(Book other) {
        int isbnComparison = this.isbn.compareTo(other.isbn);
        if (isbnComparison != 0) {
            return isbnComparison;
        }

        int titleComparison = this.title.compareTo(other.title);
        if (titleComparison != 0) {
            return titleComparison;
        }

        return this.author.compareTo(other.author);
    }

    @Override
    public String toString() {
        return "Book{" +
                "isbn='" + isbn + '\'' +
                ", title='" + title + '\'' +
                ", author='" + author + '\'' +
                ", category='" + category + '\'' +
                ", isAvailable=" + isAvailable +
                ", borrowCount=" + borrowCount +
                '}';
    }

    /**
     * "equals"based on ISBN comparison
     *
     * @param obj
     * @return whether equal or not
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        else if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Book book = (Book) obj;
        return getIsbn().equals(book.getIsbn());
    }

    /**
     * @return hashcode generated base on ISBN
     */
    @Override
    public int hashCode() {
        return getIsbn().hashCode();
    }
}