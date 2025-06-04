#include <bits/stdc++.h>
using namespace std;

class Book {
protected:
    string title, author, ISBN;
public:
    Book(string t, string a, string isbn) : title(t), author(a), ISBN(isbn) {}

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getISBN() { return ISBN; }

    virtual void display() {
        cout << "Title: " << title << '\n';
        cout << "Author: " << author << '\n';
        cout << "ISBN: " << ISBN << '\n';
    }
};

class fictionBooks : public Book {
public:
    fictionBooks(string t, string a, string isbn) : Book(t, a, isbn) {}
    void display() override {
        cout << getTitle() << '\n' << getAuthor() << '\n' << getISBN() << '\n';
    }
};

class nonFictionBooks : public Book {
public:
    nonFictionBooks(string t, string a, string isbn) : Book(t, a, isbn) {}
    void display() override {
        cout << getTitle() << '\n' << getAuthor() << '\n' << getISBN() << '\n';
    }
};

class SLLNode {
    Book* book;
    SLLNode* next;
public:
    SLLNode(Book* b) : book(b), next(nullptr) {}
    void setNext(SLLNode* n) { next = n; }
    SLLNode* getNext() { return next; }
    Book* getBook() { return book; }
};

class SLL {
    SLLNode* head;
public:
    SLL() : head(nullptr) {}

    void addBook(Book* book) {
        SLLNode* newNode = new SLLNode(book);
        if (!head) head = newNode;
        else {
            SLLNode* current = head;
            while (current->getNext()) current = current->getNext();
            current->setNext(newNode);
        }
    }

    void display() {
        SLLNode* current = head;
        while (current) {
            current->getBook()->display();
            cout << '\n';
            current = current->getNext();
        }
    }

    SLLNode* searchByISBN(string isbn) {
        SLLNode* current = head;
        while (current) {
            if (current->getBook()->getISBN() == isbn) return current;
            current = current->getNext();
        }
        return nullptr;
    }

    void deleteNode(SLLNode* target) {
        if (!head || !target) return;
        if (head == target) {
            head = head->getNext();
            delete target;
            return;
        }
        SLLNode* current = head;
        while (current->getNext() && current->getNext() != target)
            current = current->getNext();
        if (current->getNext()) {
            current->setNext(target->getNext());
            delete target;
        }
    }
};

class DLLNode {
    Book* book;
    DLLNode* next;
    DLLNode* prev;
public:
    DLLNode(Book* b) : book(b), next(nullptr), prev(nullptr) {}
    void setNext(DLLNode* n) { next = n; }
    void setPrev(DLLNode* p) { prev = p; }
    DLLNode* getNext() { return next; }
    DLLNode* getPrev() { return prev; }
    Book* getBook() { return book; }
};

class DLL {
    DLLNode* head;
    DLLNode* tail;
public:
    DLL() : head(nullptr), tail(nullptr) {}

    void addBook(Book* book) {
        DLLNode* newNode = new DLLNode(book);
        if (!head) head = tail = newNode;
        else {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
    }

    void display() {
        DLLNode* current = head;
        while (current) {
            current->getBook()->display();
            cout << '\n';
            current = current->getNext();
        }
    }

    DLLNode* searchByISBN(string isbn) {
        DLLNode* current = head;
        while (current) {
            if (current->getBook()->getISBN() == isbn) return current;
            current = current->getNext();
        }
        return nullptr;
    }

    void removeByISBN(string isbn) {
        DLLNode* current = searchByISBN(isbn);
        if (!current) return;
        if (current == head) {
            head = current->getNext();
            if (head) head->setPrev(nullptr);
        } else if (current == tail) {
            tail = current->getPrev();
            if (tail) tail->setNext(nullptr);
        } else {
            current->getPrev()->setNext(current->getNext());
            current->getNext()->setPrev(current->getPrev());
        }
        delete current;
    }
};

class stack1 {
    int maxStackSize = 5;
    int stackTop = -1;
    Book* list[5];
public:
    void initializeStack() {
        for (int i = 0; i < maxStackSize; i++) list[i] = nullptr;
        stackTop = -1;
    }
    bool isEmpty() { return stackTop == -1; }
    bool isFull() { return stackTop == maxStackSize - 1; }
    void pushBook(Book* b) { if (!isFull()) list[++stackTop] = b; }
    Book* popBook() { return isEmpty() ? nullptr : list[stackTop--]; }
    void display() {
        for (int i = stackTop; i >= 0; i--) list[i]->display();
    }
};

class queue1 {
    int maxQueueSize = 10;
    int queueFront = 0;
    int queueRear = maxQueueSize - 1;
    int count = 0;
    Book* list[10];
public:
    void initializeQueue() {
        for (int i = 0; i < maxQueueSize; i++) list[i] = nullptr;
        queueFront = 0;
        queueRear = maxQueueSize - 1;
        count = 0;
    }
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == maxQueueSize; }
    void enqueue(Book* b) {
        if (!isFull()) {
            queueRear = (queueRear + 1) % maxQueueSize;
            list[queueRear] = b;
            count++;
        }
    }
    Book* dequeue() {
        if (isEmpty()) return nullptr;
        Book* frontBook = list[queueFront];
        queueFront = (queueFront + 1) % maxQueueSize;
        count--;
        return frontBook;
    }
    void display() {
        int i = queueFront, elements = count;
        while (elements--) {
            list[i]->display();
            i = (i + 1) % maxQueueSize;
        }
    }
};

