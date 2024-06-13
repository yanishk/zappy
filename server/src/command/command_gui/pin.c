/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** plv
*/

#include "command_gui.h"

int pin(server_t *server, zappy_t *zappy, const int player_id)
{
    resource_t *resource = NULL;
    player_t *player = NULL;
    client_t *graphical = get_graphical_client(server);

    player = get_player_by_id(zappy, player_id);
    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    resource = &player->inventory;
    dprintf(graphical->client_fd, "pin %d %d %d %ld %ld %ld %ld %ld %ld %ld\n",
        player->id, player->width, player->height, resource->food,
        resource->linemate, resource->deraumere, resource->sibur,
        resource->mendiane, resource->phiras, resource->thystame);
    return EXIT_WITH_SUCCESS;
}

int pin_func(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *)
{
    int player_id = atoi(server->cmd_arg_array[1]);

    if (!is_positive_number(server->cmd_arg_array[1]))
        return EXIT_WITH_ERROR;
    return pin(server, zappy, player_id);
}
