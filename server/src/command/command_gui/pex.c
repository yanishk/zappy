/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** pex
*/

#include "command_gui.h"

int pex_func(server_t *server, player_t *player)
{
    client_t *graphical = get_graphical_client(server);

    if (graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "pex %d\n", player->id);
    return EXIT_WITH_SUCCESS;
}
