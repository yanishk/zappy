/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include "server.h"

int inventory_command(server_t *, zappy_t *zappy, int client_fd)
{
    player_t *player = get_player(zappy, client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    dprintf(client_fd, "[food %ld, linemate %ld, lderaumere %ld, sibur %ld, "
        "menldiane %ld, phiras %ld, thystame %ld]\n", player->inventory.food,
        player->inventory.linemate, player->inventory.deraumere,
        player->inventory.sibur, player->inventory.mendiane,
        player->inventory.phiras, player->inventory.thystame);
    return EXIT_WITH_SUCCESS;
}
