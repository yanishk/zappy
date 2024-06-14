/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** turn_left
*/

#include "command_gui.h"

int turn_left(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (player->direction == NORTH) {
        player->direction = WEST;
    } else {
        player->direction -= RIGHT_ANGLE;
    }
    ppo(server, zappy, player->id);
    return EXIT_WITH_SUCCESS;
}
