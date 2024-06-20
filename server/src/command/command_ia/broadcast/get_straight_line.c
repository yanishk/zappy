/*
** EPITECH PROJECT, 2024
** zppy_mmry_leak
** File description:
** get_straight_line
*/

#include "command_ia.h"

void indirect_west_east(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (road->width_undirect > 0)
        *dir_diag = EAST_TILE;
    if (road->width_undirect < 0)
        *dir_diag = WEST_TILE;
}

void direct_west_east(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (road->width_direct > 0)
        *dir_diag = WEST_TILE;
    if (road->width_direct < 0)
        *dir_diag = EAST_TILE;
}

static void indirect_north_south(road_broadcast_t *road, int i,
    size_t *dir_diag)
{
    if (road->height_undirect > 0)
        *dir_diag = SOUTH_TILE;
    if (road->height_undirect < 0)
        *dir_diag = NORTH_TILE;
}

static void direct_north_south(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (road->height_direct > 0)
        *dir_diag = NORTH_TILE;
    if (road->height_direct < 0)
        *dir_diag = SOUTH_TILE;
}

void get_straight_line(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (road->height_direct == 0 && road->width_direct != 0) {
        if (abs(road->width_direct) > abs(road->width_undirect))
            indirect_west_east(road, i, dir_diag);
        else
            direct_west_east(road, i, dir_diag);
    }
    if (road->width_direct == 0 && road->height_direct != 0) {
        if (abs(road->height_direct) > abs(road->height_undirect))
            indirect_north_south(road, i, dir_diag);
        else
            direct_north_south(road, i, dir_diag);
    }
}
