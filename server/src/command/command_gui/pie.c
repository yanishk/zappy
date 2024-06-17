/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pie
*/

#include "command_gui.h"

int pie_func(server_t *server, player_t *player, bool success)
{
    client_t *graphical = get_graphical_client(server);

    if (graphical == NULL || player == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "pie %d %d %d\n",
        player->width, player->height, success);
    return EXIT_WITH_SUCCESS;
}
