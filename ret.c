#include "ret.h"

RET *get_ret_int(int value)
{
    RET *r = (RET *) malloc(sizeof(RET));
    if (!r) {
        printf("ret.c: not available memory\n");
        exit(1);
    }

    r->type = RET_INT;
    r->value = malloc(sizeof(int));
    if (!r->value) {
        printf("ret.c: not available memory\n");
        exit(1);
    }
    * (int *) r->value = value;

    return r;
}

RET *get_ret_float(float value)
{
    RET *r = (RET *) malloc(sizeof(RET));
    if (!r) {
        printf("ret.c: not available memory\n");
        exit(1);
    }

    r->type = RET_FLOAT;
    r->value = malloc(sizeof(float));
    if (!r->value) {
        printf("ret.c: not available memory\n");
        exit(1);
    }
    * (float *) r->value = value;

    return r;
}

void free_ret(RET *r)
{
    if (r) {
        if (r->value)
            free(r->value);
        free(r);
    }
}
