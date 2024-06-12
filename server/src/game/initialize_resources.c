/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_resources
*/

#include <math.h>
#include <time.h>
#include "game.h"
#include "server.h"

struct repartion_resource repartion[] = {
    {FOOD, FOOD_DEN},
    {LINEMATE, LINEMATE_DEN},
    {DERAUMERE, DERAUMERE_DEN},
    {SIBUR, SIBUR_DEN},
    {MENDIANE, MENDIANE_DEN},
    {PHIRAS, PHIRAS_DEN},
    {THYSTAME, THYSTAME_DEN},
};

static void repartition_resource(const arguments_t *args, zappy_t *zappy,
    const char *name, double density)
{
    size_t max = round(args->width * args->height * density);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index < max) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (get_resources(&zappy->resource[rand_width][rand_height], name) > 0)
            continue;
        set_resources(&zappy->resource[rand_width][rand_height], name, 1);
        index++;
    }
}

void initialize_resources(resource_t *resource)
{
    resource->deraumere = 0;
    resource->food = 0;
    resource->linemate = 0;
    resource->mendiane = 0;
    resource->phiras = 0;
    resource->sibur = 0;
    resource->thystame = 0;
}

static void density_onland(const arguments_t *args, zappy_t *zappy)
{
    for (int x = 0; x < args->width; x++) {
        for (int y = 0; y < args->height; y++) {
            initialize_resources(&zappy->resource[x][y]);
        }
    }
    for (int index = 0; index < NB_RESOURCES; index++) {
        repartition_resource(args, zappy, repartion[index].name,
            repartion[index].density);
    }
}

void init_basis_map(zappy_t *zappy, const arguments_t *arg)
{
    zappy->resource = malloc(sizeof(resource_t *) * arg->width);
    for (int x = 0; x < arg->height; x++)
        zappy->resource[x] = malloc(sizeof(resource_t) * arg->height);
    density_onland(arg, zappy);
}
