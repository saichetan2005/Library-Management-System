#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    Book* next;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), isIssued(false), next(nullptr) {}
};

class Library {
private:
    Book* head;

    Book* searchById(int id) {
        Book* current = head;
        while (current != nullptr) {
            if (current->id == id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    Book* searchByTitle(string title) {
        Book* current = head;
        while (current != nullptr) {
            if (current->title == title)
                return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    Library() : head(nullptr) {}

    void addBook(int id, string title, string author) {
        Book* newBook = new Book(id, title, author);
        if (head == nullptr) {
            head = newBook;
        } else {
            Book* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newBook;
        }
        cout << "Book added: " << title << endl;
    }

    void searchBook(int id) {
        Book* book = searchById(id);
        if (book) {
            cout << "Book found: " << book->title << " by " << book->author << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void searchBook(string title) {
        Book* book = searchByTitle(title);
        if (book) {
            cout << "Book found: " << book->title << " by " << book->author << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void issueBook(int id, string studentName) {
        Book* book = searchById(id);
        if (book) {
            if (book->isIssued) {
                cout << "Book already issued." << endl;
            } else {
                book->isIssued = true;
                cout << "Book issued to " << studentName << endl;
            }
        } else {
            cout << "Book not found." << endl;
        }
    }

    void returnBook(int id) {
        Book* book = searchById(id);
        if (book) {
            if (book->isIssued) {
                book->isIssued = false;
                cout << "Book returned." << endl;
            } else {
                cout << "Book was not issued." << endl;
            }
        } else {
            cout << "Book not found." << endl;
        }
    }

    void listBooks() {
        if (head == nullptr) {
            cout << "No books available." << endl;
            return;
        }
        Book* current = head;
        while (current != nullptr) {
            cout << current->id << ": " << current->title << " by " <<
            current->author << (current->isIssued ? " (Issued)" : "") << endl;
            current = current->next;
        }
    }

    void deleteBook(int id) {
        if (head == nullptr) {
            cout << "No books available." << endl;
            return;
        }
        if (head->id == id) {
            Book* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Book deleted." << endl;
            return;
        }
        Book* current = head;
        while (current->next != nullptr && current->next->id != id) {
            current = current->next;
        }
        if (current->next == nullptr) {
            cout << "Book not found." << endl;
        } else {
            Book* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
            cout << "Book deleted." << endl;
        }
    }
};

int main() {
    Library library;
    int choice, id;
    string title, author, studentName;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add New Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            library.addBook(id, title, author);
            break;
        case 2:
            cout << "Enter Book ID: ";
            cin >> id;
            library.searchBook(id);
            break;
        case 3:
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, title);
            library.searchBook(title);
            break;
        case 4:
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Student Name: ";
            getline(cin, studentName);
            library.issueBook(id, studentName);
            break;
        case 5:
            cout << "Enter Book ID: ";
            cin >> id;
            library.returnBook(id);
            break;
        case 6:
            library.listBooks();
            break;
        case 7:
            cout << "Enter Book ID: ";
            cin >> id;
            library.deleteBook(id);
            break;
        case 8:
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}
