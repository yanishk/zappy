/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pbc
*/

#include "command_gui.h"

int pbc_func(server_t *server, const int player_id, const char *message)
{
    client_t *graphical = get_graphical_client(server);

    if (graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "pbc %d %s\n", player_id, message);
    return EXIT_WITH_SUCCESS;
}
