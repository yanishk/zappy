/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** tna
*/

#include "command_gui.h"

int tna_func(server_t *, zappy_t *, arguments_t *arg, client_t *client)
{
    team_t *team = NULL;

    TAILQ_FOREACH(team, &arg->team_head, team_entries)
        dprintf(client->client_fd, "tna %s\n", team->team_name);
    return EXIT_WITH_SUCCESS;
}
