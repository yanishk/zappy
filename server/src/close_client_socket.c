/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** close_client_socket
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

static void remove_client_socket(server_t *server, const int client_fd)
{
    for (size_t i = 0; i != server->size; i += 1) {
        if (server->fd_array[i] == client_fd) {
            server->fd_array[i] = 0;
            break;
        }
    }
}

void close_client_socket(server_t *server, zappy_t *zappy, client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (client->has_been_closed) {
        close(client->client_fd);
        FD_CLR(client->client_fd, &server->readfds);
        remove_client_socket(server, client->client_fd);
        free_player(zappy, player);
        free_link_by_client_fd(zappy, client->client_fd);
        client->client_fd = 0;
        client->has_been_closed = false;
        client->is_graphic = false;
    }
}
