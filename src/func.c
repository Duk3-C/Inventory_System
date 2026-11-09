#include "lib.h"
#include <bits/getopt_core.h>
#include <bits/getopt_ext.h>
#include <limits.h>
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
            case 'e':   cmd_edit(optarg);     break;
            case 'd':   cmd_delete(optarg);   break;
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
           "--edit 'SKU new FIELD NEW_VALUE'\n                     - Edit an item, either its name, SKU, price, or quantity. No more than one value can be changed at a time at the moment\n"
           "                                                         FIELDS: SKU,   NAME,   QUANTITY,   PRICE\n"
           "--delete [SKU]                                         - Delete an item\n"
           "--find [SKU]                                           - Find an item by its SKU\n"
            );
    return;
}

void cmd_add_item(
        char *text)
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

void cmd_list(void)
{
    Item item;
    FILE *fp = fopen(DATA_FILE, "rb");
    
    if(fp == NULL) { fprintf(stderr, "No contents in inventory\n"); return; }

    printf("%-15s | %-30s | %8s | %10s\n",
            "SKU", "NAME", "QUANTITY", "PRICE");
    printf("---------------------------------------------------------------\n");

    while(fread(&item, sizeof item, 1, fp) == 1)
    {
        printf("%-15s | %-30s | %8d | %10.2f\n",
                item.SKU, item.name, item.quantity, item.price);
    }
    fclose(fp);
}

void cmd_edit(char *text)
{
    // Parser variables
    char cur_sku[SKU_LEN];
    char keyword[8]; // 'new' keyword
    char field_name[16];
    char value[ITEM_NAME_LEN];
    Field field;

    if(sscanf(text, "%14s %7s %15s %255[^\n]",
                cur_sku, keyword, field_name, value) != 4 ||
            sscanf(keyword, "new") != 0)
    {
        fprintf(stderr, "Usage: --edit \"SKU new FIELD NEW_VALUE\"\n"
                        "       FIELD: SKU, NAME, QUANTITY, PRICE\n"
                        "       For more info, use --help\n"
                );
        return;
    }

    if(parse_field(field_name, &field) != 0)
    {
        fprintf(stderr, "Unknown field %s\n", field_name);
        return;
    }

    // Validating fields

    int new_quantity = 0;
    double new_price = 0.0;

    switch(field)
    {
        case FIELD_SKU:
            if(value[0] != '\0' || strlen(value) >= SKU_LEN)
            {
                fprintf(stderr,
                        "Value can only be of size 1-%d\n",
                        SKU_LEN-1);
                return;
            }
            break;
        case FIELD_NAME:
            if(value[0] != '\0' || strlen(value) >= ITEM_NAME_LEN)
            {
                fprintf(stderr,
                        "Value has to be of size 1-%d\n",
                        ITEM_NAME_LEN-1);
                return;
            }
            break;
        case FIELD_QUANTITY:
        {
            char *end;
            errno = 0;
            long quant = strtol(value, &end, 10);
            if(errno != 0 || end == value || *end != '\0' || quant < 0 || quant > INT_MAX) 
            {
                fprintf(stderr,
                        "Quantity must be a non-negative integer\n");
                return;
            }
            new_quantity = (int)quant;
            break;
        }
        case FIELD_PRICE:
        {
            char *end;
            errno = 0;
            double price = strtod(value, &end);
            if(errno != 0 || end == value || *end != '\0' || !isfinite(price) || price < 0.0)
            {
                fprintf(stderr,
                        "Price must be a non-negative number\n");
                return;
            }
            break;
        }
    }

    FILE *in = fopen(DATA_FILE, "rb");
    if(in == NULL)
    {
        fprintf(stderr,
                "No inventory found\n");
        return;
    }

    FILE *out = fopen(TEMP_FILE, "wb");
    if(out == NULL)
    {
        perror(TEMP_FILE);
        fclose(in); // if second condition fails, close first file
        return;
    }

    Item item;
    int found = 0;
    int failed = 0;
    int collision = 0;

    while(fread(&item, sizeof item, 1, in) == 1)
    {
        if(!found && strcmp(item.SKU, cur_sku) == 0)
        {
            found = 1;
            switch(field)
            {
                case FIELD_SKU:
                    snprintf(item.SKU, sizeof item.SKU, "%s", value);
                    break;
                case FIELD_NAME:
                    snprintf(item.name, sizeof item.name, "%s", value);
                    break;
                case FIELD_QUANTITY:
                    item.quantity = new_quantity;
                    break;
                case FIELD_PRICE:
                    item.price = new_price;
                    break;
            }
        } else if (field == FIELD_SKU && strcmp(item.SKU, value) == 0)
        {
            collision = 1; // This means the new SKU entered by the user already belongs to another item
        }

        if(fwrite(&item, sizeof item, 1, out) != 1)
        {
            failed = 1;
            break;
        }
    }

    if(ferror(in)) 
        failed =1;

    fclose(in);
    if(fclose(out) != 0)
        failed = 1;

    if(failed)
    {
        remove(TEMP_FILE);
        fprintf(stderr,
                "Edit failed. Inventory left unchanged\n");
        return;
    }
    if(!found)
    {
        remove(TEMP_FILE);
        fprintf(stderr,
                "SKU %s not found\n", cur_sku);
        return;
    }
    if(collision)
    {
        remove(TEMP_FILE);
        fprintf(stderr,
                "SKU %s already exists\n", cur_sku);
        return;
    }

    if(rename(TEMP_FILE, DATA_FILE) != 0)
    {
        perror("rename");
        remove(TEMP_FILE);
        return;
    }

    printf("Updated %s: %s = %s\n", cur_sku, field_name, value);

}

void cmd_delete(char *text)
{
    Item item;
    char sku[64];

    if(sscanf(text, "%63s", sku) != 1 || strlen(sku) >= SKU_LEN)
    {
        fprintf(stderr,
                "Usage: --delete \"SKU\"\n"
                "       --help for more info\n");
        return;
    }

    FILE *in = fopen(DATA_FILE, "rb"); 
    if(in == NULL)
    {
        fprintf(stderr,
                "No inventory found\n");
        return;
    }

    FILE *out = fopen(TEMP_FILE, "wb");
    if(in == NULL)
    {
        perror(TEMP_FILE);
        fclose(in);
        return;
    }

    int found = 0;
    int failed = 0;

    while(fread(&item, sizeof item, 1, in) == 1)
    {
        if(strcmp(item.SKU, sku) == 0)
        {
            found = 1;
            continue;
        }

        if(fwrite(&item, sizeof item, 1, out) != 1)
        {
            failed = 1;
            break;
        }

    }

    if(ferror(in))
        failed = 1;

    fclose(in);
    if(fclose(out) != 0)
        failed = 1;

    if(failed)
    {
        remove(TEMP_FILE);
        fprintf(stderr,
                "Delete failed\n");
        return;
    }

    if(!found)
    {
        remove(TEMP_FILE);
        fprintf(stderr,
                "Item not found, no changes were made\n");
        return;
    }

    if(rename(TEMP_FILE, DATA_FILE) != 0)
    {
        perror("rename");
        remove(TEMP_FILE);
        return;
    }

    printf("Item %s was successfully deleted\n", sku);

}
