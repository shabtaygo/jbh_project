#ifndef _QUERY_H_
#define _QUERY_H_

#include "customers_db.h"
#define ARR_LEN(_arr) (sizeof(_arr) / sizeof(_arr[0]))
typedef enum
{
    SELECT,
    SET,
    PRINT,
    QUIT,
} menu_enum;

typedef enum
{
    FIRST,
    LAST,
    ID,
    PHONE,
    DATE,
    DEBT,
} fields_enum;

typedef enum
{
    BIGGER,
    SMALLER,
    NOT_EQUAL,
    EQUAL,
} op_inum;

void handl_show(Customer *, void (*)(char *, int), int);
void handl_set(char *, Customer **, char *, void (*)(char *, int), int);
void handl_select(char *, Customer *, void (*)(char *, int), int);
void handl_query(char *, Customer **, char *, void (*)(char *, int), int);
void create_db(char *, Customer **, void (*)(char *, int), int);
#endif