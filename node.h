#ifndef NODE_H_
#define NODE_H_

#include "token.h"
#include "list.h"
#include "symtable.h"

typedef enum {
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_NUM,
    NODE_COMPOUND,
    NODE_ASSIGN,
    NODE_VAR,
    NODE_NOP,
    NODE_BLOCK,
    NODE_VAR_DECL,
    NODE_PROGRAM
} AST_NODE_TYPE;

typedef struct __compound_node CompoundNode_t;
struct __compound_node {
    AST_NODE_TYPE type;
    LIST_ENTRY *statement_list;
};

/* element in declaration_list is still a list of VarNode */
typedef struct __var_decl_node VarDeclNode_t;
struct __var_decl_node {
    AST_NODE_TYPE type;
    LIST_ENTRY *declaration_list;
};

typedef struct __block_node BlockNode_t;
struct __block_node {
    AST_NODE_TYPE type;
    VarDeclNode_t *declarations;
    CompoundNode_t *compound_statement;
};

typedef struct __program_node ProgramNode_t;
struct __program_node {
    AST_NODE_TYPE type;
    BlockNode_t *block;
    token_t program;
};

typedef struct __nop_node NopNode_t;
struct __nop_node {
    AST_NODE_TYPE type;
};

typedef struct __var_node VarNode_t;
struct __var_node {
    AST_NODE_TYPE type;
    token_t operand;
};

typedef struct __assign_node AssignNode_t;
struct __assign_node {
    AST_NODE_TYPE type;
    VarNode_t *var;
    void *expr;
};


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

int visit(void *node, SYMT *symtable);
void free_node(void *node);

#endif
