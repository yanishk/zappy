/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_resources
*/

#include <math.h>
#include <time.h>
#include "map.h"

static void repartition_food(const arguments_t *args, zappy_t *zappy)
{
    size_t max_food = round(args->width * args->height * 0.5);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_food) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].food > 0)
            continue;
        zappy->resource[rand_width][rand_height].food += 1;
        index++;
    }
}

static void repartition_linemate(const arguments_t *args, zappy_t *zappy)
{
    size_t max_linemate = round(args->width * args->height * 0.3);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_linemate) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].linemate > 0)
            continue;
        zappy->resource[rand_width][rand_height].linemate += 1;
        index++;
    }
}

static void repartition_deraumere(const arguments_t *args, zappy_t *zappy)
{
    size_t max_deraumere = round(args->width * args->height * 0.15);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_deraumere) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].deraumere > 0)
            continue;
        zappy->resource[rand_width][rand_height].deraumere += 1;
        index++;
    }
}

static void repartition_sibur(const arguments_t *args, zappy_t *zappy)
{
    size_t max_sibur = round(args->width * args->height * 0.1);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_sibur) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].sibur > 0)
            continue;
        zappy->resource[rand_width][rand_height].sibur += 1;
        index++;
    }
}

static void repartition_mendiane(const arguments_t *args, zappy_t *zappy)
{
    size_t max_mendiane = round(args->width * args->height * 0.1);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_mendiane) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].mendiane > 0)
            continue;
        zappy->resource[rand_width][rand_height].mendiane += 1;
        index++;
    }
}

static void repartition_phiras(const arguments_t *args, zappy_t *zappy)
{
    size_t max_phiras = round(args->width * args->height * 0.08);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_phiras) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].phiras > 0)
            continue;
        zappy->resource[rand_width][rand_height].phiras += 1;
        index++;
    }
}

static void repartition_thystame(const arguments_t *args, zappy_t *zappy)
{
    size_t max_thystame = round(args->width * args->height * 0.05);
    size_t index = 0;
    int rand_width = 0;
    int rand_height = 0;

    while (index != max_thystame) {
        rand_width = (rand()) % args->width;
        rand_height = (rand()) % args->height;
        if (zappy->resource[rand_width][rand_height].thystame > 0)
            continue;
        zappy->resource[rand_width][rand_height].thystame += 1;
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

void density_onland(const arguments_t *args, zappy_t *zappy)
{
    for (int x = 0; x < args->width; x++) {
        for (int y = 0; y < args->height; y++) {
            initialize_resources(&zappy->resource[x][y]);
        }
    }
    repartition_food(args, zappy);
    repartition_linemate(args, zappy);
    repartition_deraumere(args, zappy);
    repartition_sibur(args, zappy);
    repartition_mendiane(args, zappy);
    repartition_phiras(args, zappy);
    repartition_thystame(args, zappy);
}
