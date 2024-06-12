/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** edi
*/

#include "command_gui.h"

int edi_func(server_t *server, const int egg_id)
{
    client_t *graphical = get_graphical_client(server);

    if (graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "edi %d\n", egg_id);
    return EXIT_WITH_SUCCESS;
}
