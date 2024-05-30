/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** call_cmd_function
*/

#include "server.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int (*cmd_func[NB_CMD])(server_t *server) = {
    &exit_func
};

void get_user_input(server_t *server, const int client_fd)
{
    char buffer[BUFFER_MAX_SIZE] = {0};
    int status = 0;

    if (read(client_fd, buffer, BUFFER_MAX_SIZE) == 0)
        return;
    server->cmd_arg.tab = word_array(buffer, "\"\n\r");
    server->cmd_arg.len = array_size(server->cmd_arg.tab);
    for (size_t i = 0; i < NB_CMD; i++) {
        if (server->cmd_arg.len >= 1 &&
        strcmp(server->cmd_arg.tab[0], cmd_lst[i]) == 0) {
            status = cmd_func[i](server);
        }
    }
    if (status == 0)
        dprintf(client_fd, "Unknown command\n");
    free(server->cmd_arg.tab);
}
