/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pic
*/

#include "command_gui.h"

static resource_t const elevations_resources[NB_ELEVATIONS] = {
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0},
    {0, 2, 0, 1, 0, 2, 0},
    {0, 1, 1, 2, 0, 1, 0},
    {0, 1, 2, 1, 3, 0, 0},
    {0, 1, 2, 3, 0, 1, 0},
    {0, 2, 2, 2, 2, 2, 1}
};

static incantation_t const elevations[NB_ELEVATIONS] = {
    {2, 1, &elevations_resources[0]},
    {3, 2, &elevations_resources[1]},
    {4, 2, &elevations_resources[2]},
    {5, 4, &elevations_resources[3]},
    {6, 4, &elevations_resources[4]},
    {7, 6, &elevations_resources[5]},
    {8, 6, &elevations_resources[6]}
};

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
