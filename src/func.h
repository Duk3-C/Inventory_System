#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ITEM_NAME_LEN   256
#define SKU_LEN         15  // 14 chars + '\0' NULL
#define DATA_FILE       "inventory.dat"

typedef struct {
    char    SKU[SKU_LEN];
    char    name[ITEM_NAME_LEN];
    int     quantity;
    double  price;
} Item;

void parser(int argc, char **argv);
void cmd_help();
void cmd_add_item(char *text);
void cmd_list();
void cmd_search();
void cmd_edit();
void cmd_delete();
void cmd_find(); // same as searchItem function in the TUI version of the program

#endif
