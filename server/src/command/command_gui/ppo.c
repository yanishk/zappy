/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** plv
*/

#include "command_gui.h"

int ppo_func(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    int player_id = atoi(server->cmd_arg_array[1]);
    int player_direction = 0;
    player_t *player = NULL;

    if (!is_positive_number(server->cmd_arg_array[1]))
        return EXIT_WITH_ERROR;
    player = get_player_by_id(zappy, player_id);
    if (player == NULL)
        return EXIT_WITH_ERROR;
    player_direction = get_player_direction(player);
    dprintf(client->client_fd, "ppo %d %d %d %d\n", player->id,
    player->width, player->height, player_direction);
    return EXIT_WITH_SUCCESS;
}
