#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

static struct option const OPTIONS_LONG[] = {
    { "help",   no_argument,    NULL,   'h' },
    { "newlist",    required_argument,  NULL,   NULL },
    { "ls",     required_argument,  NULL,   NULL },
    { "add",    required_argument,  NULL,   'a' },
    { "name",   required_argument,  NULL,   'n' },
    { "quant",  required_argument,  NULL,   'q' },
    { "price",  required_argument,  NULL,   'p' },
};
static char const OPTIONS_SHORT[] = ":ha:n:q:p:";



int main(int argc, char *argv[])
{ 
    return 0;
}
