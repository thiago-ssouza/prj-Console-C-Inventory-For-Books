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
// #include <time.h>


// #define PLAYER_X 'X'
// #define PLAYER_O 'O'
// #define MAXIMUM_SIZE 10
// #define MINIMUM_SIZE 3



// Fuction Declaration

// Validate repeat opetation
char validate_repeat_operation(int);

// Get and validate if the number is a valid integer (Inspired in camilo's code in the calculator program, presented during the class)
int get_validate_integer(int, int);

// Print Tic-Toc-Toe Passing a Matrix
// void printf_tic_tac_toe(char[row][column]);

// Print the title of the user choice (Player vs Player, Player vs Machine, Machine vs Machine)
void display_menu_options(int);

int main(){

    int choice = -1;
    char repeat_operation = '\n';   
    
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
            case 2:
            case 3:
            case 4:
            case 5:
                do{
                    // system("cls");

                    // printf("\t\t\t      TIC-TAC-TOE GAME\n");

                    // print_title_user_choice(choice);

                    // printf("\t\t\t -----------------------------\n\n");

                    display_menu_options(choice);

                    // initialize_reset_tic_tac_toe(tic_tac_toe);

                    // printf_tic_tac_toe(tic_tac_toe);

                    // play_game(tic_tac_toe, choice);

                    repeat_operation = validate_repeat_operation(choice);

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
char validate_repeat_operation(int choice){

    char repeat_operation;

    do{
        
        printf("\nDo you want to proceed with the ");

        if(choice == 1){
            printf("\"Populate the inventory\"");
        }else if(choice == 2){
            printf("\"Search by keywords\"");
        }else if(choice == 3){
            printf("\"Process a transaction\"");
        }else if(choice == 4){
            printf("\"Delete a book record\"");
        }else if(choice == 5){
            printf("\"Display all books in the inventory\"");
        }

        printf(" operation again ? (y/n) : ");
        
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
void display_menu_options(int choice){

    system("cls");    
    
    printf("\t\t\t      INVENTORY OF BOOKS\n");
    
    if(choice == 1){
        printf("\t\t\t    Populate the inventory\n");
    }else if(choice == 2){
        printf("\t\t\t      Search by keywords\n");
    }else if(choice == 3){
        printf("\t\t\t    Process a transaction\n");
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

    printf("\n");

    return number;
}

// Print Tic-Toc-Toe Passing a Matrix
// void printf_tic_tac_toe(char tic_tac_toe[row][column]){
    
//     printf("\n");

//     for(int i = 0 ; i < row ; i++){
//         for(int j = 0 ; j < column ; j++){
        
//             if( ( (tic_tac_toe[i][j] != 'X' && tic_tac_toe[i][j] != 'O') || (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == false) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == false)) && tic_tac_toe[i][j] >= 10){

//                 if(j > 0){
//                     printf("|  ");
//                 }else{
//                     printf("  ");
//                 }

//             }else{
                
//                 if(j > 0){
//                     printf("|   ");
//                 }else{
//                     printf("   ");
//                 }
//             }

//             if( ( (tic_tac_toe[i][j] == 'X' && (idx_i_x_played != i || idx_j_x_played != j)) || (tic_tac_toe[i][j] == 'O'  && (idx_i_o_played != i || idx_j_o_played != j)) ) || ( (tic_tac_toe[i][j] == 'X' && idx_i_x_played == i && idx_j_x_played == j && wasPlayedX == true) || (tic_tac_toe[i][j] == 'O' && idx_i_o_played == i && idx_j_o_played == j && wasPlayedO == true) ) ){
//                 printf("%c", tic_tac_toe[i][j]);
//             }else{
//                 printf("%d", tic_tac_toe[i][j]);
//             }
            
//             printf("  ");
//         }
        
//         if(i != row - 1){
            
//             printf("\n");

//             for(int c = 1 ; c <= column ; c++){
//                 if(c == 1){
//                     printf("______");
//                 }else{
//                     printf("|______");
//                 }
//             }

//             printf("\n");

//         }else{

//             printf("\n");

//             for(int c = 1 ; c <= column ; c++){
//                 if(c == 1){
//                     printf("      ");
//                 }else{
//                     printf("|      ");
//                 }
//             }

//             printf("\n");

//         }
        
//     }

// }

