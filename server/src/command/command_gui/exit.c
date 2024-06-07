/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** exit
*/

#include <stdlib.h>
#include "server.h"

int exit_func(client_t *client)
{
    client->has_been_closed = true;
    return EXIT_WITH_SUCCESS;
}
