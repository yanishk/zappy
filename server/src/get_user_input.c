/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** get_user_input
*/

#include <unistd.h>
#include "command_ia.h"
#include "command_gui.h"

static char **split_commands(const char *read_buffer)
{
    static char final_buffer[MAX_BUFFER_SIZE] = {'\0'};
    char **tmp_commands_array = NULL;

    final_buffer[MAX_BUFFER_SIZE - 1] = '\0';
    strcat(final_buffer, read_buffer);
    if (!has_backslash(read_buffer))
        return NULL;
    tmp_commands_array = word_array(final_buffer, "\n");
    memset(final_buffer, '\0', sizeof(final_buffer));
    return tmp_commands_array;
}

static char **read_client_socket(server_t *server, zappy_t *zappy,
    client_t *client)
{
    char read_buffer[MAX_BUFFER_SIZE] = {'\0'};

    if (read(client->client_fd, read_buffer, MAX_BUFFER_SIZE) == 0) {
        pdi_func(server, zappy, client->client_fd);
        client->has_been_closed = true;
        return NULL;
    }
    if (strlen(read_buffer) == 0)
        return NULL;
    read_buffer[MAX_BUFFER_SIZE - 1] = '\0';
    return split_commands(read_buffer);
}

void answer_client(const int status, const unsigned int client_fd)
{
    if (status == UNKNOWN_COMMAND || status == EXIT_WITH_ERROR)
        dprintf(client_fd, "ko\n");
    else if (status == EXIT_WITH_SUCCESS)
        dprintf(client_fd, "ok\n");
}

static void execute_graphical_command(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    int status = UNKNOWN_COMMAND;
    size_t arguments_nb = array_size(server->cmd_arg_array);

    for (size_t i = 0; i < NB_GUI_CMD; i++) {
        if (strcmp(server->cmd_arg_array[0], cmd_list_gui[i].name) == 0) {
            status = arguments_nb == cmd_list_gui[i].arg_nb ?
            cmd_list_gui[i].func(server, zappy, arg, client) : EXIT_WITH_ERROR;
        }
    }
    if (status == UNKNOWN_COMMAND)
        dprintf(client->client_fd, "suc\n");
    if (status == EXIT_WITH_ERROR)
        dprintf(client->client_fd, "sbp\n");
    if (server->cmd_arg_array != NULL)
        free_array(server->cmd_arg_array);
}

static void insert_command_in_queue(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    int status = UNKNOWN_COMMAND;

    if (is_command_queue_full(client)) {
        if (server->cmd_arg_array != NULL)
            free_array(server->cmd_arg_array);
        return;
    }
    if (is_player_connected(zappy, client->client_fd))
        status = insert_game_command_in_queue(server, *arg, client);
    if (connect_player(server, zappy, *arg, client->client_fd)
        == COMMAND_SUCCESS) {
        free_array(server->cmd_arg_array);
        return;
    }
    if (status == UNKNOWN_COMMAND)
        insert_other_command_in_queue(server, client);
}

void get_user_input(server_t *server, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    char **tmp_commands_array = read_client_socket(server, zappy, client);

    if (tmp_commands_array == NULL)
        return;
    for (size_t i = 0; tmp_commands_array[i] != NULL; i++) {
        server->cmd_arg_array = word_array(tmp_commands_array[i], " ");
        if (strlen(server->cmd_arg_array[0]) == 0 ||
            connect_graphical_client(server, zappy, arg, client)) {
            free_array(server->cmd_arg_array);
            continue;
        }
        if (client->is_graphic) {
            execute_graphical_command(server, zappy, arg, client);
        } else {
            insert_command_in_queue(server, zappy, arg, client);
        }
    }
    free_array(tmp_commands_array);
}
