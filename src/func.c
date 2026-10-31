#include "func.h"
#include <bits/getopt_core.h>
#include <bits/getopt_ext.h>


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

void parser(int argc, char **argv)
{
    int command;
    while((command = getopt_long(argc, argv, "ha:le:d:f:", opts, NULL)) != -1)
    {
        switch(command)
        {
            case 'h':   cmd_help();     break;
            case 'a':   cmd_add_item(optarg);      break;
            case 'l':   cmd_list();     break;
            case 'e':   cmd_edit();     break;
            case 'd':   cmd_delete();   break;
            case 'f':   cmd_find();     break;
            default:                    break;
        }
    }
}

void cmd_help()
{
    printf("Usage: ./inventory [OPTIONS]\n"
           "--add [SKU, NAME, QUANTITY, PRICE]                     - Add a new item\n"
           "--list                                                 - Lists all items inside the inventory database\n" 
           "--edit [SKU] SKU || NAME || QUANTITY || PRICE              - Edit an item, either its name, SKU, price, or quantity\n"
           "--delete [SKU]                                         - Delete an item\n"
           "--find [SKU]                                           - Find an item by its SKU\n"
            );
    return;
}

void cmd_add_item(char *text)
{
    struct Item *item;
    FILE *fp = fopen(DATA_FILE, "wb");
    if(fp == NULL)
    {
        printf("file was not found\n");
    }

    if(!text) { printf("incomplete input; refer to --help to see available options\n"); }; 

}
