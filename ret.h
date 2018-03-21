#ifndef RET_H_
#define RET_H_

typedef enum {
    RET_INT,
    RET_FLOAT,
} RETURN_VALUE_TYPE;

typedef struct __return_value RET;
struct __return_value {
    RETURN_VALUE_TYPE type;
    void *value;
};

RET *get_ret_int(int value);
RET *get_ret_float(float value);
void free_ret(RET *r);

#endif
