/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include "server.h"

int inventory_command(server_t *, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    dprintf(client->client_fd, "[food %ld, linemate %ld, deraumere %ld, "
        "sibur %ld, mendiane %ld, phiras %ld, thystame %ld]\n",
        player->inventory.food, player->inventory.linemate,
        player->inventory.deraumere, player->inventory.sibur,
        player->inventory.mendiane, player->inventory.phiras,
        player->inventory.thystame);
    return COMMAND_SUCCESS;
}
