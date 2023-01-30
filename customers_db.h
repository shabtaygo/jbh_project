#ifndef _CUSTOMERS_DB_H_
#define _CUSTOMERS_DB_H_

typedef struct _Customer
{
    char first_name[30];
    char last_name[30];
    char id[10];
    char phone[11];
    float debt;
    char date[11];
    struct _Customer *next;
} Customer;
void free_db(Customer *);
void read_date(char *, Customer **);
void insert_customer(Customer **, Customer *);
void insert_record(char*,Customer*);
void show(Customer *);

void compare_fname(Customer*,char*,int );
void compare_lname(Customer*,char*,int);
void compare_id(Customer*,char*,int);
void compare_phone(Customer*,char*,int);
void compare_date(Customer*,char*,int);
void compare_debt(Customer*,char*,int);
void to_lower(char*);
#endif