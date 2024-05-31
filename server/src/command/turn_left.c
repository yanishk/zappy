/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** turn_left
*/

#include "server.h"
#include "map.h"

int turn_left(server_t *, zappy_t *zappy, const arguments_t,
    const unsigned int client_fd)
{
    player_t *player = get_player(zappy, client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (player->direction == NORTH) {
        player->direction = WEST;
    } else {
        player->direction -= RIGHT_ANGLE;
    }
    return EXIT_WITH_SUCCESS;
}
