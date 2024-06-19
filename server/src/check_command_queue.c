/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** check_command_queue
*/

#include "command_ia.h"

void check_command_queue(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    int status = 0;
    command_ia_t *command = NULL;
    command_ia_t *command_next = NULL;

    command = TAILQ_FIRST(&client->command_head);
    while (command != NULL) {
        command_next = TAILQ_NEXT(command, command_ia_entries);
        if (time_is_up(command->clock_begin, command->time_unit)) {
            server->cmd_arg_array = command->array;
            status = command->index == NB_IA_CMD ? UNKNOWN_COMMAND :
            cmd_list_ia[command->index].func(server, zappy, arg, client);
            answer_client(status, client->client_fd);
            free_ia_command(client, command);
            command = command_next;
            continue;
        }
        command = NULL;
    }
}
