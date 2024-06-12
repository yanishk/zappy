/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connect_nbr
*/

#include "server.h"

int connect_nbr(server_t *, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    char *team = NULL;
    unsigned int count_unused = 0;

    if (player == NULL)
        return EXIT_WITH_ERROR;
    team = player->team_name;
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (strcmp(player->team_name, team) == 0) {
            count_unused += 1;
        }
    }
    dprintf(client->client_fd, "%d\n", count_unused);
    return COMMAND_SUCCESS;
}
