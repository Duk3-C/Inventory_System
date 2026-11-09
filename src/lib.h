#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <strings.h>

#define ITEM_NAME_LEN   256
#define SKU_LEN         15  // 14 chars + '\0' NULL
#define DATA_FILE       "inventory.dat"
#define TEMP_FILE       "inventory.dat.tmp"

typedef struct {
    char    SKU[SKU_LEN];
    char    name[ITEM_NAME_LEN];
    int     quantity;
    double  price;
} Item;

typedef enum { FIELD_SKU, FIELD_NAME, FIELD_QUANTITY, FIELD_PRICE } Field;

static int parse_field(const char *name, Field *field)
{
    if(strcasecmp(name, "SKU")      == 0)       { *field = FIELD_SKU;       return 0; }
    if(strcasecmp(name, "NAME")     == 0)       { *field = FIELD_NAME;      return 0; }
    if(strcasecmp(name, "QUANTITY") == 0)       { *field = FIELD_QUANTITY;  return 0; }
    if(strcasecmp(name, "PRICE")    == 0)       { *field = FIELD_PRICE;     return 0; }
    return -1;
}

void parser(int argc, char **argv);
void cmd_help();
void cmd_add_item(char *text);
void cmd_list();
void cmd_search();
void cmd_edit(char *text);
void cmd_delete(char *text);
void cmd_find(); // same as searchItem function in the TUI version of the program

#endif
