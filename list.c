#include "list.h"

void add_list(LIST_ENTRY **HEAD, void *data)
{
    if (!(*HEAD)) {
        *HEAD = (LIST_ENTRY *) malloc(sizeof(LIST_ENTRY));
        (*HEAD)->data = data;
        (*HEAD)->next = NULL;
        return;
    }

    for (LIST_ENTRY ptr = *HEAD; ptr->next; ptr = ptr->next);
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
        /* TODO: Specific free function for data */
        free(HEAD->data);
        free(HEAD);
        HEAD = NEXT;
    }
}
