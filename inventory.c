#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct Item
{
    int id;
    char name[40];
    int quantity;
    float price;
};

void addItem();
void displayItems();
void searchItems();
void generateID(struct Item *item);
void editItem();

/* TODO
void deleteItem();
void quit();
*/

int main(void) 
{
    system("clear");
    srand((unsigned)time(NULL));

    char in_menu;

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
        /*case '5':
            deleteItem();
            break;
        case 'q':
            quit();
            break;
        case 'Q':
            quit();
            break;
        */
        default:
            printf("Invalid Response, Please try again\n\n");
            sleep(2);
            main();
    }
    return 0;
}

// Random ID generator
void generateID(struct Item *item)
{
    item->id = 1000000 + rand() % 9000000;
}

void addItem()
{
    struct Item item = {0};
    FILE *fp;

    fp = fopen("inventory.dat", "ab");
    if(fp == NULL) 
    {
        printf("Error opening file\n\n");
        return;
    }

    printf("\n\nEnter Item Name: ");
    scanf("%s", item.name);
    printf("\n\nEnter Item Quantity: ");
    scanf("%d", &item.quantity);
    printf("\n\nEnter Item Price: ");
    scanf("%f", &item.price);
    generateID(&item);

    fwrite(&item, sizeof(struct Item), 1, fp);
    fclose(fp);

    sleep(1);
    printf("\n\nItem was added successfully\n\n");
}

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
    printf("Items can also be displayed out of the program through the view_inventory.py program, \nwhich will read and output all items info like this option\n\n");
    sleep(1);

    printf("ID\tName\tQuantity\tPrice\n");
    printf("-----------------------------------\n\n");

    while(fread(&item, sizeof(struct Item), 1, fp))
    {
        // Display Item Info
        printf("%d\t%s\t%d\t\t$%.2f\n", item.id, item.name, item.quantity, item.price);
    }

    fclose(fp);
}

void searchItems()
{
    struct Item item;
    FILE *fp;
    int id, found = 0;

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
            printf("%d\t%s\t%d\t\t%.2f\n", item.id, item.name, item.quantity, item.price);
            found = 1;
            break;
        }
    }

    if(found != 1)
    {
        printf("\nItem was not found\n\n");
    }

    fclose(fp);
}

void editItem()
{
    int in_menu;
    system("clear");
    struct Item item = {0};
    FILE *fp;

    fp = fopen("inventory.dat", "r+b");
    if(fp == NULL)
    {
        printf("Error opening file\n\n");
        return;
    }



    printf("\nWhat would you like to do?\n");
    printf("-------------------------------------\n");
    printf("1 > Edit Item's name\n");
    printf("2 > Edit Item's quantity\n");
    printf("3 > Edit Item's price\n");
    printf("4 > Create a new ID for the item\n");
    printf("5 > Go back to main menu\n");
    scanf("%d", &in_menu);

    switch(in_menu) 
    {
        case 1:
            system("clear");
            printf("Enter new item's name: ");
            scanf("%s", item.name);
            while(fread(&item, sizeof(struct Item), 1, fp))
            {
                fseek(fp, -sizeof(struct Item), SEEK_CUR);
                fwrite(&item, sizeof(struct Item), 1, fp);
            }
            break;
        case 2:
            system("clear");
            printf("Enter new item's quantity: ");
            scanf("%d", &item.quantity);
            while(fread(&item, sizeof(struct Item), 1, fp))
            {
                fseek(fp, -sizeof(struct Item), SEEK_CUR);
                fwrite(&item, sizeof(struct Item), 1, fp);
            }
            break;
        case 3:
            break;
        case 4:
            generateID(&item);
            break;
        case 5:
            main();
            break;
        default:
            printf("\n\nInvalid Answer; please try again");
            editItem();
            break;
    }
}
