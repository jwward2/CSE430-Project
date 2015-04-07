#ifndef Q_H_
#define Q_H_
#include "tcb.h"
#include <stdlib.h>

TCB_t* NewItem()
{
	TCB_t* temp = (TCB_t*)malloc(sizeof(TCB_t));
    temp->prev = NULL;
    temp->next = NULL;
    
    return temp;
}

void InitQueue(TCB_t ** head)
{
    *head = NULL;
}

void AddQueue(TCB_t** head, TCB_t* item)
{
    if (*head == NULL)
        *head = item;
    else
    {
        TCB_t* temp = *head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = item;
        temp->next->prev = temp;
    }
}

TCB_t* DelQueue(TCB_t** head)
{
    if (*head == NULL)
        return NULL;
    else
    {
        TCB_t* temp = *head;
        *head = temp->next;
        temp->next = NULL;
        temp->prev = NULL;
        return temp;
    }
}

void RotateQ(TCB_t** head)
{
    AddQueue(head, DelQueue(head));
}

int QueueSize(TCB_t* head)
{
    int count = 0;
    
    while (head != NULL)
    {
	count++;
	head = head->next;
    }
    
    return count;
}

#endif // Q_H_
