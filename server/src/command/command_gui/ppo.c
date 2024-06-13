/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** plv
*/

#include "command_gui.h"

int ppo(server_t *server, zappy_t *zappy, const int player_id)
{
    int player_direction = 0;
    player_t *player = NULL;
    client_t *graphic = get_graphical_client(server);

    player = get_player_by_id(zappy, player_id);
    if (player == NULL || graphic == NULL)
        return EXIT_WITH_ERROR;
    player_direction = get_player_direction(player);
    dprintf(graphic->client_fd, "ppo %d %d %d %d\n", player->id,
    player->width, player->height, player_direction);
    return EXIT_WITH_SUCCESS;
}

int ppo_func(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *)
{
    int player_id = atoi(server->cmd_arg_array[1]);

    if (!is_positive_number(server->cmd_arg_array[1]))
        return EXIT_WITH_ERROR;
    return ppo(server, zappy, player_id);
}
