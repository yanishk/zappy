/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** free_program
*/

#include <unistd.h>
#include "command_ia.h"

void free_ia_command(client_t *client, command_ia_t *command)
{
    if (command != NULL) {
        TAILQ_REMOVE(&client->command_head, command, command_ia_entries);
        if (command->array != NULL) {
            free_array(command->array);
        }
        free(command);
    }
}

static void free_ia_commands(client_t *client)
{
    command_ia_t *command = NULL;
    command_ia_t *command_next = NULL;

    if (TAILQ_EMPTY(&client->command_head))
        return;
    command = TAILQ_FIRST(&client->command_head);
    while (command != NULL) {
        if (command->array != NULL) {
            free_array(command->array);
        }
        command_next = TAILQ_NEXT(command, command_ia_entries);
        free(command);
        command = command_next;
    }
}

static void free_server(server_t *server)
{
    close(server->server_fd);
    for (size_t i = 0; i != server->max_clients; i += 1)
        free_ia_commands(server->clients[i]);
    for (size_t i = 0; i != server->max_clients; i += 1)
        free(server->clients[i]);
    free(server->clients);
    free(server->fd_array);
    free(server);
}

void free_arg_teams(arguments_t *arg)
{
    team_t *team = TAILQ_FIRST(&arg->team_head);
    team_t *team_next = NULL;

    while (team != NULL) {
        if (team->team_name != NULL)
            free(team->team_name);
        team_next = TAILQ_NEXT(team, team_entries);
        free(team);
        team = team_next;
    }
}

void free_program(server_t *server, zappy_t *zappy, arguments_t *arg)
{
    free_game(zappy, arg);
    free_arg_teams(arg);
    free_server(server);
}
