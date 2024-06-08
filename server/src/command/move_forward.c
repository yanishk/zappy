/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** move_forward
*/

#include "command.h"

int move_forward(server_t *, zappy_t *zappy,
    const arguments_t arg, client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    move_player(player->direction, player, arg);
    return EXIT_WITH_SUCCESS;
}
