/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** call_cmd_function
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"
#include "map.h"

int (*cmd_func[NB_CMD])(server_t *server, zappy_t *zappy, int client_fd) = {
    &exit_func,
    &inventory_command,
    &take_command
};

static int read_client_socket(server_t *server, const unsigned int client_fd)
{
    char buffer[BUFFER_MAX_SIZE] = {0};

    if (read(client_fd, buffer, BUFFER_MAX_SIZE) == 0)
        return EXIT_WITH_ERROR;
    server->cmd_arg.tab = word_array(buffer, "\n ");
    server->cmd_arg.len = array_size(server->cmd_arg.tab);
    if (strlen(server->cmd_arg.tab[0]) == 0)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}

void get_user_input(server_t *server, zappy_t *zappy, const arguments_t arg)
{
    int status = UNKNOWN_COMMAND;
    unsigned int client_fd = server->clients[server->user_index]->client_fd;

    if (read_client_socket(server, client_fd) == EXIT_WITH_ERROR)
        return;
    for (size_t i = 0; i < NB_CMD; i++) {
        if (server->cmd_arg.len >= 1 &&
        strcmp(server->cmd_arg.tab[0], cmd_lst[i]) == 0) {
            status = cmd_func[i](server, zappy, client_fd);
        }
    }
    printf("status = %d\n", status);
    if (server->cmd_arg.len == 1 && !is_player_connected(zappy, client_fd) &&
        status == UNKNOWN_COMMAND)
        status = connect_player(server, zappy, arg, client_fd);
    if (status == UNKNOWN_COMMAND || status == EXIT_WITH_ERROR)
        dprintf(client_fd, "ko\n");
    else
        dprintf(client_fd, "ok\n");
    free(server->cmd_arg.tab);
}
