/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** turn_left
*/

#include "server.h"
#include "map.h"

int turn_right(server_t *, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (player->direction == WEST)
        player->direction = NORTH;
    else
        player->direction += RIGHT_ANGLE;
    return EXIT_WITH_SUCCESS;
}
