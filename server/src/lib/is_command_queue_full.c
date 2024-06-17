/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** is_command_queue_full
*/

#include "command_ia.h"

static unsigned int command_queue_size(client_t *client)
{
    command_ia_t *command = NULL;
    unsigned int count_commands = 0;

    TAILQ_FOREACH(command, &client->command_head, command_ia_entries)
        count_commands++;
    return count_commands;
}

bool is_command_queue_full(client_t *client)
{
    if (command_queue_size(client) >= MAX_QUEUE_COMMANDS)
        return true;
    return false;
}
