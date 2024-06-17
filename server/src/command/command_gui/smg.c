/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** smg
*/

#include "command_gui.h"

int smg_func(server_t *server, const char *message)
{
    client_t *graphic = get_graphical_client(server);

    if (graphic == NULL || message == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphic->client_fd, "smg %s\n", message);
    return EXIT_WITH_SUCCESS;
}
