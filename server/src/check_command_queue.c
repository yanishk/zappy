/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** check_command_queue
*/

#include "server.h"

static void call_commands(server_t *server, zappy_t *zappy,
    const arguments_t arg, client_t *client)
{
    time_t end;
    int status = 0;
    command_t *command;

    for ((command) = ((&client->command_head)->tqh_first); (command);
        (command) = ((command)->command_entries.tqe_next)) {
        end = time(NULL);
        if (difftime(end, command->time_begin) >= command->time_unit) {
            server->cmd_arg_array = command->tab;
            status = command->index == NB_CMD ?
            connect_player(server, zappy, arg, client->client_fd) :
            cmd_func[command->index](server, zappy, arg, client);
            answer_client(status, client->client_fd);
            free_array(command->tab);
            TAILQ_REMOVE(&client->command_head, command, command_entries);
        }
    }
}

void check_command_queue(server_t *server, zappy_t *zappy,
    const arguments_t arg, const int client_fd)
{
    client_t *client = get_client_in_struct(server, client_fd);

    if (client == NULL)
        return;
    if (TAILQ_EMPTY(&client->command_head))
        return;
    call_commands(server, zappy, arg, client);
}
