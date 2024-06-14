/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** turn_right
*/

#include "command_gui.h"

int turn_right(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (player->direction == WEST)
        player->direction = NORTH;
    else
        player->direction += RIGHT_ANGLE;
    ppo(server, zappy, player->id);
    return EXIT_WITH_SUCCESS;
}
