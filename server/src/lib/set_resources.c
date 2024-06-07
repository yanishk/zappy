/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set_resources
*/

#include "server.h"

void set_resources(resource_t *resource, const char *name, int value)
{
    if (strcmp(name, FOOD) == 0)
        resource->food += value;
    if (strcmp(name, LINEMATE) == 0)
        resource->linemate += value;
    if (strcmp(name, DERAUMERE) == 0)
        resource->deraumere += value;
    if (strcmp(name, SIBUR) == 0)
        resource->sibur += value;
    if (strcmp(name, MENDIANE) == 0)
        resource->mendiane += value;
    if (strcmp(name, PHIRAS) == 0)
        resource->phiras += value;
    if (strcmp(name, THYSTAME) == 0)
        resource->thystame += value;
}
