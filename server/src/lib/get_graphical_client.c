/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_graphical_client
*/

#include "server.h"

client_t *get_graphical_client(server_t *server)
{
    for (size_t i = 0; i != server->max_clients; i += 1) {
        if (server->clients[i]->is_graphic)
            return server->clients[i];
    }
    return NULL;
}
