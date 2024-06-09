/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork_player
*/

#include "command_gui.h"

int fork_player(server_t *server, zappy_t *zappy, const arguments_t arg,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);

    initialize_egg(arg, zappy, player->team_name, EGG_FROM_FORK);
    pfk_func(server, zappy, client->client_fd);
    return EXIT_WITH_SUCCESS;
}
