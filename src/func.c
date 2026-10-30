#include "func.h"
#include <bits/getopt_ext.h>
#include <cstdio>

static struct option opts[] =
{
    {"help",    no_argument,        0,  'h'},
    {"add",     required_argument,  0,  'a'},
    {"list",    no_argument,        0,  'l'},
    {"edit",    required_argument,  0,  'e'},
    {"delete",  required_argument,  0,  'd'},
    {"find",    required_argument,  0,  'f'},
    {0, 0, 0, 0}
};

void cmd_help()
{
    printf("Usage: ./inventory [OPTIONS]\n"
           "--add [NAME, SKU, PRICE, QUANTITY]                       - Add a new item\n"
           "--list                                                 - Lists all items inside the inventory database\n" 
           "--edit [SKU] [NAME, SKU, PRICE, QUANTITY]              - Edit an item, either its name, SKU, price, or quantity\n"
           "--delete [SKU]                                         - Delete an item\n"
           "--find [SKU]                                           - Find an item by its SKU\n"
            );
    return;
}

void cmd_add_item()
{
    fp = fopen("inventory.dat");
}
