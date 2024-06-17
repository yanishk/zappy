/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** exit
*/

#include "server.h"

int exit_func(server_t *, zappy_t *, arguments_t *, client_t *client)
{
    client->has_been_closed = true;
    return EXIT_WITH_SUCCESS;
}
