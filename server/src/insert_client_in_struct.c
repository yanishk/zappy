/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** server
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

client_t *get_client_in_struct(server_t *server, const int client_fd)
{
    for (size_t i = 0; i != MAX_USER; i += 1) {
        if (server->clients[i]->client_fd == client_fd) {
            return server->clients[i];
        }
    }
    return NULL;
}

client_t *insert_client_in_struct(server_t *server, const int client_fd)
{
    client_t *client = get_client_in_struct(server, client_fd);

    if (client != NULL)
        return client;
    for (size_t i = 0; i != MAX_USER; i += 1) {
        if (server->clients[i]->client_fd == 0) {
            server->clients[i]->client_fd = client_fd;
            return server->clients[i];
        }
    }
    return NULL;
}
