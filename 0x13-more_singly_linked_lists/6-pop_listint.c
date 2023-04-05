#include "lists.h"

/**
 * pop_listint - Deletes the head node of a listint_t linked list,
 *               and returns the head node’s data (n).
 * @head: Pointer to the pointer to the head node.
 *
 * Return: The head node's data (n), or 0 if the list is empty.
 */
int pop_listint(listint_t **head)
{
    int data;
    listint_t *next_node;

    if (*head == NULL)
        return (0);

    data = (*head)->n;
    next_node = (*head)->next;
    free(*head);
    *head = next_node;

    return (data);
}
