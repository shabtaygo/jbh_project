
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "customers_db.h"
// valgrind --leak-check=yes
void free_db(Customer *head)
{
    while (head)
    {
        Customer *temp = head->next;
        free(head);
        head = temp;
    }
}

void show(Customer *head)
{
    if (!head)
    {
        puts("No customers");
        return;
    }
    else
    {
        printf("%-15s%-15s%-15s%-15s%-15s%-15s\n",
               "First Name", "Last Name", "ID", "Phone", "Debt", "Date");
        puts("=================================================================================");
    }

    while (head)
    {
        printf("%-15s%-15s%-15s%-15s%-15s%-15.2f\n", head->first_name, head->last_name,
               head->id, head->phone, head->date, head->debt);
        head = head->next;
    }
}

Customer *find_by_id(Customer **pHead, Customer *customer)
{
    Customer **pNext = pHead;
    Customer *new;
    while (*pNext && strcmp((*pNext)->id, customer->id))
    {
        pNext = &((*pNext)->next);
    }
    if (!*pNext)
    {
        return NULL;
    }
    else
    {
        new = *pNext;
        *pNext = (*pNext)->next;
        new->next = NULL;
        strcpy(new->date, customer->date);
        new->debt += customer->debt;
        return new;
    }
}

void insert_record(char *fname, Customer *customer)
{
    int write = 0;
    FILE *f = fopen(fname, "a");
    if (!f)
    {
        printf("Error opening file\n");
        return;
    }
    write = fprintf(f, "\n%s,%s,%s,%s,%s,%.2f",
                    customer->first_name,
                    customer->last_name,
                    customer->id,
                    customer->phone,
                    customer->date,
                    customer->debt);
    write < 0 ? printf("wrong inseration\n") : printf("SUCCESS");
    fclose(f);
}

void insert_customer(Customer **pHead, Customer *customer)
{
    Customer **pNext = pHead;
    Customer *new = find_by_id(pHead, customer);
    customer = new ?: customer;
    while (*pNext && (*pNext)->debt > customer->debt)
    {
        pNext = &((*pNext)->next);
    }

    if (!new)
    {
        new = malloc(sizeof(Customer));
        if (!new)
        {
            return;
        }
        strcpy(new->first_name, customer->first_name);
        strcpy(new->last_name, customer->last_name);
        strcpy(new->id, customer->id);
        strcpy(new->phone, customer->phone);
        new->debt = customer->debt;
        strcpy(new->date, customer->date);
    }
    new->next = *pNext;
    *pNext = new;
}

void read_date(char *fname, Customer **pHead)
{
    char buffr[200];
    unsigned read = 0, i = 0;
    Customer customer = {};
    FILE *f = fopen(fname, "r");
    if (!f)
    {
        printf("Error opening file\n");
        return;
    }
    while (!feof(f))
    {
        fgets(buffr, sizeof(buffr), f);
        read = sscanf(buffr, "%29[^,],%29[^,],%9[^,],%10[^,],%10[^,],%f\n",
                      customer.first_name,
                      customer.last_name,
                      customer.id,
                      customer.phone,
                      customer.date,
                      &customer.debt);
        if (read == 6)
        {
            i++;
            insert_customer(pHead, &customer);
        }
        else
        {
            printf("line %u uncorrect", i++);
        }
    }
    fclose(f);
    show(*pHead);
};

void insertTail(Customer **pTail, Customer *customer)
{
    Customer *new = malloc(sizeof(Customer));

    if (!new)
    {
        return;
    }
    strcpy(new->first_name, customer->first_name);
    strcpy(new->last_name, customer->last_name);
    strcpy(new->id, customer->id);
    strcpy(new->phone, customer->phone);
    new->debt = customer->debt;
    strcpy(new->date, customer->date);
    new->next = NULL;
    if (*pTail)
    {
        (*pTail)->next = new;
    }
    *pTail = new;
}

void compare_fname(Customer *db, char *fname, int op)
{
    Customer *head = NULL, *tail = NULL, *customer = db;

    while (customer)
    {
        unsigned match = 0;
        int res = strcmp(customer->first_name, fname);
        switch (op)
        {
        case 0:
            match = res > 0 ? ++match : match;
            break;
        case 1:
            match = res < 0 ? ++match : match;
            break;
        case 2:
            match = res ? ++match : match;
            break;
        case 3:
            match = !res ? ++match : match;
            break;
        }
        if (match)
        {
            insertTail(&tail, customer);
            if (!head)
            {
                head = tail;
            }
        }
        customer = customer->next;
    }
    show(head);
    free_db(head);
};

