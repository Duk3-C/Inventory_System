#include <stdio.h>
#include <unistd.h>

// Defining true and false since I don't want to use stdbool.h
#define TRUE 1
#define FALSE 0

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
/* TODO
void editItem();
void deleteItem();
void quit();
*/

int main(void) 
{

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
    /*case '4':
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
    */
    default:
      printf("Invalid Response, Please try again\n\n");
  }
  return 0;
}

void addItem()
{
  struct Item item;
  FILE *fp;

  fp = fopen("Inventory.dat", "ab");
  if(fp == NULL) 
  {
    printf("Error opening file\n\n");
    return;
  }

  printf("Enter Item ID: ");
  scanf("%d", &item.id);
  printf("\n\nEnter Item Name: ");
  scanf("%s", item.name);
  printf("\n\nEnter Item Quantity: ");
  scanf("%d", &item.quantity);
  printf("\n\nEnter Item Price: ");
  scanf("%f", &item.price);

  fwrite(&item, sizeof(struct Item), 1, fp);
  fclose(fp);

  sleep(1);
  printf("\n\nItem was added successfully\n\n");
}

void displayItems()
{
  struct Item item;
  FILE *fp;

  fp = fopen("Inventory.dat", "rb");
  if(fp == NULL)
  {
    printf("Error opening file\n\n");
    return;
  }

  printf("ID\tName\tQuantity\tPrice\n");
  printf("-----------------------------------\n\n");

  while(fread(&item, sizeof(struct Item), 1, fp))
  {
    // Display Item Info
    printf("%d\t%s\t%d\t\t%.2f\n", item.id, item.name, item.quantity, item.price);
  }

  fclose(fp);
}

void searchItems()
{
  struct Item item;
  FILE *fp;
  int id, found = FALSE;

  fp = fopen("Inventory.dat", "rb");
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
      found = TRUE;
      break;
    }
  }

  if(found != TRUE)
  {
    printf("\nItem was not found\n\n");
  }

  fclose(fp);
}
