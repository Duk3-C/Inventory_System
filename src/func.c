#include "func.h"
#include <bits/getopt_core.h>
#include <bits/getopt_ext.h>
#include <stdio.h>


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
            //case 'e':   cmd_edit();     break;
            //case 'd':   cmd_delete();   break;
            //case 'f':   cmd_find();     break;
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
    Item item = {0};

    if(sscanf(text, "%14[^,], %255[^,], %d, %lf",
                item.SKU, item.name, &item.quantity, &item.price) != 4)
    {
        fprintf(stderr, 
                "Usage: --add \"SKU,NAME,QUANTITY,PRICE\"\n"
                "       --help to learn more\n");
        return;
    }

    if(item.quantity < 0 || item.price < 0)
    {
        fprintf(stderr,
                "Invalid amount entered\n");
        return;
    }

    FILE *fp_existing = fopen(DATA_FILE, "rb");
    if(fp_existing != NULL)
    {
        Item existing;
        while(fread(&existing, sizeof existing, 1, fp_existing) == 1) 
        {
            if(strcmp(existing.SKU, item.SKU) == 0)
            {
                fclose(fp_existing);
                fprintf(stderr,
                        "SKU %s already exists\n",
                        item.SKU);
                return;
            }
        }
        fclose(fp_existing);
    }

    FILE *fp = fopen(DATA_FILE, "ab");
    if(fp == NULL) { perror(DATA_FILE); return; }
    
    if(fwrite(&item, sizeof item, 1, fp) != 1) { perror("fwrite"); }
    fclose(fp);
}

void cmd_list()
{
    Item item;
    FILE *fp = fopen(DATA_FILE, "rb");
    
    if(fp == NULL) { fprintf(stderr, "No contents in inventory\n"); return; }

    printf("%-15s | %-30s | %8s | %10s\n",
            "SKU", "NAME", "QUANTITY", "PRICE");
    printf("---------------------------------------------------------------\n");

    while(fread(&item, sizeof item, 1, fp) == 1)
    {
        printf("%-15s | %-30s | %8d | %10.2f",
                item.SKU, item.name, item.quantity, item.price);
    }

    fclose(fp);

}
