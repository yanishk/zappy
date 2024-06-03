/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_player_by_id
*/

#include "map.h"

player_t *get_player(zappy_t *zappy, const unsigned int client_fd)
{
    player_t *player;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->id == client_fd)
            return player;
    }
    return NULL;
}
