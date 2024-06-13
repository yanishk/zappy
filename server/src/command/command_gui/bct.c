/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** bct
*/

#include "command_gui.h"

int bct_func(server_t *server, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    int tile_width = get_tile_index(server->cmd_arg_array[1], arg->width);
    int tile_height = get_tile_index(server->cmd_arg_array[2], arg->height);

    if (tile_width == ERROR_RETURN || tile_height == ERROR_RETURN)
        return EXIT_WITH_ERROR;
    print_tile_resources(client->client_fd, tile_width, tile_height,
        zappy->resource[tile_height][tile_width]);
    return EXIT_WITH_SUCCESS;
}
