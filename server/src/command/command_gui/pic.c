/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pic
*/

#include "command_gui.h"
#include "command_ia.h"

int pic_func(server_t *server, player_t *player, int *id_players)
{
    client_t *graphic = get_graphical_client(server);

    if (graphic == NULL || player == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphic->client_fd, "pic %d %d %d", player->width,
        player->height, player->level);
    for (unsigned int x = 0; x < REQUIRED_PLAYERS; x++) {
        dprintf(graphic->client_fd, " %d", id_players[x]);
    }
    dprintf(graphic->client_fd, "\n");
    return EXIT_WITH_SUCCESS;
}
