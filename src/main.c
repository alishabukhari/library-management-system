#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[50];
    char author[50];
} Book;

// Function to check if a book with the same ID already exists
int isBookIdUnique(int id) {
    FILE *file = fopen("library.txt", "r");
    if (!file) {
        return 1; // If the file doesn't exist, assume ID is unique
    }

    Book book;
    while (fscanf(file, "%d,%[^,],%[^\n]\n", &book.id, book.title, book.author) != EOF) {
        if (book.id == id) {
            fclose(file);
            return 0; // ID is not unique
        }
    }
    fclose(file);
    return 1; // ID is unique
}

void addBook() {
    FILE *file = fopen("library.txt", "a");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    Book book;
    printf("Enter Book ID: ");
    scanf("%d", &book.id);

    // Check if the book ID is unique
    if (!isBookIdUnique(book.id)) {
        printf("Error: A book with ID %d already exists.\n", book.id);
        fclose(file);
        return;
    }

    printf("Enter Book Title: ");
    scanf(" %[^\n]", book.title); // Reads a full line including spaces
    printf("Enter Book Author: ");
    scanf(" %[^\n]", book.author);

    fprintf(file, "%d,%s,%s\n", book.id, book.title, book.author);
    fclose(file);
    printf("Book added successfully!\n");
}

void searchBook() {
    FILE *file = fopen("library.txt", "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    int id;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    Book book;
    int found = 0;

    while (fscanf(file, "%d,%[^,],%[^\n]\n", &book.id, book.title, book.author) != EOF) {
        if (book.id == id) {
            printf("\nBook Found:\n");
            printf("ID: %d\n", book.id);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No book found with ID %d.\n", id);
    }
}

void deleteBook() {
    FILE *file = fopen("library.txt", "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    Book book;
    int found = 0;

    while (fscanf(file, "%d,%[^,],%[^\n]\n", &book.id, book.title, book.author) != EOF) {
        if (book.id == id) {
            found = 1; // Skip writing this book to the temp file
        } else {
            fprintf(temp, "%d,%s,%s\n", book.id, book.title, book.author);
        }
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove("library.txt");
        rename("temp.txt", "library.txt");
        printf("Book deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("No book found with ID %d.\n", id);
    }
}

void listAllBooks() {
    FILE *file = fopen("library.txt", "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    Book book;
    int hasBooks = 0;

    printf("\nAll Books in the Library:\n");
    printf("---------------------------------------------\n");
    printf("| ID   | Title            | Author  |\n");
    printf("---------------------------------------------\n");

    while (fscanf(file, "%d,%[^,],%[^\n]\n", &book.id, book.title, book.author) != EOF) {
        printf("| %d | %s | %s |\n", book.id, book.title, book.author);
        hasBooks = 1;
    }

    fclose(file);

    if (!hasBooks) {
        printf("No books available in the library.\n");
    } else {
        printf("---------------------------------------------\n");
    }
}

void menu() {
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Delete Book\n");
        printf("4. List All Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                listAllBooks();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
