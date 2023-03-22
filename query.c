#include "query.h"

void handl_show(Customer *head, void (*show)(char *, int), int mode)
{
    if (!head)
    {
        show("No customers", mode);
        return;
    }
    else
    {
        char message[200];
        sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15s\n",
                "First Name", "Last Name", "ID", "Phone", "Date", "Debt");
        show(message, mode);
        show("=================================================================================\n",
             mode);
        while (head)
        {
            memset(message, 0, sizeof(message));
            sprintf(message, "%-15s%-15s%-15s%-15s%-15s%-15.2f\n", head->first_name, head->last_name,
                    head->id, head->phone, head->date, head->debt);
            show(message, mode);
            printf("handl_show mode=%d\n", mode);
            head = head->next;
        }
    }
}

void create_db(char *fname, Customer **pHead, void (*show)(char *, int), int mode)
{
    read_date(fname, pHead, show, mode);
    handl_show(*pHead, show, mode);
}

void handl_set(char *set_command, Customer **pHead, char *fname,
               void (*show)(char *, int), int mode)
{
    Customer customer = {};
    char *a, *b, *c, *d, *e, *f;
    // set first name=or,second name=rubin,id=444444444,phone=0555555555,date=12/12/2022,debt=800
    // set first name=avi,last name=cohen,id=245366789,phone=0545689711,debt=250,date=07/12/2022
    a = strtok(set_command, ",");
    b = strtok(NULL, ",");
    c = strtok(NULL, ",");
    d = strtok(NULL, ",");
    e = strtok(NULL, ",");
    f = strtok(NULL, ",");
    a = strstr(a, "=");
    a += 1;
    to_lower(a);
    b = strstr(b, "=");
    b += 1;
    to_lower(b);
    c = strstr(c, "=");
    c += 1;
    to_lower(c);
    d = strstr(d, "=");
    d += 1;
    to_lower(d);
    e = strstr(e, "=");
    e += 1;
    to_lower(e);
    f = strstr(f, "=");
    f += 1;
    to_lower(f);
    strcpy(customer.first_name, a);
    strcpy(customer.last_name, b);
    strcpy(customer.id, c);
    strcpy(customer.phone, d);
    strcpy(customer.date, e);
    customer.debt = atof(f);
    insert_customer(pHead, &customer, show, mode);
    insert_record(fname, &customer, show, mode);
}

void handl_select(char *select_command, Customer *head,
                  void (*show)(char *, int), int mode)
{
    char *field = NULL, *condition = NULL, *op,
         *opertions[] = {">", "<", "!=", "="},
         *fields[] = {"first name", "second name", "id", "phone", "date", "debt"};
    op_inum i = 0;
    fields_enum j = 0;
    while (i < ARR_LEN(opertions))
    {
        op = strstr(select_command, opertions[i]);
        if (op)
        {
            break;
        }
        i++;
    }
    if (i == ARR_LEN(opertions))
    {
        show("No match operator\n", mode);
        return;
    }
    condition = (i != 2) ? op + 1 : op + 2;
    to_lower(condition);
    field = strtok(select_command + 1, opertions[i]);
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
        show("No match field\n", mode);
        return;
    }
    switch (j)
    {
    case FIRST:
        compare_fname(head, condition, i, show, mode);
        break;
    case LAST:
        compare_lname(head, condition, i, show, mode);
        break;
    case ID:
        compare_id(head, condition, i, show, mode);
        break;
    case PHONE:
        compare_phone(head, condition, i, show, mode);
        break;
    case DATE:
        compare_date(head, condition, i, show, mode);
        break;
    case DEBT:
        compare_debt(head, condition, i, show, mode);
        break;
    };
}

void handl_query(char *command, Customer **pHead, char *file_name,
                 void (*show)(char *, int), int mode)
{
    char str[10] = {0};
    sscanf(command, "%s", str);
    printf("command=%s\n", str);
    if (!strcmp(str, "show"))
    {
        handl_show(*pHead, show, mode);
        return;
    }
    if (!strcmp(str, "select"))
    {
        handl_select(command + strlen(str), *pHead, show, mode);
        return;
    }
    if (!strcmp(str, "set"))
    {
        handl_set(command + strlen(str) + 1, pHead, file_name, show, mode);
        return;
    }
}