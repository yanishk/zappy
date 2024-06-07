/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** check_command_queue
*/

#include "server.h"
#include "command_ia.h"

void check_command_queue(server_t *server, zappy_t *zappy,
    const arguments_t arg, client_t *client)
{
    int status = 0;
    command_ia_t *command = NULL;

    if (TAILQ_EMPTY(&client->command_head))
        return;
    for ((command) = ((&client->command_head)->tqh_first); (command);
        (command) = ((command)->command_entries.tqe_next)) {
        if (time_is_up(command->clock_begin, command->time_unit)) {
            server->cmd_arg_array = command->array;
            status = command->index == NB_IA_CMD ?
            connect_player(server, zappy, arg, client) :
            cmd_func_ia[command->index](server, zappy, arg, client);
            answer_client(status, client->client_fd);
            free_array(command->array);
            TAILQ_REMOVE(&client->command_head, command, command_entries);
        }
    }
}
