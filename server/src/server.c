/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "server.h"
#include "map.h"

static void free_server_struct(server_t *server)
{
    close(server->server_fd);
    free(server->fd_array);
    free(server);
}

static void init_basis_map(zappy_t *zappy, arguments_t *arg)
{
    zappy->resource = malloc(sizeof(resource_t *) * arg->width);
    for (int x = 0; x < arg->height; x++)
        zappy->resource[x] = malloc(sizeof(resource_t) * arg->height);
    density_onland(arg, zappy);
}

int server(int ac, const char **av)
{
    server_t *server;
    arguments_t arg;
    zappy_t zappy;

    TAILQ_INIT(&zappy.player_head);
    srand(time(NULL));
    if (fill_arg_struct(ac, av, &arg) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    init_basis_map(&zappy, &arg);
    server = init_server_struct(arg.port);
    initialize_map(arg, &zappy);
    if (server == NULL)
        return EXIT_WITH_ERROR;
    if (initialize_server(server) == EXIT_WITH_ERROR ||
        run_server(server, &zappy, arg) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    free_server_struct(server);
    return EXIT_WITH_SUCCESS;
}
