/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_resources
*/

#include <string.h>
#include "game.h"

bool is_a_resource(const char *argument)
{
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    for (size_t i = 0; i < NB_RESOURCES; i++)
        if (strcmp(resource_list[i], argument) == 0)
            return true;
    return false;
}
