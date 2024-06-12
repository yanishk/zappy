/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pdi
*/

#include "command_gui.h"

int pdi_func(server_t *server, zappy_t *zappy, const unsigned int client_fd)
{
    player_t *player = get_player_by_fd(zappy, client_fd);
    client_t *graphical = get_graphical_client(server);

    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "pdi %d\n", player->id);
    return EXIT_WITH_SUCCESS;
}
