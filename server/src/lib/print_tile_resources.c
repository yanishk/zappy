/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** print_tile_resources
*/

#include <stdio.h>
#include "resource.h"

void print_tile_resources(const unsigned int client_fd, int width,
    int height, const resource_t resource)
{
    dprintf(client_fd, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n",
    width, height, resource.food, resource.linemate, resource.deraumere,
    resource.sibur, resource.mendiane, resource.phiras, resource.thystame);
}
