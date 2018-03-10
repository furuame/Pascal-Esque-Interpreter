#include "interpreter.h"
#include "symtable.h"
#include <string.h>

Interpreter *interpreter_init(const char *text)
{
    Interpreter *interpreter = (Interpreter *) malloc(sizeof(Interpreter));
    if (!interpreter) {
        printf("interpreter.c: No availabe memory for use\n");
        exit(0);
    }

    interpreter->parser = parser_init(text);
    interpreter->symtable = symt_init();

    return interpreter;
}

void interpreter_destroy(Interpreter *interpreter)
{
    symt_destroy(interpreter->symtable);
    parser_destroy(interpreter->parser);
    free(interpreter);
}

int interprete(Interpreter *interpreter)
{
    parse(interpreter->parser);
    visit(interpreter->parser->ast, interpreter->symtable);
    print_symt(interpreter->symtable);
    return 0;
}
