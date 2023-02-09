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

void insert_record(char *fname, Customer *customer,
                   void (*show)(char *, int), int mode)
{
    char message[40] = {0};
    int write = 0;
    FILE *f = fopen(fname, "a");
    if (!f)
    {
        sprintf(message, "Error opening %s file\n", fname);
        show(message, mode);
        return;
    }
    write = fprintf(f, "\n%s,%s,%s,%s,%s,%.2f",
                    customer->first_name,
                    customer->last_name,
                    customer->id,
                    customer->phone,
                    customer->date,
                    customer->debt);
    write < 0 ? show("wrong inseration\n", mode) : show("SUCCESS\n", mode);
    fclose(f);
}

void insert_customer(Customer **pHead, Customer *customer,
                     void (*show)(char *, int), int mode)
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
            show("Memory not allocated.\n", mode);
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

void read_date(char *fname, Customer **pHead,
               void (*show)(char *, int), int mode)
{
    char buffr[200], message[30] = {0};
    unsigned read = 0, i = 0;
    Customer customer = {};
    FILE *f = fopen(fname, "r");
    if (!f)
    {
        show("Error opening file\n", mode);
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
            insert_customer(pHead, &customer, show, mode);
        }
        else
        {
            sprintf(message, "record %u is incorrect\n", i++);
            show(message, mode);
        }
    }
    fclose(f);
};

void compare_fname(const Customer *db, char *fname, int op,
                   void (*show)(char *, int), int mode)
{
    char message[200] = {0};
    while (db)
    {
        unsigned match = 0;
        int res = strcmp(db->first_name, fname);
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
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n",
                    db->first_name, db->last_name,
                    db->id, db->phone, db->date, db->debt);
            show(message, mode);
        }
        db = db->next;
    }
};
void compare_lname(const Customer *db, char *lname, int op,
                   void (*show)(char *, int), int mode)
{
    char message[200] = {0};
    while (db)
    {
        unsigned match = 0;
        int res = strcmp(db->last_name, lname);
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
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n",
                    db->first_name, db->last_name,
                    db->id, db->phone, db->date, db->debt);
            show(message, mode);
        }
        db = db->next;
    }
};

void compare_id(const Customer *db, char *id, int op,
                void (*show)(char *, int), int mode)
{
    char message[200] = {0};
    while (db)
    {
        unsigned match = 0;
        int res = strcmp(db->id, id);
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
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n",
                    db->first_name, db->last_name,
                    db->id, db->phone, db->date, db->debt);
            show(message, mode);
        }
        db = db->next;
    }
};

void compare_phone(const Customer *db, char *phone, int op,
                   void (*show)(char *, int), int mode)
{
    char message[200] = {0};
    while (db)
    {
        unsigned match = 0;
        int res = strcmp(db->phone, phone);
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
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n",
                    db->first_name, db->last_name,
                    db->id, db->phone, db->date, db->debt);
            show(message, mode);
        }
        db = db->next;
    }
};

int compare_int(int a, int b)
{
    return a - b;
}

void compare_date(const Customer *db, char *date, int op,
                  void (*show)(char *, int), int mode)
{
    char message[200] = {0};
    unsigned days = atol(strtok(date, "/"));
    unsigned month = atoi(strtok(NULL, "/"));
    unsigned years = atoi(strtok(NULL, "'\0'"));
    while (db)
    {
        char *date_cus = strdup(db->date);
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
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n",
                    db->first_name, db->last_name,
                    db->id, db->phone, db->date, db->debt);
            show(message, mode);
        }
        db = db->next;
        free(date_cus);
    }
};

void compare_debt(const Customer *db, char *debtc, int op,
                  void (*show)(char *, int), int mode)
{
    char message[200] = {0};
    float debt = atof(debtc);
    while (db)
    {
        unsigned match = 0;
        int res = debt - db->debt;
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
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n",
                    db->first_name, db->last_name,
                    db->id, db->phone, db->date, db->debt);
            show(message, mode);
        }
        db = db->next;
    }
};

void to_lower(char *str)
{
    unsigned len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }
}