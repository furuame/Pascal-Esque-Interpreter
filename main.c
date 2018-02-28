#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "interpreter.h"

#define MAX_STRING_LEN 100000

int main(int argc, char *argv[])
{
    char text[MAX_STRING_LEN];

    if (argc < 2) {
        printf("Please specify input file\n");
        exit(0);
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("This file doesn't exists\n");
        exit(0);
    }

    fread(text, sizeof(char), MAX_STRING_LEN, fin);

    //fgets(text, MAX_STRING_LEN, stdin);

    Interpreter *foo = interpreter_init(text);
    interprete(foo);
    //printf("%d\n", interprete(foo));
    interpreter_destroy(foo);

    return 0;
}
