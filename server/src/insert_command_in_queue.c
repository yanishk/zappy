/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** insert_command_in_queue
*/

#include "command_ia.h"

static bool command_arg_is_valid(server_t *server, const char *command_name)
{
    if (strcmp(SET_COMMAND, command_name) == 0 ||
        strcmp(TAKE_COMMAND, command_name) == 0)
        return is_a_resource(server->cmd_arg_array[1]);
    return true;
}

int insert_game_command_in_queue(server_t *server, arguments_t arg,
    client_t *client)
{
    command_ia_t *command = NULL;

    for (size_t i = 0; i < NB_IA_CMD; i++) {
        if (array_size(server->cmd_arg_array) == cmd_list_ia[i].arg_nb &&
        strcmp(server->cmd_arg_array[0], cmd_list_ia[i].name) == 0 &&
        command_arg_is_valid(server, cmd_list_ia[i].name)) {
            command = malloc(sizeof(command_ia_t));
            TAILQ_INSERT_TAIL(&client->command_head, command,
                command_ia_entries);
            command->array = server->cmd_arg_array;
            command->time_unit =
                calculate_freq(arg.freq, cmd_list_ia[i].time_unit);
            command->index = i;
            command->clock_begin = clock();
            return EXIT_WITH_SUCCESS;
        }
    }
    return UNKNOWN_COMMAND;
}

void insert_other_command_in_queue(server_t *server,
    client_t *client)
{
    command_ia_t *command = NULL;

    command = malloc(sizeof(command_ia_t));
    TAILQ_INSERT_TAIL(&client->command_head, command, command_ia_entries);
    command->array = server->cmd_arg_array;
    command->time_unit = 0;
    command->index = NB_IA_CMD;
    command->clock_begin = clock();
}
