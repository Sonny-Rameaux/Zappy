/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** queue
*/
#include "server.h"

cmd_queue_t *create_node(char *data)
{
    cmd_queue_t *newNode = malloc(sizeof(cmd_queue_t));

    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = malloc(sizeof(char) * (my_strlen(data) + 1));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}

void append(cmd_queue_t **headRef, char *data)
{
    cmd_queue_t *newNode = create_node(data);
    cmd_queue_t *current;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    current = *headRef;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void print_list(cmd_queue_t *head)
{
    cmd_queue_t *current = head;

    printf("Linked List: ");
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(cmd_queue_t *head)
{
    cmd_queue_t *current = head;
    cmd_queue_t *temp;

    if (!head)
        return;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

char *pop_front(cmd_queue_t **headRef)
{
    cmd_queue_t *temp;
    char *data;

    if (*headRef == NULL) {
        return NULL;
    }
    temp = *headRef;
    data = temp->data;
    *headRef = temp->next;
    free(temp);
    return data;
}
