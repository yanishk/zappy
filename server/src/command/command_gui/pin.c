/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** plv
*/

#include "command_gui.h"

int pin_func(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    int player_id = atoi(server->cmd_arg_array[1]);
    player_t *player = NULL;
    resource_t *resource = NULL;

    if (!is_positive_number(server->cmd_arg_array[1]))
        return EXIT_WITH_ERROR;
    player = get_player_by_id(zappy, player_id);
    if (player == NULL)
        return EXIT_WITH_ERROR;
    resource = &player->inventory;
    dprintf(client->client_fd, "pin %d %d %ld %ld %ld %ld %ld %ld %ld\n",
    player->width, player->height, resource->food, resource->linemate,
        resource->deraumere, resource->sibur, resource->mendiane,
        resource->phiras, resource->thystame);
    return EXIT_WITH_SUCCESS;
}
