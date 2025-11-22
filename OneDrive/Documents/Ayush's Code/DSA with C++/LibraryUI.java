import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.util.List;

// Book class - made fields final since they shouldn't change after creation
class Book {
    private final String title;
    private final String author;
    private final String genre;
    private boolean isAvailable;
    private Date borrowDate;

    public Book(String title, String author, String genre) {
        this.title = Objects.requireNonNull(title, "Title cannot be null");
        this.author = Objects.requireNonNull(author, "Author cannot be null");
        this.genre = Objects.requireNonNull(genre, "Genre cannot be null");
        this.isAvailable = true;
        this.borrowDate = null;
    }

    // Getters
    public String getTitle() { return title; }
    public String getAuthor() { return author; }
    public String getGenre() { return genre; }
    public boolean isAvailable() { return isAvailable; }
    public Date getBorrowDate() { return borrowDate != null ? (Date) borrowDate.clone() : null; }

    // Setters with validation
    public void setAvailable(boolean available) { isAvailable = available; }
    public void setBorrowDate(Date borrowDate) { 
        this.borrowDate = borrowDate != null ? (Date) borrowDate.clone() : null; 
    }

    @Override
    public String toString() {
        return String.format("%s by %s (%s) - %s", title, author, genre, 
                           isAvailable ? "Available" : "Borrowed");
    }
}

// Library Manager
class LibraryManager {
    private final List<Book> books;
    private static final int FINE_RATE = 1; // Rs 1 per day

    public LibraryManager() {
        books = new ArrayList<>();
    }

    public void addBook(Book book) {
        if (book == null) {
            throw new IllegalArgumentException("Book cannot be null");
        }
        books.add(book);
    }

    public boolean borrowBook(String title) {
        if (title == null || title.trim().isEmpty()) {
            return false;
        }
        
        for (Book book : books) {
            if (book.getTitle().equalsIgnoreCase(title.trim()) && book.isAvailable()) {
                book.setAvailable(false);
                book.setBorrowDate(new Date());
                return true;
            }
        }
        return false;
    }

    public int returnBook(String title) {
        if (title == null || title.trim().isEmpty()) {
            return -1;
        }
        
        for (Book book : books) {
            if (book.getTitle().equalsIgnoreCase(title.trim()) && !book.isAvailable()) {
                book.setAvailable(true);
                int fine = calculateFine(book.getBorrowDate());
                book.setBorrowDate(null);
                return fine;
            }
        }
        return -1;
    }

    private int calculateFine(Date borrowDate) {
        if (borrowDate == null) return 0;
        long diff = new Date().getTime() - borrowDate.getTime();
        int daysLate = (int) (diff / (1000 * 60 * 60 * 24));
        return Math.max(daysLate * FINE_RATE, 0);
    }

    public List<Book> searchBook(String query) {
        List<Book> results = new ArrayList<>();
        if (query == null || query.trim().isEmpty()) {
            return results;
        }
        
        String lowerQuery = query.toLowerCase();
        for (Book book : books) {
            if (book.getTitle().toLowerCase().contains(lowerQuery) ||
                book.getAuthor().toLowerCase().contains(lowerQuery) ||
                book.getGenre().toLowerCase().contains(lowerQuery)) {
                results.add(book);
            }
        }
        return results;
    }

    public List<Book> getBooks() {
        return new ArrayList<>(books); // Return a copy to prevent external modification
    }
}

// GUI Class
class LibraryUI extends JFrame implements ActionListener {
    private final LibraryManager libraryManager;
    private final JTable bookTable;
    private final DefaultTableModel tableModel;
    private final JTextField searchField;
    private final JButton borrowButton, returnButton, searchButton;

    public LibraryUI() {
        libraryManager = new LibraryManager();
        
        setTitle("Library Management System");
        setSize(800, 500); // Increased size for better visibility
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        
        // Table setup
        tableModel = new DefaultTableModel(
            new String[]{"Title", "Author", "Genre", "Availability"}, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false; // Make table non-editable
            }
        };
        bookTable = new JTable(tableModel);
        bookTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        add(new JScrollPane(bookTable), BorderLayout.CENTER);
        
        // Button panel setup
        JPanel buttonPanel = new JPanel(new FlowLayout());
        borrowButton = new JButton("Borrow");
        returnButton = new JButton("Return");
        borrowButton.addActionListener(this);
        returnButton.addActionListener(this);
        
        buttonPanel.add(borrowButton);
        buttonPanel.add(returnButton);
        
        // Search panel setup
        JPanel searchPanel = new JPanel(new BorderLayout());
        searchField = new JTextField(30);
        searchButton = new JButton("Search");
        searchButton.addActionListener(this);
        
        JPanel searchInputPanel = new JPanel();
        searchInputPanel.add(new JLabel("Search: "));
        searchInputPanel.add(searchField);
        searchInputPanel.add(searchButton);
        
        searchPanel.add(searchInputPanel, BorderLayout.WEST);
        searchPanel.add(buttonPanel, BorderLayout.EAST);
        
        add(searchPanel, BorderLayout.SOUTH);
        
        loadSampleData();
        updateTable();
        
        // Center the window
        setLocationRelativeTo(null);
    }

    private void loadSampleData() {
        libraryManager.addBook(new Book("The Hobbit", "J.R.R. Tolkien", "Fantasy"));
        libraryManager.addBook(new Book("1984", "George Orwell", "Dystopian"));
        libraryManager.addBook(new Book("To Kill a Mockingbird", "Harper Lee", "Fiction"));
        libraryManager.addBook(new Book("Pride and Prejudice", "Jane Austen", "Classic"));
        libraryManager.addBook(new Book("The Great Gatsby", "F. Scott Fitzgerald", "Classic"));
    }

    private void updateTable() {
        updateTable(libraryManager.getBooks());
    }
    
    private void updateTable(List<Book> booksToDisplay) {
        tableModel.setRowCount(0);
        for (Book book : booksToDisplay) {
            tableModel.addRow(new Object[]{
                book.getTitle(), 
                book.getAuthor(), 
                book.getGenre(), 
                book.isAvailable() ? "Available" : "Borrowed"
            });
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == searchButton) {
            String searchQuery = searchField.getText().trim();
            List<Book> results = libraryManager.searchBook(searchQuery);
            updateTable(results);
            return;
        }
        
        int selectedRow = bookTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Please select a book first!", 
                "No Selection", JOptionPane.WARNING_MESSAGE);
            return;
        }
        
        String title = (String) tableModel.getValueAt(selectedRow, 0);
        
        if (e.getSource() == borrowButton) {
            if (libraryManager.borrowBook(title)) {
                JOptionPane.showMessageDialog(this, 
                    "Book borrowed successfully!", 
                    "Success", JOptionPane.INFORMATION_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(this, 
                    "Book not available for borrowing!", 
                    "Error", JOptionPane.ERROR_MESSAGE);
            }
        } else if (e.getSource() == returnButton) {
            int fine = libraryManager.returnBook(title);
            if (fine >= 0) {
                String message = "Book returned successfully!";
                if (fine > 0) {
                    message += "\nFine: Rs " + fine;
                }
                JOptionPane.showMessageDialog(this, message, 
                    "Success", JOptionPane.INFORMATION_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(this, 
                    "Book not found or not borrowed!", 
                    "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
        updateTable();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            } catch (Exception e) {
                e.printStackTrace();
            }
            new LibraryUI().setVisible(true);
        });
    }
}