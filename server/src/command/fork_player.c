/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork_player
*/

#include "server.h"

int fork_player(server_t *, zappy_t *zappy, const arguments_t arg,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);

    initialize_player(arg, zappy, player->team_name);
    return EXIT_WITH_SUCCESS;
}
