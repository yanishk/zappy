/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** choose_random_egg
*/

#include <string.h>
#include "server.h"

static player_t **get_team_eggs(zappy_t *zappy,
    size_t *nb_players, char *team_name)
{
    player_t *player = NULL;
    player_t **egg_array = NULL;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (strcmp(team_name, player->team_name) == 0 &&
            player->status != IS_PLAYER) {
            *nb_players += 1;
            egg_array = realloc(egg_array, sizeof(player_t *) * (*nb_players));
            egg_array[(*nb_players) - 1] = player;
        }
    }
    return egg_array;
}

player_t *get_random_team_egg(zappy_t *zappy, char *team_name)
{
    player_t **egg_array = NULL;
    size_t nb_players = 0;

    egg_array = get_team_eggs(zappy, &nb_players, team_name);
    if (egg_array == NULL || nb_players == 0)
        return NULL;
    return egg_array[rand() % nb_players];
}
