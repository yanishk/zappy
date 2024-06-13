/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork_player
*/

#include "command_gui.h"

static int init_fork_egg(zappy_t *zappy, char *team_name, int pos_height,
    int pos_width)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (egg == NULL)
        return ERROR_RETURN;
    TAILQ_INSERT_TAIL(&zappy->egg_head, egg, egg_entries);
    egg->height = pos_height;
    egg->width = pos_width;
    egg->team_name = strdup(team_name);
    egg->id = get_next_id(&zappy->infos->last_egg_id);
    return egg->id;
}

int fork_player(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    int egg_id = init_fork_egg(zappy, player->team_name,
        player->height, player->width);

    if (player == NULL || egg_id == ERROR_RETURN)
        return EXIT_WITH_ERROR;
    pfk_func(server, zappy, client->client_fd);
    enw_func(server, player, egg_id);
    return EXIT_WITH_SUCCESS;
}
