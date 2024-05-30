/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

static void free_server_struct(server_t *server)
{
    close(server->server_fd);
    free(server->fd_array);
    free(server);
}

int server(int ac, const char **av)
{
    arguments_t arg;
    server_t *server;

    if (init_arg_struct(ac, av, &arg) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    server = init_server_struct(arg.port);
    if (server == NULL)
        return EXIT_WITH_ERROR;
    if (initialize_server(server) == EXIT_WITH_ERROR ||
        run_server(server) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    free_server_struct(server);
    return EXIT_WITH_SUCCESS;
}
