/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** exit
*/

#include <stdlib.h>
#include "server.h"

int exit_func(server_t *server)
{
    server->clients[server->user_index]->has_been_closed = true;
    return EXIT_WITH_SUCCESS;
}
