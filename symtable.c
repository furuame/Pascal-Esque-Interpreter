#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add_symt_entry(SYMT *symtable, char *text, TYPE type)
{
    for (int i = 0; i < symtable->num; i++) {
        if (strcmp(text, symtable->entry[i].name) == 0) {
            printf("Duplicate Declaration\n");
            exit(0);
        }
    }

    if (symtable->num == _MAX_SYMT_ENTRY) {
        printf("Too much Symbol\n");
        exit(0);
    }

    symtable->entry[symtable->num].name = text;
    symtable->entry[symtable->num].type = type;
    symtable->entry[symtable->num].value = 0;
    symtable->num += 1;

}

void set_symt_value(SYMT *symtable, char *text, \
                    /*VARIABLE_TYPE type, \*/
                    int value)
{
    for (int i = 0; i < symtable->num; i++) {
        if (strcmp(text, symtable->entry[i].name) == 0) {
            /*
            if (symtable->entry[i].type != type) {
                printf("Wrong type assignment\n");
                exit(0);
            }
            */
            symtable->entry[i].value = value;
            return;
        }
    }

    printf("This variable %s doesn't declare in advance\n", text);
    exit(0);
}

int get_symt_value(SYMT *symtable, char *text)
{
    for (int i = 0; i < symtable->num; i++) {
        if (strcmp(text, symtable->entry[i].name) == 0) {
            return symtable->entry[i].value;
        }
    }

    printf("This variable \"%s\" not initialized\n", text);
    exit(0);
}

SYMT *symt_init(void)
{
    SYMT *symtable = (SYMT *) malloc(sizeof(SYMT));
    if (!symtable) {
        printf("symtable.c: Not availabe malloc\n");
        exit(0);
    }
    return symtable;
}

void symt_destroy(SYMT *symtable)
{
    free(symtable);
}

void print_symt(SYMT *symtable)
{
    printf("===== Symbol Table =====\n");
    for (int i = 0; i < symtable->num; i++) {
        printf("%s: %d\n", symtable->entry[i].name, symtable->entry[i].value);
    }
    printf("========================\n");
}
