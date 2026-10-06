#ifndef OPTIONS
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct Item
{
    char SKU[14];
    char name[40];
    int quantity;
    float price;
};

void generateID(struct Item *item);
void addSKU();
void addItem();
void displayItems();
void searchItems();
void editItem();
void deleteItem();
void quit();

#endif // !OPTIONS
