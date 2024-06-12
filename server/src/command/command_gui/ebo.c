/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ebo
*/

#include "command_gui.h"

int ebo_func(server_t *server, const int id_egg)
{
    client_t *graphical = get_graphical_client(server);

    if (graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "ebo %d\n", id_egg);
    return EXIT_WITH_SUCCESS;
}
