#ifndef _CUSTOMERS_DB_H_
#define _CUSTOMERS_DB_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
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
void read_date(char *, Customer **, void (*)(char *, int), int);
void insert_customer(Customer **, Customer *, void (*)(char *, int), int);
void insert_record(char *, Customer *, void (*)(char *, int), int);

void compare_fname(const Customer *, char *, int, void (*)(char *, int), int);
void compare_lname(const Customer *, char *, int, void (*)(char *, int), int);
void compare_id(const Customer *, char *, int, void (*)(char *, int), int);
void compare_phone(const Customer *, char *, int, void (*)(char *, int), int);
void compare_date(const Customer *, char *, int, void (*)(char *, int), int);
void compare_debt(const Customer *, char *, int, void (*)(char *, int), int);
#endif