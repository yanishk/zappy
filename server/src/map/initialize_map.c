/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_map
*/

#include "map.h"

static void init_basis_map(zappy_t *zappy, const arguments_t *arg)
{
    zappy->resource = malloc(sizeof(resource_t *) * arg->width);
    for (int x = 0; x < arg->height; x++)
        zappy->resource[x] = malloc(sizeof(resource_t) * arg->height);
    density_onland(arg, zappy);
}

void initialize_map(const arguments_t arg, zappy_t *zappy)
{
    init_basis_map(zappy, &arg);
    initialize_teams(arg, zappy);
}
