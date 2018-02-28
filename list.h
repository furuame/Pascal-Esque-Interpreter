#ifndef LIST_H_
#define LIST_H_

typedef struct __list_entry LIST_ENTRY;

struct __list_entry {
    void *data;
    LIST_ENTRY *next;
};

void add_list(LIST_ENTRY **HEAD, void *data);
void free_list(LIST_ENTRY *HEAD);

#endif
