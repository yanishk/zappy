/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** sgt
*/

#include "command_gui.h"

int sgt_func(server_t *server, zappy_t *, arguments_t *arg, client_t *)
{
    client_t *graphical = get_graphical_client(server);

    if (graphical == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphical->client_fd, "sgt %d\n", arg->freq);
    return EXIT_WITH_SUCCESS;
}
