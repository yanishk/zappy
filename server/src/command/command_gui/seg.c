/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** segs
*/

#include "command_gui.h"

int seg_func(server_t *server, char *team_name)
{
    client_t *graphic = get_graphical_client(server);

    if (graphic == NULL)
        return EXIT_WITH_ERROR;
    dprintf(graphic->client_fd, "seg %s\n", team_name);
    return EXIT_WITH_SUCCESS;
}
