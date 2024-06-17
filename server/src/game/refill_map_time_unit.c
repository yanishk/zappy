/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** refill_map_time_unit
*/

#include <math.h>
#include "command_gui.h"

static size_t get_nb_resource(const arguments_t *args, zappy_t *zappy,
    const char *name)
{
    size_t resource = 0;

    for (int x = 0; x < args->height; x++) {
        for (int y = 0; y < args->width; y++) {
            resource += get_resources(&zappy->resource[x][y], name);
        }
    }
    return resource;
}

static void repartition_resource(server_t *server, const arguments_t *args,
    zappy_t *zappy, struct repartion_resource const *repartion_unit)
{
    size_t density_calc =
        round(args->width * args->height * repartion_unit->density);
    size_t count_resource = get_nb_resource(args, zappy, repartion_unit->name);
    int rand_width = 0;
    int rand_height = 0;

    while (count_resource < density_calc) {
        rand_height = (rand()) % args->height;
        rand_width = (rand()) % args->width;
        if (get_resources(&zappy->resource[rand_height][rand_width],
            repartion_unit->name) > 0)
            continue;
        set_resources(&zappy->resource[rand_height][rand_width],
            repartion_unit->name, 1);
        bct(server, zappy, rand_width, rand_height);
        count_resource++;
    }
}

void refill_map(zappy_t *zappy, const arguments_t arg, server_t *server,
    clock_t *refill)
{
    double time_unit = calculate_freq(arg.freq, REFILL_MAP_TIME_UNIT);

    if (time_is_up(*refill, time_unit)) {
        for (int index = 0; index < NB_RESOURCES; index++) {
            repartition_resource(server, &arg, zappy, &repartion_unit[index]);
        }
        *refill = clock();
    }
}
