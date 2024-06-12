/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** get_player_direction
*/

#include "server.h"

static struct direction_player const direction[] = {
    {NORTH, 1},
    {EAST, 2},
    {SOUTH, 3},
    {WEST, 4}
};

int get_player_direction(const player_t *player)
{
    if (player == NULL)
        return ERROR_RETURN;
    for (size_t index = 0; index < NB_DIRECTIONS; index++) {
        if (direction[index].angle == player->direction)
            return direction[index].direction;
    }
    return EXIT_WITH_SUCCESS;
}
