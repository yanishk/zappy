/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** get_user_input
*/

#include <unistd.h>
#include "command_ia.h"
#include "command_gui.h"

static int read_client_socket(server_t *server, zappy_t *zappy,
    client_t *client)
{
    char buffer[MAX_BUFFER_SIZE] = {0};

    if (read(client->client_fd, buffer, MAX_BUFFER_SIZE) == 0) {
        pdi_func(server, zappy, client->client_fd);
        client->has_been_closed = true;
        return EXIT_WITH_ERROR;
    }
    server->cmd_arg_array = word_array(buffer, "\n ");
    if (strlen(server->cmd_arg_array[0]) == 0)
        return UNKNOWN_COMMAND;
    return EXIT_WITH_SUCCESS;
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
    if (status == UNKNOWN_COMMAND)
        insert_other_command_in_queue(server, client);
}

void get_user_input(server_t *server, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    if (read_client_socket(server, zappy, client) != EXIT_WITH_SUCCESS)
        return;
    if (connect_graphical_client(server, zappy, arg, client))
        return;
    if (client->is_graphic)
        return execute_graphical_command(server, zappy, arg, client);
    insert_command_in_queue(server, zappy, arg, client);
}
