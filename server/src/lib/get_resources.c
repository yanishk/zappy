/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_resources
*/

#include "command.h"

int get_resources(resource_t *resource, char *name)
{
    if (strcmp(name, FOOD) == 0)
        return resource->food;
    if (strcmp(name, LINEMATE) == 0)
        return resource->linemate;
    if (strcmp(name, DERAUMERE) == 0)
        return resource->deraumere;
    if (strcmp(name, SIBUR) == 0)
        return resource->sibur;
    if (strcmp(name, MENDIANE) == 0)
        return resource->mendiane;
    if (strcmp(name, PHIRAS) == 0)
        return resource->phiras;
    if (strcmp(name, THYSTAME) == 0)
        return resource->thystame;
    return ERROR_RETURN;
}
