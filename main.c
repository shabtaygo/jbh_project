#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main()
{
    Customer *head = NULL;
    char buf[100] = {}, str[10] = {};
    char file_name[] = "customers.txt";
    read_date(file_name, &head);
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        puts("Enter an order : (show ,set , select , quit) ");
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        sscanf(buf, "%s", str);
        if (!strcmp(str, "show"))
        {
            show(head);
            continue;
        }
        if (!strcmp(str, "select"))
        {
            to_lower(buf + strlen(str));
            char *field = NULL, *condition = NULL, *op,
                 *opertions[] = {">", "<", "!=", "="},
                 *fields[] = {"first name", "second name", "id", "phone", "date", "debt"};
            op_inum i = 0;
            fields_enum j = 0;
            while (i < ARR_LEN(opertions))
            {
                op = strstr(buf + strlen(str), opertions[i]);
                if (op)
                {
                    break;
                }
                i++;
            }
            if (i == ARR_LEN(opertions))
            {
                puts("No match operator");
                continue;
            }
            condition = (i != 2) ? op + 1 : op + 2;
            to_lower(condition);
            field = strtok(buf + strlen(str) + 1, opertions[i]);
            while (j < ARR_LEN(fields))
            {
                if (!strcmp(field, fields[j]))
                {
                    break;
                }
                j++;
            }
            if (j == ARR_LEN(fields))
            {
                puts("No match field");
                continue;
            }
            switch (j)
            {
            case FIRST:
                compare_fname(head, condition, i);
                break;
            case LAST:
                compare_lname(head, condition, i);
                break;
            case ID:
                compare_id(head, condition, i);
                break;
            case PHONE:
                compare_phone(head, condition, i);
                break;
            case DATE:
                compare_date(head, condition, i);
                break;
            case DEBT:
                compare_debt(head, condition, i);
                break;
            }
            continue;
        }
        if (!strcmp(str, "set"))
        {
            Customer customer = {};
            char *a, *b, *c, *d, *e, *f;
            // set first name=avi,last name=cohen,id=245366789,phone=0545689711,debt=250,date=07/12/2022
            a = strtok(buf + strlen(str), ",");
            b = strtok(NULL, ",");
            c = strtok(NULL, ",");
            d = strtok(NULL, ",");
            e = strtok(NULL, ",");
            f = strtok(NULL, ",");

            a = strstr(a, "=");
            a += 1;
            b = strstr(b, "=");
            b += 1;
            c = strstr(c, "=");
            c += 1;
            d = strstr(d, "=");
            d += 1;
            e = strstr(e, "=");
            e += 1;
            f = strstr(f, "=");
            f += 1;

            strcpy(customer.first_name, a);
            strcpy(customer.last_name, b);
            strcpy(customer.id, c);
            strcpy(customer.phone, d);
            strcpy(customer.date, e);
            customer.debt = atof(f);
            insert_customer(&head, &customer);
            insert_record(file_name, &customer);
            continue;
        }
        if (!strncmp(str, "quit", strlen(buf) - 1))
        {
            free_db(head);
            break;
        }
    }
    return 0;
}