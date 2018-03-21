#include "list.h"
#include <stdlib.h>

void add_list(LIST_ENTRY **HEAD, void *data)
{
    if (!(*HEAD)) {
        *HEAD = (LIST_ENTRY *) malloc(sizeof(LIST_ENTRY));
        (*HEAD)->data = data;
        (*HEAD)->next = NULL;
        return;
    }

    LIST_ENTRY *ptr;
    for (ptr = *HEAD; ptr->next; ptr = ptr->next)
        ;

    ptr->next = (LIST_ENTRY *) malloc(sizeof(LIST_ENTRY));
    ptr->next->data = data;
    ptr->next->next = NULL;
    return;
}

void free_list(LIST_ENTRY *HEAD)
{
    LIST_ENTRY *NEXT = NULL;
    while (HEAD) {
        NEXT = HEAD->next;
        free(HEAD);
        HEAD = NEXT;
    }
}
