/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_server
*/

#include "server.h"

static int check_socket_creation(server_t *server)
{
    if (server->server_fd == -1) {
        fprintf(stderr, "socket creation failed\n");
        return EXIT_WITH_ERROR;
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt");
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

static int check_socket_config(server_t *server)
{
    server->sock_addr.sin_family = AF_INET;
    server->sock_addr.sin_addr.s_addr = INADDR_ANY;
    server->sock_addr.sin_port = htons(server->port);
    if (bind(server->server_fd, (struct sockaddr *) &server->sock_addr,
        sizeof(server->sock_addr)) < 0) {
        perror("bind");
        return EXIT_WITH_ERROR;
    }
    if (listen(server->server_fd, 10) == -1) {
        perror("listen");
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

static int *create_int_array(int size)
{
    int *array = malloc(sizeof(int) * size);

    if (array == NULL)
        return NULL;
    array[0] = 0;
    return array;
}

int initialize_server(server_t *server)
{
    if (check_socket_creation(server) == EXIT_WITH_ERROR ||
        check_socket_config(server) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}

void init_client(client_t *client)
{
    client->client_fd = 0;
    client->has_been_closed = false;
    client->is_graphic = false;
    TAILQ_INIT(&client->command_head);
}

static void init_client_struct(server_t *server)
{
    server->clients = malloc(sizeof(client_t) * (server->max_clients));
    for (size_t i = 0; i != server->max_clients; i += 1) {
        server->clients[i] = malloc(sizeof(client_t));
        init_client(server->clients[i]);
    }
}

server_t *init_server_struct(const arguments_t arg)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return NULL;
    server->port = arg.port;
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server->fd_array_size = 1;
    server->fd_array = create_int_array(server->fd_array_size);
    server->max_clients = 1;
    if (server->fd_array == NULL)
        return NULL;
    init_client_struct(server);
    return server;
}
