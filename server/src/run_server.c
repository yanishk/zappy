/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** run_server
*/

#include <signal.h>
#include <errno.h>
#include "server.h"

static sig_atomic_t handle_server(const volatile sig_atomic_t new_status)
{
    static volatile sig_atomic_t status = 1;

    if (new_status != 1)
        status = new_status;
    return status;
}

static void handle_ctrl_c(int signal)
{
    if (signal == SIGINT)
        handle_server(0);
}

static int check_clients_sockets(server_t *server, zappy_t *zappy,
    arguments_t *arg)
{
    int client_fd = 0;
    client_t *client = NULL;

    for (size_t i = 0; i != server->fd_array_size; i += 1) {
        client_fd = server->fd_array[i];
        if (FD_ISSET(client_fd, &server->readfds) != 0) {
            client = insert_client_in_struct(server, client_fd);
            get_user_input(server, zappy, arg, client);
        } else
            client = get_client_in_struct(server, client_fd);
        check_players_food(server, zappy, *arg);
        if (client == NULL)
            continue;
        if (client->client_fd != 0)
            check_command_queue(server, zappy, arg, client);
        close_client_socket(server, zappy, client);
    }
    return EXIT_WITH_SUCCESS;
}

static int add_client_socket(server_t *server, int new_client_fd)
{
    bool has_been_set = false;

    for (size_t i = 0; i != server->fd_array_size; i += 1) {
        if (server->fd_array[i] == 0) {
            server->fd_array[i] = new_client_fd;
            has_been_set = true;
            break;
        }
    }
    if (!has_been_set) {
        server->fd_array_size += 1;
        server->fd_array = realloc(server->fd_array,
            sizeof(int) * server->fd_array_size);
        if (server->fd_array == NULL)
            return EXIT_WITH_ERROR;
        server->fd_array[server->fd_array_size - 1] = new_client_fd;
    }
    return EXIT_WITH_SUCCESS;
}

static int accept_connections(server_t *server, int new_client_fd)
{
    socklen_t addrlen = sizeof(server->sock_addr);

    new_client_fd = accept(server->server_fd,
        (struct sockaddr *) &server->sock_addr, &addrlen);
    if (new_client_fd == -1) {
        perror("accept");
        return EXIT_WITH_ERROR;
    }
    return new_client_fd;
}

static int check_server_socket(server_t *server)
{
    int new_client_fd = 0;

    if (FD_ISSET(server->server_fd, &server->readfds) != 0) {
        new_client_fd = accept_connections(server, new_client_fd);
        if (new_client_fd == EXIT_WITH_ERROR)
            return EXIT_WITH_ERROR;
        dprintf(new_client_fd, "WELCOME\n");
        if (add_client_socket(server, new_client_fd) == EXIT_WITH_ERROR)
            return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

static void set_clients_sockets(server_t *server, unsigned int *max_fd_set)
{
    unsigned int client_fd = 0;

    *max_fd_set = server->server_fd;
    for (size_t i = 0; i != server->fd_array_size; i += 1) {
        client_fd = server->fd_array[i];
        if (client_fd != 0)
            FD_SET(client_fd, &server->readfds);
        if (client_fd > *max_fd_set)
            *max_fd_set = client_fd;
    }
}

static int set_sockets(server_t *server)
{
    static unsigned int max_fd_set = 0;
    struct timeval timeout = {0};

    FD_ZERO(&server->readfds);
    FD_SET(server->server_fd, &server->readfds);
    set_clients_sockets(server, &max_fd_set);
    if (select(max_fd_set + 1, &server->readfds,
        NULL, NULL, &timeout) == -1) {
        perror("select");
        if (errno == EINTR)
            return INTERRUPTED_SYSCALL;
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

int run_server(server_t *server, zappy_t *zappy, arguments_t *arg)
{
    int select_status = 0;
    clock_t refill = clock();

    signal(SIGINT, handle_ctrl_c);
    signal(SIGPIPE, handle_ctrl_c);
    while (handle_server(1)) {
        select_status = set_sockets(server);
        if (select_status != EXIT_WITH_SUCCESS)
            return select_status;
        if (check_server_socket(server) == EXIT_WITH_ERROR ||
            check_clients_sockets(server, zappy, arg) == EXIT_WITH_ERROR)
            return EXIT_WITH_ERROR;
        refill_map(zappy, *arg, server, &refill);
        if (win_condition(server, zappy, arg) != NULL)
            return EXIT_WITH_SUCCESS;
    }
    return EXIT_WITH_SUCCESS;
}
