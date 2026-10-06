/* TODO
    [X] - check debugger for errors
    [X] - add comments to give more context of each function
    [ ] - Implement cli functionality
    [ ] - Implement a better way of accounting item IDs
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "func.h"


// Main Function
int main(void) 
{
    system("clear");
    
    // Random Seed
    srand((unsigned)time(NULL));


    // TUI menu
    char in_menu;

    // do while loop to make the program 
    // go back to main menu after completing 
    // a task
    do {
        printf("\n\n\n");
        printf("================================================\n");
        printf("=         Inventory Management System          =\n");
        printf("================================================\n\n");
        printf("  Options:\n\n");
        printf("------------------------------------------------\n\n");
        printf("  1 > Add a new item\n");
        printf("  2 > Display Items\n");
        printf("  3 > Search Items\n");
        printf("  4 > Edit an Item\n");
        printf("  5 > Delete an Item\n");
        printf("  q/Q > Exit the program\n\n");
        scanf("%c", &in_menu);
        switch (in_menu) 
        {
            case '1':
                addItem();
                break;
            case '2':
                displayItems();
                break;
            case '3':
                searchItems();
                break;
            case '4':
                editItem();
                break;
            case '5':
                deleteItem();
                break;
            case 'q':
                quit();
                break;
            case 'Q':
                quit();
                break;
            default:
                printf("Invalid Response, Please try again\n\n");
                sleep(2);
                main();
        }
    } while(in_menu != 'q' && in_menu != 'Q');

    return 0;
}
