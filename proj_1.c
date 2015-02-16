#include <stdio.h>
#include <stdlib.h>
#include "q.h"

int main()
{
    struct q_element* head;

    InitQueue(&head);
    AddQueue(&head, NewItem(4));
    AddQueue(&head, NewItem(2));
    AddQueue(&head, NewItem(5));
    AddQueue(&head, NewItem(7));
    AddQueue(&head, NewItem(10));

    struct q_element* iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    DelQueue(&head);
    DelQueue(&head);


    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    AddQueue(&head, NewItem(8));
    AddQueue(&head, NewItem(1));

    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    RotateQ(&head);

    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    RotateQ(&head);

    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    RotateQ(&head);

    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    DelQueue(&head);
    DelQueue(&head);
    DelQueue(&head);
    DelQueue(&head);
    RotateQ(&head);

    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    DelQueue(&head);
    RotateQ(&head);

    printf("\n");
    iter = head;

    while (iter != NULL)
    {
        printf("%d\n", iter->value);
        iter = iter->next;
    }

    return 0;
}
