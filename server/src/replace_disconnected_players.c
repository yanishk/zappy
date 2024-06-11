/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** replace_disconnected_players
*/

#include <string.h>
#include "map.h"

static void count_team_players(zappy_t *zappy, team_t *team, player_t *player,
    int *nb_players)
{
    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (strcmp(team->team_name, player->team_name) == 0) {
            *nb_players += 1;
        }
    }
}

void replace_disconnected_players(const arguments_t arg, zappy_t *zappy)
{
    team_t *team = NULL;
    player_t *player = NULL;
    int nb_players = 0;

    for ((team) = ((&arg.team_head)->tqh_first); (team);
        (team) = ((team)->team_entries.tqe_next)) {
        nb_players = 0;
        count_team_players(zappy, team, player, &nb_players);
        while (nb_players < arg.nb_clients) {
            initialize_player(arg, zappy, team->team_name, IS_EGG_FROM_START);
            nb_players++;
        }
    }
}
