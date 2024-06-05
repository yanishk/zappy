/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** get_user_input
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"
#include "map.h"
#include "command.h"

static int read_client_socket(server_t *server, client_t *client)
{
    char buffer[MAX_BUFFER_SIZE] = {0};

    if (read(client->client_fd, buffer, MAX_BUFFER_SIZE) == 0) {
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
        dprintf(client_fd, COMMAND_KO);
    else
        dprintf(client_fd, COMMAND_OK);
}

static int insert_game_command_in_queue(server_t *server, client_t *client)
{
    command_t *command = NULL;

    for (size_t i = 0; i < NB_CMD; i++) {
        if (array_size(server->cmd_arg_array) >= 1 &&
        strcmp(server->cmd_arg_array[0], cmd_list[i].name) == 0) {
            command = malloc(sizeof(command_t));
            TAILQ_INSERT_TAIL(&client->command_head, command, command_entries);
            command->tab = server->cmd_arg_array;
            command->time_unit = cmd_list[i].time_unit;
            command->index = i;
            command->clock_begin = clock();
            return EXIT_WITH_SUCCESS;
        }
    }
    return UNKNOWN_COMMAND;
}

static void insert_other_command_in_queue(server_t *server,
    client_t *client)
{
    command_t *command = NULL;

    command = malloc(sizeof(command_t));
    TAILQ_INSERT_TAIL(&client->command_head, command, command_entries);
    command->tab = server->cmd_arg_array;
    command->time_unit = 0;
    command->index = NB_CMD;
    command->clock_begin = clock();
}

void get_user_input(server_t *server, zappy_t *zappy, client_t *client)
{
    int status = UNKNOWN_COMMAND;

    if (read_client_socket(server, client) != EXIT_WITH_SUCCESS)
        return;
    if (is_command_queue_full(client)) {
        if (server->cmd_arg_array != NULL)
            free_array(server->cmd_arg_array);
        return;
    }
    if (is_player_connected(zappy, client->client_fd))
        status = insert_game_command_in_queue(server, client);
    if (status == UNKNOWN_COMMAND)
        insert_other_command_in_queue(server, client);
}
