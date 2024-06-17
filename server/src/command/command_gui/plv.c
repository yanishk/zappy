/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** plv
*/

#include "command_gui.h"

int plv(server_t *server, zappy_t *zappy, const int player_id)
{
    player_t *player = get_player_by_id(zappy, player_id);
    client_t *graphical = get_graphical_client(server);

    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "plv %d %d\n", player->id, player->level);
    return EXIT_WITH_SUCCESS;
}

int plv_func(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *)
{
    int player_id = atoi(server->cmd_arg_array[1]);

    if (!is_positive_number(server->cmd_arg_array[1]))
        return EXIT_WITH_ERROR;
    return plv(server, zappy, player_id);
}
