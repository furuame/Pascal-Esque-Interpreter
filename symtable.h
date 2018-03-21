#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include "token.h"

#define _MAX_SYMT_ENTRY 100

/*
typedef enum {
    TYPE_INTEGER,
    TYPE_FLOAT
} VARIABLE_TYPE;
*/

typedef struct __symbol_table_entry SYMT_ENTRY;
struct __symbol_table_entry {
    char *name;
    TYPE type;
    int value;
};

typedef struct __symbol_table SYMT;
struct __symbol_table {
    SYMT_ENTRY entry[_MAX_SYMT_ENTRY];
    int num;
};

void add_symt_entry(SYMT *symtable, char *text, TYPE type);
void set_symt_value(SYMT *symtable,
                    char *text, /*VARIABLE_TYPE type,*/
                    int value);
int get_symt_value(SYMT *symtable, char *text);
SYMT *symt_init(void);
void symt_destroy(SYMT *symtable);
void print_symt(SYMT *symtable);
#endif
