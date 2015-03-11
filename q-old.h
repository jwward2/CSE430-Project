#ifndef Q_H_
#define Q_H_
#include "tcb.h"

struct q_element
{
    struct q_element* prev;
    struct q_element* next;
    int value;
};

struct q_element* NewItem(int v)
{
    struct q_element* temp = (struct q_element*)malloc(sizeof(struct q_element));
    temp->prev = NULL;
    temp->next = NULL;
    temp->value = v;
    return temp;
}

void InitQueue(struct q_element** head)
{
    *head = NULL;
}

void AddQueue(struct q_element** head, struct q_element* item)
{
    if (*head == NULL)
        *head = item;
    else
    {
        struct q_element* temp = *head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = item;
        temp->next->prev = temp;
    }
}

struct q_element* DelQueue(struct q_element** head)
{
    if (*head == NULL)
        return NULL;
    else
    {
        struct q_element* temp = *head;
        *head = temp->next;
        temp->next = NULL;
        temp->prev = NULL;
        return temp;
    }
}

void RotateQ(struct q_element** head)
{
    AddQueue(head, DelQueue(head));
}

#endif // Q_H_
