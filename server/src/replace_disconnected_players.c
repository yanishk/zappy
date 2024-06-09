/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** replace_disconnected_players
*/

#include <string.h>
#include "server.h"

void replace_disconnected_players(const arguments_t arg, zappy_t *zappy)
{
    team_t *team = NULL;
    int count_slots = 0;

    for ((team) = ((&arg.team_head)->tqh_first); (team);
        (team) = ((team)->team_entries.tqe_next)) {
        count_slots = count_team_slots(zappy, team->team_name);
        while (count_slots < arg.nb_clients) {
            initialize_egg(arg, zappy, team->team_name, EGG_FROM_START);
            count_slots++;
        }
    }
}