class Library {
    SLL fictionList;
    DLL nonFictionList;
    stack1 recentlyAdded;
    queue1 borrowQueue;
public:
    Library() {
        recentlyAdded.initializeStack();
        borrowQueue.initializeQueue();
    }

    void addBook(Book* book, bool isFiction) {
        if (isFiction) fictionList.addBook(book);
        else nonFictionList.addBook(book);
        recentlyAdded.pushBook(book);
        cout << "Book added successfully.\n";
    }

    void removeBook(string ISBN) {
        SLLNode* fictionNode = fictionList.searchByISBN(ISBN);
        if (fictionNode) {
            fictionList.deleteNode(fictionNode);
            cout << "Book removed from Fiction List.\n";
            return;
        }
        DLLNode* nonFictionNode = nonFictionList.searchByISBN(ISBN);
        if (nonFictionNode) {
            nonFictionList.removeByISBN(ISBN);
            cout << "Book removed from Non-Fiction List.\n";
            return;
        }
        cout << "Book not found in either list.\n";
    }

    Book* searchBook(string query) {
        SLLNode* fictionNode = fictionList.searchByISBN(query);
        if (fictionNode) {
            cout << "Book found in Fiction List.\n";
            return fictionNode->getBook();
        }
        DLLNode* nonFictionNode = nonFictionList.searchByISBN(query);
        if (nonFictionNode) {
            cout << "Book found in Non-Fiction List.\n";
            return nonFictionNode->getBook();
        }
        return nullptr;
    }

    void borrowBook(Book* book) {
        borrowQueue.enqueue(book);
        cout << "Book added to borrow queue.\n";
    }

    void returnBook() {
        Book* returnedBook = borrowQueue.dequeue();
        if (returnedBook) {
            cout << "Book returned: ";
            returnedBook->display();
        } else {
            cout << "No books to return.\n";
        }
    }

    void displayAllBooks() {
        cout << "Fiction Books:\n";
        fictionList.display();
        cout << "\nNon-Fiction Books:\n";
        nonFictionList.display();
        cout << "\nRecently Added Books:\n";
        recentlyAdded.display();
    }

    void displayBorrowedBooks() {
        borrowQueue.display();
    }
};

int main() {
    Library lib;
    Book* book;
    string title, author, ISBN;
    bool isFiction;
    int choice;

    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1. Add Book\n2. Remove Book\n3. Search Book\n4. Borrow Book\n5. Return Book\n6. Display All Books\n7. Display Borrowed Books\n8. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: "; cin >> title;
                cout << "Enter author: "; cin >> author;
                cout << "Enter ISBN: "; cin >> ISBN;
                cout << "Is it a fiction book? (1 for Yes, 0 for No): "; cin >> isFiction;
                if (isFiction) book = new fictionBooks(title, author, ISBN);
                else book = new nonFictionBooks(title, author, ISBN);
                lib.addBook(book, isFiction);
                break;
            case 2:
                cout << "Enter ISBN of the book to remove: ";
                cin >> ISBN;
                lib.removeBook(ISBN);
                break;
            case 3:
                cout << "Enter title or ISBN to search: ";
                cin >> ISBN;
                book = lib.searchBook(ISBN);
                if (book) book->display();
                else cout << "Book not found.\n";
                break;
            case 4:
                cout << "Enter ISBN of the book to borrow: ";
                cin >> ISBN;
                book = lib.searchBook(ISBN);
                if (book) lib.borrowBook(book);
                else cout << "Book not found.\n";
                break;
            case 5:
                lib.returnBook();
                break;
            case 6:
                lib.displayAllBooks();
                break;
            case 7:
                lib.displayBorrowedBooks();
                break;
            case 8:
                cout << "Exiting the library system.\n";
                return 0;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    }
}
