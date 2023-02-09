#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "query.h"

void show(char *str, int mode)
{
    printf("%s", str);
}
int main()
{
    Customer *head = NULL;
    char buf[100] = {0};
    char file_name[] = "customers.txt";
    create_db(file_name, &head, show, 0);
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        puts("Enter an order : (show ,set , select , quit) ");
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        if (!strncmp(buf, "quit", strlen("quit")))
        {
            break;
        }
        handl_query(buf, &head, file_name, show, 0);
    }
    free_db(head);
    return 0;
}