/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** mct
*/

#include "command_gui.h"

int mct_func(server_t *, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    for (int i = 0; i < arg->height; i++) {
        for (int j = 0; j < arg->width; j++) {
            print_tile_resources(client->client_fd, j, i,
                zappy->resource[i][j]);
        }
    }
    return EXIT_WITH_SUCCESS;
}
