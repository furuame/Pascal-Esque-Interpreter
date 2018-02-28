#ifndef NODE_H_
#define NODE_H_

#include "token.h"

typedef enum {
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_NUM
} AST_NODE_TYPE;

typedef struct __binary_operation_node BinNode_t;
struct __binary_operation_node {
    AST_NODE_TYPE type;
    token_t op;
    void *left;
    void *right;
};

typedef struct __number_node NumNode_t;
struct __number_node {
    AST_NODE_TYPE type;
    token_t operand;
};

typedef struct __unary_node UnaryNode_t;
struct __unary_node {
    AST_NODE_TYPE type;
    token_t op;
    void *expr;
};

int visit(void *node);
void free_node(void *node);

#endif
