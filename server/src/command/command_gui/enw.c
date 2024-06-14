/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** enw
*/

#include "command_gui.h"

int enw_func(server_t *server, player_t *player, const int egg_id)
{
    client_t *graphical = get_graphical_client(server);

    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "enw %d %d %d %d\n",
        egg_id, player->id, player->width, player->height);
    return EXIT_WITH_SUCCESS;
}
