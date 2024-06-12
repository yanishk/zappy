/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** count_team_slots
*/

#include "server.h"

unsigned int count_team_eggs(const zappy_t *zappy, const char *team_name)
{
    unsigned int count_eggs = 0;
    egg_t *egg = NULL;

    TAILQ_FOREACH(egg, &zappy->egg_head, egg_entries) {
        if (strcmp(team_name, egg->team_name) == 0) {
            count_eggs++;
        }
    }
    return count_eggs;
}

unsigned int count_team_players(const zappy_t *zappy, const char *team_name)
{
    unsigned int count_players = 0;
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (strcmp(team_name, player->team_name) == 0) {
            count_players++;
        }
    }
    return count_players;
}

unsigned int count_team_slots(const zappy_t *zappy,
    const char *team_name)
{
    return (count_team_players(zappy, team_name) +
        count_team_eggs(zappy, team_name));
}
