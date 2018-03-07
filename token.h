#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    /* DECLARATION */
    INTEGER_DECL,
    REAL_DECL,
    /* Constant */
    INTEGER_CONST,
    REAL_CONST,
    /* Operator */
    PLUS,
    MINUS,
    MULTIPLY,
    INTEGER_DIVIDE,
    REAL_DIVIDE,
    POWER,
    /* Reserved Words */
    PROGRAM,
    VAR,
    BEGIN,
    END,
    /* Identifier */
    ID,
    /* Special Characters */
    ASSIGN,
    SEMI,
    DOT,
    LPAREN,
    RPAREN,
    COMMA,
    COLON,
    NONE
} TYPE;

typedef struct __token token_t;

struct __token {
    TYPE type;
    void *value;
};

#endif
