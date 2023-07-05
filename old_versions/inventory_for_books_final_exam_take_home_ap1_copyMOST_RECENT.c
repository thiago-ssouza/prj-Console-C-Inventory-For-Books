/******************************************************************************
thiago.soares_de_souza @ lcieducation.net
AP1 - Michelle, Final Exam take home - Inventory for Books
winter 2022 LaSalle College
2022-04-29

Instructions: 

You are creating an inventory for books.

You are creating an inventory for books. You care about the following characteristics:

- ISBN – a unique ID
- Title
- Author
- Publisher
- Genre
- Year of Publication
- Amount in Stock
- Selling Price

Start by creating a struct books that can store the above members.
Then, create an array that can hold up to 500 books
Both struct and array need to be declared globally.

In addition, you may need/want to declare a global int k that keeps track of how many items have been entered in the array…

When the system fires up, it offers the user the following main menu options:

1. Populate the inventory // option to add one or more books to the inventory
2. Search by keywords // this could match title, author, genre, or publisher
3. Process a transaction // this is a buy or return transaction
4. Delete a book record
5. Display all books in the inventory
6. Exit the system

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MIN_INVENTORY 0
#define MAX_INVENTORY 500
#define ISBN_GENERATOR_DEFAULT 2008109456
#define MIN_TITLE_SIZE 1
#define MIN_PUBLISHER_SIZE 3
#define MIN_AUTHOR_SIZE 3
#define MIN_GENRE_SIZE 4
#define MIN_AMOUNT 0
#define MAX_AMOUNT 100000000
#define MIN_PRICE 0
#define MAX_PRICE 100000000
#define NO_TRANSACTION_TYPE -1


// Struct
typedef struct book {
    long int isbn;
    char title[71];
    char author[51];
    char publisher[71];
    char genre[41];
    int year_publication;
    int amount_stock;
    float price;
} Book;


// Global Variables
Book book_inventory[MAX_INVENTORY];

long int isbn_generator = 2008109456; // 2008109456 + MAX_INVENTORY (500) -> 2008109956 maximum number

int amount_books = 0;

const size_t title_size = sizeof(book_inventory[0].title) / sizeof(book_inventory[0].title[0]);
const size_t author_size = sizeof(book_inventory[0].author) / sizeof(book_inventory[0].author[0]);
const size_t publisher_size = sizeof(book_inventory[0].publisher) / sizeof(book_inventory[0].publisher[0]);
const size_t genre_size = sizeof(book_inventory[0].genre) / sizeof(book_inventory[0].genre[0]);

// Fuction Declaration

// Validate repeat opetation
char validate_repeat_operation(int, int);

// Get and validate if the number is a valid integer (Inspired in camilo's get_validate_integer code in the calculator program, presented during the class)
int get_validate_integer(int, int);

// Get and validate if the number is a valid float (Inspired in camilo's get_validate_integer code in the calculator program, presented during the class)
float get_validate_float(float, float);

// Get and validate if the string has a valid length (Inspired in camilo's get_validate_integer code in the calculator program, presented during the class)
void get_validate_string(char[], int, int);

// Print the title of the user choice and the type of transaction if it is available (Player vs Player, Player vs Machine, Machine vs Machine)
void display_menu_options(int, int);

// Get answer yes or no
char get_answer_yes_no(char[]);

// Add 1 or More books depended of the user choise and the inventory free space
void add_books(int, int);

// Add 1 book record, depending if the inventory has free space
void add_book_record(int);

// Get a book record prompting to the user and returns it
Book get_book_record();

// Print a single book record
void print_book(int);

// Print all the book inventory
void print_book_inventory();

// Pre load demo data for testing
void pre_load_demo_data();

// Search a unique book by ISBN
int search_book(int);

// Check if the inventory is empty
bool isInventoryEmpty();

// Prinf the empty message and set a sleep time of 3 seconds
void print_empty_message();

// Delete a book using the index
void delete_book(int, int);

// Print a single book record receiving a book
void print_book_by_book(int, Book);

// Acourding to each operation (Add book, delete book, transactions)
void print_confirm_operation(int, int);

// Get current_year
int get_current_year();

// Get first_printed_book_year
int get_first_printed_book_year();

// Check if the string has only blank space
bool has_only_blank_space(char[], int);

// Check if the string has only alpha and blank space
bool has_only_alpha_and_space(char[], int);

// Check if the string has at least one letter
bool has_alpha(char[], int);

// Remove blank spaces before the string
void trim_string_left(char[], int, int);

// Remove blank spaces after the string
void trim_string_right(char[], int, int);

// Remove blank spaces between the string
void trim_string_between(char[], int, int);

// Search for book by keywords (Title, Author, Genre and/or Publisher) and return the number of indexes found
int search_book_by_keywords(char[], char[], char[], char[], int[]);

// Convert string to lowercase
void string_to_lower(char[], size_t);

// Get the keyword to do the search by keyword
void get_keywords_search(char[], char[], char[], char[]);

// Purchase a book or books depending of the quantity
void purchase_book(int[], int, int, int);

// Return operation of a book by ISBN if found
void return_book(int, int, int);

int main(){

    int choice = -1;
    char repeat_operation = '\n';

    // Pre load demo data for testing
    pre_load_demo_data();   
    
    do{
        system("cls");
        choice = -1;

        do{
            printf("\t\t\t      INVENTORY OF BOOKS\n");
            printf("\t\t\t Main Menu Operators Choice\n");
            printf("\t\t\t----------------------------\n\n");

            printf("  1 - Populate the inventory\n");
            printf("  2 - Search by keywords\n");
            printf("  3 - Process a transaction\n");
            printf("  4 - Delete a book record\n");
            printf("  5 - Display all books in the inventory\n");
            printf("  6 - Exit the system\n\n\n");

            printf("Make your choice (1 - 6) : ");
            scanf(" %d", &choice);
            fflush(stdin);
            
            if(choice < 1 || choice > 6){
                printf("\nInvalid choice. Choice should be between 1 - 6.\n");
                choice = -1;
                sleep(2);
                system("cls");
            }

        }while(choice < 1 || choice > 6);

        switch(choice){
            case 1:

                do{
                    
                    display_menu_options(choice, NO_TRANSACTION_TYPE);

                    if(amount_books == MAX_INVENTORY){
                        
                        printf("Inventory of book is full (%d). Please delete a book first.\n", amount_books);
                        sleep(3);
                        
                        repeat_operation = 'n';

                    }else{
                        
                        printf("Inventory free space for books: (%d).\n", MAX_INVENTORY - amount_books);

                        char enter_more_books = '\n';
                        int num_books_enter = 1;

                        if(MAX_INVENTORY - amount_books > MIN_INVENTORY + 1){

                            char question[] = "\nWould you like to enter more than 1 book (y/n) ? : ";

                            enter_more_books = get_answer_yes_no(question);
                        }

                        display_menu_options(choice, NO_TRANSACTION_TYPE);

                        if(enter_more_books == 'y'){

                            printf("Please enter the quantity of books you want to enter (%d - %d) or type 0 to cancel the operation : ", MIN_INVENTORY, MAX_INVENTORY - amount_books);
                            num_books_enter = get_validate_integer(MIN_INVENTORY, MAX_INVENTORY - amount_books);

                            if(num_books_enter == 0){

                                printf("\nYou have Select %d to enter. Returning to the main menu...\n", num_books_enter);
                                
                                sleep(3);

                                repeat_operation = 'n';

                            }else{
                                add_books(num_books_enter, choice);
                            }

                        }else{
                            add_book_record(choice);
                        }

                        if(num_books_enter != 0){
                            repeat_operation = validate_repeat_operation(choice, NO_TRANSACTION_TYPE);
                        }
                    }

                }while(repeat_operation == 'y');

                break;

            case 2:

                do{
                    
                    display_menu_options(choice, NO_TRANSACTION_TYPE);

                    char title_search[title_size];
                    char author_search[author_size];
                    char publisher_search[publisher_size];
                    char genre_search[genre_size];

                    int indexes_found[amount_books];

                    int count_found = 0;

                    if(isInventoryEmpty()){
                        print_empty_message();
                        repeat_operation = 'n';
                    }else{

                        get_keywords_search(title_search, author_search, genre_search, publisher_search);

                        count_found = search_book_by_keywords(title_search, author_search, genre_search, publisher_search, indexes_found);

                        if(count_found == 0){
                            printf("\nResult not found!\n");
                        }
                    }

                    repeat_operation = validate_repeat_operation(choice, NO_TRANSACTION_TYPE);

                }while(repeat_operation == 'y');

                break;
            
            case 3:

                do{

                    char repeat_transaction = '\n';
                    int transaction_type = -1;

                    char title_search[title_size];
                    char author_search[author_size];
                    char publisher_search[publisher_size];
                    char genre_search[genre_size];

                    int indexes_found[amount_books];

                    int isbn_search = 0;

                    int isbn_idx = -1;

                    int count_found = 0;
                    
                    do{
                        display_menu_options(choice, transaction_type);

                        printf("  1 - Purchase\n");
                        printf("  2 - Return\n");
                        printf("  3 - Cancel\n\n\n");
                        
                        printf("Make your transation type choice (1 - 3) : ");
                        
                        scanf(" %d", &transaction_type);
                        fflush(stdin);
                        
                        if(transaction_type < 1 || transaction_type > 3){
                            printf("\nInvalid transaction type. Choice should be between 1 - 3.\n");
                            transaction_type = -1;
                            sleep(2);
                        }

                    }while(transaction_type < 1 || transaction_type > 3);

                    switch(transaction_type){
                        
                        case 1:
                            do{
                                display_menu_options(choice, transaction_type);

                                get_keywords_search(title_search, author_search, genre_search, publisher_search);
                            
                                count_found = search_book_by_keywords(title_search, author_search, genre_search, publisher_search, indexes_found);

                                if(count_found == 0){
                                    printf("\nResult not found!\n");
                                }else{
                                    purchase_book(indexes_found, count_found, choice, transaction_type);
                                }

                                repeat_transaction = validate_repeat_operation(choice, transaction_type);

                            }while(repeat_transaction == 'y');

                            printf("\nLeving purchase transaction...");
                            sleep(2);

                            transaction_type = -1;

                            break;

                        case 2:

                            do{
                                display_menu_options(choice, transaction_type);

                                printf("Please enter the ISBN the book that you want to return (%d - %d) : ", ISBN_GENERATOR_DEFAULT, ((isbn_generator - ISBN_GENERATOR_DEFAULT) + ISBN_GENERATOR_DEFAULT) - 1);
                                
                                isbn_search = get_validate_integer(ISBN_GENERATOR_DEFAULT, ((isbn_generator - ISBN_GENERATOR_DEFAULT) + ISBN_GENERATOR_DEFAULT) - 1);

                                isbn_idx = search_book(isbn_search);

                                return_book(isbn_idx, choice, transaction_type);

                                repeat_transaction = validate_repeat_operation(choice, transaction_type);

                            }while(repeat_transaction == 'y');

                            printf("\nLeving return transaction...");
                            sleep(2);

                            transaction_type = -1;

                            break;

                        case 3:
                            printf("\nCanceling operation. Returning to the main menu...");
                            sleep(2);
                            repeat_operation = 'n';
                            break;

                        default:
                            printf("Operation not found. Please try to enter the operation again.\n");
                    }

                    display_menu_options(choice, transaction_type);

                    if(transaction_type != 3){
                        repeat_operation = validate_repeat_operation(choice, transaction_type);
                    }

                }while(repeat_operation == 'y');

                break;

            case 4:

                do{
                    display_menu_options(choice, NO_TRANSACTION_TYPE);

                    long int delete_isbn = 0;
                    int isbn_index = -1;
                    char confirm_purchase;
                    char question[] = "\nPlease confirm if you would you like to purchase the book (y/n) : ";

                    if(isInventoryEmpty()){
                        
                        print_empty_message();
                        repeat_operation = 'n';
                    }else{
                        printf("Enter the ISBN of the book that you would like to delete (%d - %d) : ",
                        ISBN_GENERATOR_DEFAULT, ( (isbn_generator - ISBN_GENERATOR_DEFAULT) + ISBN_GENERATOR_DEFAULT) - 1 );
                        delete_isbn = get_validate_integer(ISBN_GENERATOR_DEFAULT, ((isbn_generator - ISBN_GENERATOR_DEFAULT) + ISBN_GENERATOR_DEFAULT) - 1);

                        isbn_index = search_book(delete_isbn);

                        if(isbn_index == -1){
                            printf("\nISBN not found!\n");
                        }else{

                            print_book(isbn_index);

                            confirm_purchase = get_answer_yes_no(question);

                            if(confirm_purchase == 'y'){
                                delete_book(isbn_index, choice);
                            }else{
                                printf("\nCanceling delete operation...\n");
                                sleep(2);
                            } 
                        }

                        repeat_operation = validate_repeat_operation(choice, NO_TRANSACTION_TYPE);
                    }

                }while(repeat_operation == 'y');

                break;

            case 5:
                
                do{ 
                    display_menu_options(choice, NO_TRANSACTION_TYPE);

                    if(isInventoryEmpty()){
                        print_empty_message();
                        repeat_operation = 'n';
                    }else{
                        print_book_inventory();
                        repeat_operation = validate_repeat_operation(choice, NO_TRANSACTION_TYPE);
                    }

                }while(repeat_operation == 'y');

                break;
            
            case 6:
                printf("\nGoodbye...");
                sleep(2);
                system("cls");
                exit(0);

            default:
                printf("Operation not found. Please try to enter the operation again.\n");
        }

    }while(choice != 6);

    return 0;
}

// Fuction Definition

// Validate repeat opetation
char validate_repeat_operation(int choice, int transaction_type){

    char repeat_operation;

    do{
        
        // printf("\nDo you want to proceed with the ");
        printf("\nWould you like to do another ");

        if(choice == 1){
            printf("\"Populate the inventory\"");
        }else if(choice == 2){
            printf("\"Search by keywords\"");
        }else if(choice == 3){
            // printf("\"Process a transaction\"");
            if(transaction_type == 1){
                printf("\"Purchase a Book Transaction\"");
            }else if(transaction_type == 2){
                printf("\"Return a Book Transaction\"");
            }else{
                printf("\"Process a Transaction\"");
            }
        }else if(choice == 4){
            printf("\"Delete a book record\"");
        }else if(choice == 5){
            printf("\"Display all books in the inventory\"");
        }

        // printf(" operation again ? (y/n) : ");
        printf(" operation ? (y/n) : ");
        
        scanf(" %c", &repeat_operation);
        fflush(stdin);
        repeat_operation = tolower(repeat_operation);
        
        if(repeat_operation != 'y' && repeat_operation != 'n'){
            printf("\nInvalid option.\n");
            sleep(2);
        }

    }while(repeat_operation != 'y' && repeat_operation != 'n');

    return repeat_operation;
}

// Print the menu dinamically for the options inside the switch case
void display_menu_options(int choice, int transaction_type){

    system("cls");    
    
    printf("\t\t\t      INVENTORY OF BOOKS\n");
    
    if(choice == 1){
        printf("\t\t\t    Populate the Inventory\n");
    }else if(choice == 2){
        printf("\t\t\t      Search by Keywords\n");
    }else if(choice == 3){
        if(transaction_type == 1){
            printf("\t\t\t  Purchase a Book Transaction\n");
        }else if(transaction_type == 2){
            printf("\t\t\t  Return a Book Transaction\n");
        }else{
            printf("\t\t\t    Process a Transaction\n");
        }
    }else if(choice == 4){
        printf("\t\t\t     Delete a book record\n");
    }else if(choice == 5){
        printf("\t\t      Display all books in the inventory\n");
    }
    
    printf("\t\t     ------------------------------------\n\n");

}

// Get and validate if the number is a valid integer (Inspired in camilo's code in the calculator program, presented during the class)
int get_validate_integer(int min, int limit){

    int number = false;
    int valid;
    bool error = true;

    do{
        valid = scanf("%d", &number);
        getchar();

        if(valid != 0 && number >= min && number <= limit){
            error = false;
        }else{
            printf("\nPlease enter a valid number between %d - %d: ", min, limit);
        }

    }while(error);

    return number;
}

// Get and validate if the number is a valid float (Inspired in camilo's code in the calculator program, presented during the class)
float get_validate_float(float min, float limit){
    
    float number = false;
    int valid;
    bool error = true;

    do{
        valid = scanf("%f", &number);
        getchar();

        if(valid != 0 && number >= min && number <= limit){
            error = false;
        }else{
            printf("\nPlease enter a valid number between %.0f - %.0f: ", min, limit);
        }

    }while(error);

    return number;
}

// Get and validate if the string has a valid length (Inspired in camilo's code in the calculator program, presented during the class)
void get_validate_string(char str[], int min, int limit){
    
    bool valid = false;
    size_t length;
    bool error = true;

    do{
        
        fflush(stdin);
        fgets(str, limit, stdin);
        str[strcspn(str,"\n")] = 0;


        if(has_only_blank_space(str, strlen(str))){
            printf("\nThe text has only blank space!\n");
        }

        trim_string_left(str, strlen(str), limit);
        trim_string_right(str, strlen(str), limit);
        trim_string_between(str, strlen(str), limit);

        length = strlen(str);

        if(length >= min && length <= limit - 1){
            
            if(limit == title_size || limit == publisher_size){

                if(!has_alpha(str, length)){
                    printf("\nThe text cannot have only special characters and/or digit! Example: \"@#$%^23\" .\n");
                }else{
                    valid = true;
                }
            }
            else { // (limit == author_size || limit == genre_size)
                if(!has_only_alpha_and_space(str, length)){
                    printf("\nThe text must have only letters and one blank space between the words!\n");
                }else{
                    valid = true;
                }
            }

            if(valid == true){
                error = false;
            }else{
                printf("\nPlease enter a valid text between %d - %d of length: ", min, limit - 1);
            }

        }else{
            printf("\nPlease enter a valid text between %d - %d of length: ", min, limit - 1);
        }

    }while(error);
}

// Get answer yes or no
char get_answer_yes_no(char question[]){

    char ans;

    do{
        printf("%s", question);
        scanf(" %c", &ans);
        fflush(stdin);
        ans = tolower(ans);
        
        if(tolower(ans) != 'y' && tolower(ans) != 'n'){
            printf("\nInvalid option.\n");
            sleep(2);
        }

    }while(tolower(ans) != 'y' && tolower(ans) != 'n');

    return tolower(ans);
}

// Add More books depended of the user choise and the inventory free space
void add_books(int quantity, int choice){
    for(int i = 0 ; i < quantity ; i++){
        add_book_record(choice);
    }
}

// Add 1 book record, depending if the inventory has free space
void add_book_record(int choice){

    book_inventory[amount_books] = get_book_record();

    print_confirm_operation(choice, NO_TRANSACTION_TYPE);
    // printf("\n\nThe Book was added correctly. See information below:\n");

    print_book(amount_books);

    amount_books++;

}

// Get a book record prompting to the user and returns it
Book get_book_record(){
    
    Book book; 

    printf("Book inventory number: %d\n\n", amount_books + 1);

    printf("Please enter the information below:\n\n");

    printf("Enter the Tittle of the book between %d - %d characters) : ", MIN_TITLE_SIZE, title_size - 1);
    get_validate_string(book.title, MIN_TITLE_SIZE , title_size);

    printf("Enter the Author name of the book between %d - %d characters) : ", MIN_AUTHOR_SIZE, author_size - 1);
    get_validate_string(book.author, MIN_AUTHOR_SIZE , author_size);

    printf("Enter the Publisher name of the book between %d - %d characters) : ", MIN_PUBLISHER_SIZE, publisher_size - 1);
    get_validate_string(book.publisher, MIN_PUBLISHER_SIZE , publisher_size);

    printf("Enter the Genre of the book between %d - %d characters) : ", MIN_GENRE_SIZE, genre_size - 1);
    get_validate_string(book.genre, MIN_GENRE_SIZE , genre_size);
    
    fflush(stdin);
    printf("Enter the Year of Publication of the book (%d - %d) : ", get_first_printed_book_year(), get_current_year());
    book.year_publication = get_validate_integer(get_first_printed_book_year(), get_current_year());

    fflush(stdin);
    printf("Enter the currently Amount in Stock for this of the book (%d - %d) : ", MIN_AMOUNT, MAX_AMOUNT);
    book.amount_stock = get_validate_integer(MIN_AMOUNT, MAX_AMOUNT);
    
    fflush(stdin);
    printf("Enter the Selling Price for this book (%d - %d) : ", MIN_PRICE, MAX_PRICE);
    book.price = get_validate_float(MIN_PRICE, MAX_PRICE);

    fflush(stdin);
    book.isbn = isbn_generator;
    isbn_generator++;

    return book;
}

// Print a single book record
void print_book(int index){
           
    printf("\nBook inventory number: %d\n\n", index + 1);
    printf("ISBN: %ld\n", book_inventory[index].isbn);
    printf("Title: %s\n", book_inventory[index].title);
    printf("Author: %s\n", book_inventory[index].author);
    printf("Publisher: %s\n", book_inventory[index].publisher);
    printf("Genre: %s\n", book_inventory[index].genre);
    printf("Year of Publication: %d\n", book_inventory[index].year_publication);
    printf("Amount in Stock: %d\n", book_inventory[index].amount_stock);
    printf("Selling Price: %.2f\n\n", book_inventory[index].price);

}

// Print all the book inventory
void print_book_inventory(){

    printf("Total of books in the Inventory : %d/%d\n", amount_books, MAX_INVENTORY);

    for(int i=0; i < amount_books ; i++){ 
        print_book(i);
    }
}

// Pre load demo data for testing
void pre_load_demo_data(){
    
    Book b1 = {isbn_generator, "Information Technology Programmer Analyst", "Thiago Soares de Souza", "LaSalle Publisher", "Information Tachnology", 1989, 5, 149.5};
    isbn_generator++;
    book_inventory[amount_books] = b1;
    amount_books++;

    Book b2 = {isbn_generator, "Algotithms And Programming", "Michelle Khalife", "LaSalle Publisher", "Information Technology", 1992, 10, 192.8};
    isbn_generator++;
    book_inventory[amount_books] = b2;
    amount_books++;

    Book b3 = {isbn_generator, "Head First C#", "Andrew Stellman", "O'Reilly Media, Inc", "Computers, Mathematics, Programming", 2012, 500, 68.15};
    isbn_generator++;
    book_inventory[amount_books] = b3;
    amount_books++;

    Book b4 = {isbn_generator, "Head First Design Patterns", "Eric Freeman & Elisabeth Robson", "O'Reilly Media, Inc", "Computers, Math, Java Programming", 2020, 0, 54.89};
    isbn_generator++;
    book_inventory[amount_books] = b4;
    amount_books++;

    Book b5 = {isbn_generator, "Test to be deleted and generate a space", "Thiago Test", "Test", "test", 2022, 0, 83.48};
    isbn_generator++;
    book_inventory[amount_books] = b5;
    amount_books++;

    delete_book(4, 4);

    Book b6 = {isbn_generator, "Harry Potter and the Philosopher's Stone", "J.K. Rowling", "Bloomsbury Publishing", "Adventure, Fantasy", 2014, 1, 36.90};
    isbn_generator++;
    book_inventory[amount_books] = b6;
    amount_books++;

}

// Search a unique book by ISBN
int search_book(int isbn){
    
    for(int i = 0 ; i < amount_books ; i++){
        if(book_inventory[i].isbn == isbn){
            return i;
        }
    }

    return -1;
}

// Check if the inventory is empty
bool isInventoryEmpty(){
    
    if(amount_books == MIN_INVENTORY){
        return true;
    }

    return false;
}

// Prinf the empty message and set a sleep time of 3 seconds
void print_empty_message(){    
    printf("The inventory of book is empty! Returning to the main menu.");
    sleep(3);
}

// Delete a book using the index
void delete_book(int index, int choice){
    
    Book book_aux;
    
    if(amount_books == MIN_INVENTORY + 1 && index == 0){
        book_aux = book_inventory[index];
    }else{
        for(int i = index ; i < amount_books ; i++){
            book_aux = book_inventory[i];
            book_inventory[i] = book_inventory[i+1];
            book_inventory[i+1] = book_aux;
        }
    }

    print_confirm_operation(choice, NO_TRANSACTION_TYPE);

    print_book_by_book(index , book_aux);

    amount_books--;
}

// Print a single book record receiving a book
void print_book_by_book(int index, Book book){
           
    printf("\nBook inventory number: %d\n\n", index + 1);
    printf("ISBN: %ld\n", book.isbn);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Publisher: %s\n", book.publisher);
    printf("Genre: %s\n", book.genre);
    printf("Year of Publication: %d\n", book.year_publication);
    printf("Amount in Stock: %d\n", book.amount_stock);
    printf("Selling Price: %.2f\n\n", book.price);
}

// Acourding to each operation (Add book, delete book, transactions)
void print_confirm_operation(int choice, int transaction_type){

    display_menu_options(choice, transaction_type);

    printf("The Book was ");

    if(choice == 1){
        printf("\"added\"");
    }else if(choice == 3){
        transaction_type == 1 ? printf("\"purchased\"") : printf("\"returned\"");
    }else if(choice == 4){
        printf("\"deleted\"");
    }

    printf(" correctly. See information below:\n");
}

// Get current_year
int get_current_year(){
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    return tm.tm_year + 1900;
}

// Get first_printed_book_year
int get_first_printed_book_year(){
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    return (tm.tm_year + 1900) - ((tm.tm_year + 1900) - 1452); // 1452 was the first printed book
}

// Check if the string has only blank space
bool has_only_blank_space(char str[], int length){

    int i = 0;

    while(str[i] != '\0' && i <= length){
        if(!isspace(str[i])){
            return false;
        }
        i++;
    }

    return true;
}

// Check if the string has only alpha and blank space
bool has_only_alpha_and_space(char str[], int length){

    int i = 0;

    while(str[i] != '\0' && i <= length){
        if(!isspace(str[i]) && !isalpha(str[i]) ){
            return false;
        }
        i++;
    }

    return true;
}

// Check if the string has at least one letter
bool has_alpha(char str[], int length){
    
    int i = 0;

    while(str[i] != '\0' && i <= length){
        if(isalpha(str[i])){
            return true;
        }
        i++;
    }

    return false;
}

// Remove blank spaces before the string
void trim_string_left(char str[], int length, int limit){

    char str_aux[limit];
    int count = 0;
    int count_left_space = 0;
    int i = 0;

    while(isspace(str[i])){
        if(!isspace(str[i])){
            break;
        }
        count_left_space++;
        i++;
    }

    if(count_left_space != 0){
        for(int i = count_left_space ; i <= length ; i++){
            str_aux[count] = str[i];
            count++;
        }

        strcpy(str, str_aux);
    }

}

// Remove blank spaces after the string
void trim_string_right(char str[], int length, int limit){

    char str_aux[limit];
    int count = 0;
    int count_right_space = length - 1;

    while(isspace(str[count_right_space])){
        
        if(!isspace(str[count_right_space])){
            break;
        }
        
        count_right_space--;
    }

    if(count_right_space != length - 1){
        
        for(int i = 0 ; i <= count_right_space ; i++){
            str_aux[count] = str[i];
            count++;
        }
        str_aux[count_right_space + 1] = '\0';
        strcpy(str, str_aux);

    }

}

// Remove blank spaces between the string
void trim_string_between(char str[], int length, int limit){

    char str_aux[limit];
    int count = 0;
    int count_between_space = 0;

    for(int i = 0 ; i <= length ; i++){
        
        if(isspace(str[i])){
            str_aux[count] = str[i];
            count++;
            count_between_space++;
            i++;
            while(count_between_space > 0 && i < length){
                if(isspace(str[i])){
                    count_between_space++;
                    i++;
                }else{
                    str_aux[count] = str[i];
                    count++;
                    count_between_space = 0;
                }
            }
        }else{
            str_aux[count] = str[i];
            count++;
        }
    }

    strcpy(str, str_aux);
}

// Search for book by keywords (Title, Author, Genre and/or Publisher) and return the number of indexes found
int search_book_by_keywords(char title[], char author[], char genre[], char publisher[], int indexes_found[]){
    
    char title_aux[title_size];
    char author_aux[author_size];
    char genre_aux[genre_size];
    char publisher_aux[publisher_size];

    string_to_lower(title, strlen(title));
    string_to_lower(author, strlen(author));
    string_to_lower(genre, strlen(genre));
    string_to_lower(publisher, strlen(publisher));

    int count_indices = 0;

    for(int i = 0 ; i < amount_books ; i++){

        if(strlen(title) != 0){
            strcpy(title_aux, book_inventory[i].title);
            string_to_lower(title_aux, strlen(title_aux));

            if(strstr(title_aux, title) != NULL){
                print_book(i);
                indexes_found[count_indices] = i;
                count_indices++;
                continue;
            }
        }

        if(strlen(author) != 0){

            strcpy(author_aux, book_inventory[i].author);
            string_to_lower(author_aux, strlen(author_aux));

            if(strstr(author_aux, author) != NULL){
                print_book(i);
                indexes_found[count_indices] = i;
                count_indices++;
                continue;
            }
        }

        if(strlen(genre) != 0){
            
            strcpy(genre_aux, book_inventory[i].genre);
            string_to_lower(genre_aux, strlen(genre_aux));

            if(strstr(genre_aux, genre) != NULL){
                print_book(i);
                indexes_found[count_indices] = i;
                count_indices++;
                continue;
            }
        }

        if(strlen(publisher) != 0){
            
            strcpy(publisher_aux, book_inventory[i].publisher);
            string_to_lower(publisher_aux, strlen(publisher_aux));
            
            if(strstr(publisher_aux, publisher) != NULL){
                print_book(i);
                indexes_found[count_indices] = i;
                count_indices++;
                continue;
            }
        }
    }

    return count_indices;
}

// Convert string to lowercase
void string_to_lower(char str[], size_t length){
    
    for(int i = 0 ; i < length ; i++){
        str[i] = tolower(str[i]);
    }
}

// Get the keyword to do the search by keyword
void get_keywords_search(char title_keyword[], char author_keyword[], char genre_keyword[], char publisher_keyword[]){

    printf("Enter the information below to search the book.\n");

    printf("Enter the Tittle of the book : ");
    fflush(stdin);
    fgets(title_keyword, title_size, stdin);
    title_keyword[strcspn(title_keyword,"\n")] = 0;

    printf("Enter the Author name of the book : ");
    fflush(stdin);
    fgets(author_keyword, author_size, stdin);
    author_keyword[strcspn(author_keyword,"\n")] = 0;

    printf("Enter the Genre of the book : ");
    fflush(stdin);
    fgets(genre_keyword, genre_size, stdin);
    genre_keyword[strcspn(genre_keyword,"\n")] = 0;

    printf("Enter the Publisher name of the book : ");
    fflush(stdin);
    fgets(publisher_keyword, publisher_size, stdin);
    publisher_keyword[strcspn(publisher_keyword,"\n")] = 0;
}

// Purchase a book or books depending of the quantity
void purchase_book(int indexes_found[], int count_found, int choice, int transaction_type){

    char confirm_purchase;
    char question[] = "\nPlease confirm if you would you like to purchase the book (y/n) : ";

    if(count_found > 1){
        // printf("More than 1 book found. Please choose which book(s) do you want to buy.\n");
        int isbn_search;
        int isbn_index;
        bool isListed = false;
        char repeat_buy_list = '\n';
        
        printf("More than 1 book found.\n");

        do{
            repeat_buy_list = '\n';
            isListed = false;

            printf("\nPlease type the ISBN book from the searched list that you want to buy : ");

            isbn_search = get_validate_integer(0, ((isbn_generator - ISBN_GENERATOR_DEFAULT) + ISBN_GENERATOR_DEFAULT) - 1);

            isbn_index = search_book(isbn_search);

            if(isbn_index == -1){
                printf("\nISBN not found!\n");
            }else{
                for(int i = 0 ; i < count_found ; i++){
                    if(isbn_index == indexes_found[i]){
                        isListed = true;
                        break;
                    }
                }

                if(isListed){
                    print_book(isbn_index);

                    if(book_inventory[isbn_index].amount_stock > 0){
                        // char confirm_purchase;
                        // char question[] = "Please confirm if you would you like to purchase the book (y/n) : ";

                        confirm_purchase = get_answer_yes_no(question);

                        if(confirm_purchase == 'y'){
                            book_inventory[isbn_index].amount_stock--;
                            print_confirm_operation(choice, transaction_type);
                            print_book(isbn_index);
                        }else{
                            printf("\nCanceling purchase...\n");
                            sleep(2);
                        }

                    }else{
                        display_menu_options(choice, transaction_type);
                        printf("The book below is out of stock.\n");
                        print_book(isbn_index);
                    }

                }else{
                    printf("\nThe ISBN is not on the searched list shown previously.\n");
                }
            }

            char question_list[] = "\nWould you like to enter another ISBN that match from the previuos searched list ? (y/n) : ";

            repeat_buy_list = get_answer_yes_no(question_list);

        }while(repeat_buy_list == 'y');


    }else{

        if(book_inventory[indexes_found[count_found - 1]].amount_stock > 0){
            // char confirm_purchase;
            // char question[] = "Please confirm if you would you like to purchase the book (y/n) : ";

            confirm_purchase = get_answer_yes_no(question);

            if(confirm_purchase == 'y'){
                book_inventory[indexes_found[count_found - 1]].amount_stock--;
                print_confirm_operation(choice, transaction_type);
                print_book(indexes_found[count_found - 1]);
            }else{
                printf("\nCanceling purchase...\n");
                sleep(2);
            }

        }else{
            display_menu_options(choice, transaction_type);
            printf("The book below is out of stock.\n");
            print_book(indexes_found[count_found - 1]);
        }
    }
}

// Return operation of a book by ISBN if found
void return_book(int isbn, int choice, int transaction_type){

    if(isbn == -1){
        printf("\nISBN not found!\n");
    }else{

        char confirm_purchase;
        char question[] = "\nPlease confirm if you would you like to return the book (y/n) : ";

        print_book(isbn);

        confirm_purchase = get_answer_yes_no(question);

        if(confirm_purchase == 'y'){
            book_inventory[isbn].amount_stock++;
            print_confirm_operation(choice, transaction_type);
            print_book(isbn);
        }else{
            printf("\nCanceling return...\n");
            sleep(2);
        }   
    }
}

