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

int insert_client_in_struct(server_t *server, const int client_fd)
{
    for (size_t i = 0; i != MAX_USER; i += 1) {
        if (server->clients[i]->client_fd == client_fd) {
            return i;
        }
    }
    for (size_t i = 0; i != MAX_USER; i += 1) {
        if (server->clients[i]->client_fd == 0) {
            server->clients[i]->client_fd = client_fd;
            return i;
        }
    }
    return EXIT_WITH_SUCCESS;
}
