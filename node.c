#include "node.h"
#include "token.h"
#include "symtable.h"
#include "list.h"

/* return n ^ k */
int mypow(int n, int k)
{
    int ret = n;
    
    if (k <= 0) return 1;

    for (int i = 0; i < k - 1; i++) {
        ret *= n;
    }
    return ret;
}

int visit_BinNode(BinNode_t *node, SYMT *symtable)
{
    switch (node->op.type) {
        case PLUS:
            return visit(node->left, symtable) + visit(node->right, symtable);
        case MINUS:
            return visit(node->left, symtable) - visit(node->right, symtable);
        case MULTIPLY:
            return visit(node->left, symtable) * visit(node->right, symtable);
        case INTEGER_DIVIDE:
            return visit(node->left, symtable) / visit(node->right, symtable);
        case POWER:
            return mypow(visit(node->left, symtable), visit(node->right, symtable));
        default:
            printf("node.c: Unavailable op type\n");
            exit(0);
    }
}

int visit_NumNode(NumNode_t *node)
{
    return * (int *) node->operand.value;
}

int visit_UnaryNode(UnaryNode_t *node, SYMT *symtable)
{
    switch (node->op.type) {
        case PLUS:
            return visit(node->expr, symtable);
        case MINUS:
            return -1 * visit(node->expr, symtable);
        default:
            printf("node.c: Unavailabe op type\n");
            exit(0);
    }
}

int visit_CompoundNode(CompoundNode_t *node, SYMT *symtable)
{
    LIST_ENTRY *ptr = node->statement_list;
    while (ptr) {
        visit(ptr->data, symtable);
        ptr = ptr->next;
    }
    return 0;
}

int visit_AssignNode(AssignNode_t *node, SYMT *symtable)
{
    int ret = visit(node->expr, symtable);
    set_symt_value(symtable, (char *) node->var->operand.value, ret);
    return 0;
}

int visit_VarNode(VarNode_t *node, SYMT *symtable)
{
    return get_symt_value(symtable, (char *) node->operand.value);
}

int visit(void *node, SYMT *symtable)
{
    switch (*((AST_NODE_TYPE *) node)) {
        case NODE_NUM:
            return visit_NumNode((NumNode_t *) node);
        case NODE_BINARY_OP:
            return visit_BinNode((BinNode_t *) node, symtable);
        case NODE_UNARY_OP:
            return visit_UnaryNode((UnaryNode_t *) node, symtable);
        case NODE_COMPOUND:
            return visit_CompoundNode((CompoundNode_t *) node, symtable);
        case NODE_ASSIGN:
            return visit_AssignNode((AssignNode_t *) node, symtable);
        case NODE_VAR:
            return visit_VarNode((VarNode_t *) node, symtable);
        case NODE_NOP:
            return 0;
        default:
            printf("node.c: error\n");
            exit(0);
    }
}

void free_node(void *node)
{
    if (*((AST_NODE_TYPE *) node) == NODE_BINARY_OP) {
        free_node(((BinNode_t *) node)->left);
        free_node(((BinNode_t *) node)->right);
    }

    if (*((AST_NODE_TYPE *) node) == NODE_UNARY_OP) {
        free_node(((UnaryNode_t *) node)->expr);
    }

    if (*((AST_NODE_TYPE *) node) == NODE_NUM) {
        free(((NumNode_t *) node)->operand.value);
    }

    if (*((AST_NODE_TYPE *) node) == NODE_VAR) {
        free(((VarNode_t *) node)->operand.value);
    }
    
    if (*((AST_NODE_TYPE *) node) == NODE_COMPOUND) {
        for (LIST_ENTRY *ptr = ((CompoundNode_t *) node)->statement_list; ptr; ptr = ptr->next) {
            free_node(ptr->data);
        }
        free_list(((CompoundNode_t *) node)->statement_list);
    }

    free(node);
}
