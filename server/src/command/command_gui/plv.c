/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** plv
*/

#include "command_gui.h"

int plv_func(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    int player_id = atoi(server->cmd_arg_array[1]);
    player_t *player = NULL;

    if (!is_positive_number(server->cmd_arg_array[1]))
        return EXIT_WITH_ERROR;
    player = get_player_by_id(zappy, player_id);
    if (player == NULL)
        return EXIT_WITH_ERROR;
    dprintf(client->client_fd, "plv %d %d\n", player->id, player->level);
    return EXIT_WITH_SUCCESS;
}
