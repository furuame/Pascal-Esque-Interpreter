#include "interpreter.h"
#include <string.h>

Interpreter *interpreter_init(const char *text)
{
    Interpreter *interpreter = (Interpreter *) malloc(sizeof(Interpreter));
    if (!interpreter) {
        printf("interpreter.c: No availabe memory for use\n");
        exit(0);
    }

    interpreter->parser = parser_init(text);

    return interpreter;
}

void interpreter_destroy(Interpreter *interpreter)
{
    parser_destroy(interpreter->parser);
    free(interpreter);
}

int interprete(Interpreter *interpreter)
{
    parse(interpreter->parser);
    return visit(interpreter->parser->ast); 
}
