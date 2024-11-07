#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int quantity;

    void getData() {
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Title: ";
        cin.ignore();  
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void displayData() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Quantity: " << quantity << endl;
    }
};

void addBook() {
    ofstream file("library.txt", ios::app);
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    Book b;
    b.getData();

    
    file << b.id << "\n" << b.title << "\n" << b.author << "\n" << b.quantity << "\n";
    file.close();
    cout << "Book added successfully.\n";
}

void displayAllBooks() {
    ifstream file("library.txt");
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    Book b;
    bool found = false;

    while (file >> b.id) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.quantity;
        file.ignore();

        b.displayData();
        found = true;
    }

    if (!found) {
        cout << "No books found.\n";
    }

    file.close();
}

void searchBook() {
    ifstream file("library.txt");
    if (!file) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    int searchID;
    bool found = false;
    cout << "Enter Book ID to search: ";
    cin >> searchID;

    Book b;
    while (file >> b.id) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.quantity;
        file.ignore();

        if (b.id == searchID) {
            cout << "Book Found:\n";
            b.displayData();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }

    file.close();
}

void deleteBook() {
    ifstream file("library.txt");
    ofstream temp("temp.txt");
    if (!file || !temp) {
        cerr << "Error opening file.\n";
        return;
    }

    int deleteID;
    bool found = false;
    cout << "Enter Book ID to delete: ";
    cin >> deleteID;

    Book b;
    while (file >> b.id) {
        file.ignore();
        getline(file, b.title);
        getline(file, b.author);
        file >> b.quantity;
        file.ignore();

        if (b.id == deleteID) {
            cout << "Book deleted successfully.\n";
            found = true;
        } else {
            
            temp << b.id << "\n" << b.title << "\n" << b.author << "\n" << b.quantity << "\n";
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }

    file.close();
    temp.close();

    
    remove("library.txt");
    rename("temp.txt", "library.txt");
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Add Book\n2. Display All Books\n3. Search Book by ID\n4. Delete Book by ID\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            displayAllBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            deleteBook();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
