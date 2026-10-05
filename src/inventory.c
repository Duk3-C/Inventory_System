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


// structure for items value management
struct Item
{
    int id;
    char name[40];
    int quantity;
    float price;
};


// declaring inventory management functions
void addItem();
void displayItems();
void searchItems();
void generateID(struct Item *item);
void editItem();
void deleteItem();
void quit();


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


// Random ID generator
void generateID(struct Item *item)
{
    item->id = 1000000 + rand() % 9000000;
}


// Very Self-explanatory
void addItem()
{
    struct Item item = {0};
    FILE *fp; // variable used for interacting with data file

    fp = fopen("inventory.dat", "ab");
    if(fp == NULL) 
    {
        printf("Error opening file\n\n");
        return;
    }


    // Item creation
    printf("\n\nEnter Item Name: ");
    scanf("%s", item.name);
    printf("\n\nEnter Item Quantity: ");
    scanf("%d", &item.quantity);
    printf("\n\nEnter Item Price: ");
    scanf("%f", &item.price);
    generateID(&item);

    // write to data file
    fwrite(&item, sizeof(struct Item), 1, fp);
    fclose(fp);

    sleep(1); // unnecessary but I like wait times between actions
    printf("\n\nItem was added successfully\n\n");

}


// Function pretty much useless since I have the view_inventory.py 
// for the same purpose, just wanted to add it inside the program LOL
void displayItems()
{
    struct Item item;
    FILE *fp;

    fp = fopen("inventory.dat", "rb");
    if(fp == NULL)
    {
        printf("Error opening file\n\n");
        return;
    }

    // Note for people that may want to use the .py file instead
    printf("Items can also be displayed out of the program through the view_inventory.py program, \nwhich will read and output all items info like this option\n\n");
    sleep(1);

    printf("ID\tName\tQuantity\tPrice\n");
    printf("-----------------------------------\n\n");

    while(fread(&item, sizeof(struct Item), 1, fp))
    {
        // Display Item Info
        printf("%d\t%s\t%d\t\t$%.2f\n", 
                item.id, item.name, item.quantity, item.price);
    }

    fclose(fp);
}

void searchItems()
{
    struct Item item;
    FILE *fp;
    int id, found = 0; // int found is basically a boolean
                       // I didn't want to use the stdbool.h file 
                       // for this, so instead I used the good old way

    fp = fopen("inventory.dat", "rb");
    if(fp == NULL) 
    {
        printf("Error opening file\n\n");
        return;
    }

    printf("Enter Item ID: ");
    scanf("%d", &id);

    while(fread(&item, sizeof(struct Item), 1, fp))
    {
        if(item.id == id)
        {
            // Display Item Info
            printf("%d\t%s\t%d\t\t%.2f\n", 
                    item.id, item.name, item.quantity, item.price);
            found = 1; // found returns true
            break;
        }
    }

    // Error Handling
    if(found != 1)
    {
        printf("\nItem was not found\n\n");
    }

    fclose(fp);
}

void editItem()
{
    int in_menu;
    int id, found = 0;
    system("clear");

    // item needs to be set to 0 for this use case
    // same as in addItem()
    struct Item item = {0};
    FILE *fp;

    fp = fopen("inventory.dat", "r+b");
    if(fp == NULL)
    {
        printf("Error opening file\n\n");
        return;
    }

    printf("\nEnter ID number: ");
    scanf("%d", &id);

    while(fread(&item, sizeof(struct Item), 1, fp))
    {
        if(item.id == id)
        {
            found = 1;

            // displaying item info for the user to verify whether it is the right one
            printf("\nCurrent Item:\n");
            printf("ID: %d  |   Name: %s    |   Quantity: %d    |   Price: $%.2f\n\n",
                    item.id,    item.name,      item.quantity,      item.price);


            printf("What would you like to edit?\n");
            printf(" 1> Name\n");
            printf(" 2> Quantity\n");
            printf(" 3> Price\n");
            scanf("%d", &in_menu);
            
            // The input goes directly to the exact item value
            // that is used
            switch(in_menu)
            {
                case 1:
                    printf("\n\nEnter new item name\n");
                    scanf("%s", item.name);
                    break;
                case 2:
                    printf("\n\nEnter new item quantity\n");
                    scanf("%d", &item.quantity);
                    break;
                case 3:
                    printf("\n\nEnter new item price\n");
                    scanf("%f", &item.price);
                    break;
                case 4:
                    fclose(fp);
                    return;
                default:
                    printf("Invalid Choice\n\n");
                    fclose(fp);
                    return;
            }

            // Writing changes to data file
            fseek(fp, -sizeof(struct Item), SEEK_CUR);
            fwrite(&item, sizeof(struct Item), 1, fp);
            printf("Item successfully updated\n\n");
            break;
        }

        if(found != 1)
        {
            printf("Item not found\n\n");
        }

        fclose(fp);
    }

}

void deleteItem()
{
    struct Item item;
    int id, found = 0;
    FILE *fp, *temp;

    fp = fopen("inventory.dat", "rb");
    if(fp == NULL)
    {
        printf("Error opening inventory file\n");
        return;
    }

    // a temporary file is used for writing new data 
    // into it, leaving the obsolete item in the 
    // previous inventory.dat file
    temp = fopen("temp.dat", "wb");
    if(temp == NULL)
    {
        printf("Error opening temporary file\n");
        return;
    }

    printf("Enter item ID to delete: ");
    scanf("%d", &id);

    while(fread(&item, sizeof(struct Item), 1, fp)) 
    {
        if(item.id != id)
        {
            fwrite(&item, sizeof(struct Item), 1, temp);
        } else 
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat"); // After inventory.dat is removed
                                         // temp.dat gets renamed so that
                                         // it becomes the main data file
    
    if(found)
    {
        printf("Item deleted successfully\n\n");
    } else
    {
        printf("Item not found\n\n");
    }
}

// Very simple function to exit the program
void quit()
{
    printf("Exiting Program...\n\n");
    sleep(1);
    exit(0);
}
