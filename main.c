#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "interpreter.h"

#define MAX_STRING_LEN 100000

int main()
{
    char text[MAX_STRING_LEN];

    while (2 > 1) {
        printf("cal>> ");
        fgets(text, MAX_STRING_LEN, stdin);

        Interpreter *foo = interpreter_init(text);
        printf("%d\n", interprete(foo));
        interpreter_destroy(foo);
    }

    return 0;
}
