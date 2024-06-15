/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** insert_client_in_struct
*/

#include "server.h"

client_t *get_client_in_struct(server_t *server, const int client_fd)
{
    for (size_t i = 0; i != server->max_clients; i += 1) {
        if (server->clients[i]->client_fd == client_fd) {
            return server->clients[i];
        }
    }
    return NULL;
}

static client_t *realloc_client_struct(server_t *server, const int client_fd)
{
    server->max_clients += 1;
    server->clients = realloc(server->clients,
        sizeof(client_t) * server->max_clients);
    if (server->clients == NULL)
        return NULL;
    server->clients[server->max_clients - 1] = malloc(sizeof(client_t));
    init_client(server->clients[server->max_clients - 1]);
    server->clients[server->max_clients - 1]->client_fd = client_fd;
    return server->clients[server->max_clients - 1];
}

client_t *insert_client_in_struct(server_t *server, const int client_fd)
{
    client_t *client = get_client_in_struct(server, client_fd);

    if (client != NULL)
        return client;
    for (size_t i = 0; i != server->max_clients; i += 1) {
        if (server->clients[i]->client_fd == 0) {
            server->clients[i]->client_fd = client_fd;
            return server->clients[i];
        }
    }
    return realloc_client_struct(server, client_fd);
}
