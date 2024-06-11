/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork_player
*/

#include "command_gui.h"

static void init_fork_egg(zappy_t *zappy, char *team_name, int pos_height,
    int pos_width)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (egg == NULL)
        return;
    TAILQ_INSERT_TAIL(&zappy->egg_head, egg, egg_entries);
    egg->height = pos_height;
    egg->width = pos_width;
    egg->team_name = strdup(team_name);
    egg->id = get_next_id(&zappy->infos->last_egg_id);
}

int fork_player(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    init_fork_egg(zappy, player->team_name, player->height, player->width);
    pfk_func(server, zappy, client->client_fd);
    return EXIT_WITH_SUCCESS;
}
