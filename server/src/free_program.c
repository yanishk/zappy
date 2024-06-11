/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** free_program
*/

#include <unistd.h>
#include "server.h"
#include "command_ia.h"

void free_client_commands(client_t *client)
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
        command_next = TAILQ_NEXT(command, command_entries);
        free(command);
        command = command_next;
    }
}

static void free_server(server_t *server)
{
    close(server->server_fd);
    for (size_t i = 0; i != server->max_user; i += 1)
        free_client_commands(server->clients[i]);
    for (size_t i = 0; i != server->max_user; i += 1)
        free(server->clients[i]);
    free(server->clients);
    free(server->fd_array);
    free(server);
}

static void free_arg_teams(arguments_t *arg)
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

void free_ia_command(client_t *client, command_ia_t *command)
{
    if (command != NULL) {
        TAILQ_REMOVE(&client->command_head, command, command_entries);
        if (command->array != NULL) {
            free_array(command->array);
        }
        free(command);
    }
}

void free_zappy_player(zappy_t *zappy, player_t *player)
{
    if (player != NULL) {
        TAILQ_REMOVE(&zappy->player_head, player, player_entries);
        if (player->team_name != NULL)
            free(player->team_name);
        free(player);
    }
}

static void free_zappy_players(zappy_t *zappy)
{
    player_t *player = TAILQ_FIRST(&zappy->player_head);
    player_t *player_next = NULL;

    while (player != NULL) {
        if (player->team_name != NULL)
            free(player->team_name);
        player_next = TAILQ_NEXT(player, player_entries);
        free(player);
        player = player_next;
    }
}

static void free_zappy_map(zappy_t *zappy, const arguments_t *arg)
{
    for (int x = 0; x < arg->height; x++)
        free(zappy->resource[x]);
    free(zappy->resource);
}

void free_program(server_t *server, zappy_t *zappy, arguments_t *arg)
{
    free_zappy_map(zappy, arg);
    free_zappy_players(zappy);
    free_arg_teams(arg);
    free_server(server);
}