void compare_lname(Customer *db, char *lname, int op)
{
    Customer *head = NULL, *tail = NULL, *customer = db;

    while (customer)
    {
        unsigned match = 0;
        int res = strcmp(customer->last_name, lname);
        switch (op)
        {
        case 0:
            match = res > 0 ? ++match : match;
            break;
        case 1:
            match = res < 0 ? ++match : match;
            break;
        case 2:
            match = res ? ++match : match;
            break;
        case 3:
            match = !res ? ++match : match;
            break;
        }
        if (match)
        {
            insertTail(&tail, customer);
            if (!head)
            {
                head = tail;
            }
        }
        customer = customer->next;
    }
    show(head);
    free_db(head);
};

void compare_id(Customer *db, char *id, int op)
{
    Customer *head = NULL, *tail = NULL, *customer = db;

    while (customer)
    {
        unsigned match = 0;
        int res = strcmp(customer->id, id);
        switch (op)
        {
        case 0:
            match = res > 0 ? ++match : match;
            break;
        case 1:
            match = res < 0 ? ++match : match;
            break;
        case 2:
            match = res ? ++match : match;
            break;
        case 3:
            match = !res ? ++match : match;
            break;
        }
        if (match)
        {
            insertTail(&tail, customer);
            if (!head)
            {
                head = tail;
            }
        }
        customer = customer->next;
    }
    show(head);
    free_db(head);
};

void compare_phone(Customer *db, char *phone, int op)
{
    Customer *head = NULL, *tail = NULL, *customer = db;

    while (customer)
    {
        unsigned match = 0;
        int res = strcmp(customer->phone, phone);
        switch (op)
        {
        case 0:
            match = res > 0 ? ++match : match;
            break;
        case 1:
            match = res < 0 ? ++match : match;
            break;
        case 2:
            match = res ? ++match : match;
            break;
        case 3:
            match = !res ? ++match : match;
            break;
        }
        if (match)
        {
            insertTail(&tail, customer);
            if (!head)
            {
                head = tail;
            }
        }
        customer = customer->next;
    }
    show(head);
    free_db(head);
};

int compare_int(int a, int b)
{
    return a - b;
}

void compare_date(Customer *db, char *date, int op)
{
    Customer *head = NULL, *tail = NULL, *customer = db;
    unsigned days = atol(strtok(date, "/"));
    unsigned month = atoi(strtok(NULL, "/"));
    unsigned years = atoi(strtok(NULL, "'\0'"));

    while (customer)
    {
        char *date_cus = strdup(customer->date);
        unsigned match = 0;
        unsigned day_cus = atol(strtok(date_cus, "/"));
        unsigned month_cus = atoi(strtok(NULL, "/"));
        unsigned years_cus = atoi(strtok(NULL, "'\0'"));
        int res = compare_int(years_cus, years);
        if (!res)
        {
            res = compare_int(month_cus, month);
            if (!res)
            {
                res = compare_int(day_cus, days);
            }
        }

        switch (op)
        {
        case 0:
            match = res > 0 ? ++match : match;
            break;
        case 1:
            match = res < 0 ? ++match : match;
            break;
        case 2:
            match = res ? ++match : match;
            break;
        case 3:
            match = !res ? ++match : match;
            break;
        }
        if (match)
        {
            insertTail(&tail, customer);
            if (!head)
            {
                head = tail;
            }
        }
        customer = customer->next;
        free(date_cus);
    }
    show(head);
    free_db(head);
};

void compare_debt(Customer *db, char *debtc, int op)
{
    Customer *head = NULL, *tail = NULL, *customer = db;
    float debt = atof(debtc);
    while (customer)
    {
        unsigned match = 0;
        int res = debt - customer->debt;
        switch (op)
        {
        case 0:
            match = res > 0 ? ++match : match;
            break;
        case 1:
            match = res < 0 ? ++match : match;
            break;
        case 2:
            match = res ? ++match : match;
            break;
        case 3:
            match = !res ? ++match : match;
            break;
        }
        if (match)
        {
            insertTail(&tail, customer);
            if (!head)
            {
                head = tail;
            }
        }
        customer = customer->next;
    }
    show(head);
    free_db(head);
};

void to_lower(char* str)
{
    unsigned len=strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        str[i]=tolower(str[i]);
    }
}