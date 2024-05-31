/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_teams
*/

#include <string.h>
#include "server.h"
#include "map.h"

static bool has_already_an_egg(zappy_t *zappy, size_t height, size_t width)
{
    player_t *player;
    unsigned int count = 0;

    if (TAILQ_EMPTY(&zappy->player_head))
        return false;
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->height == height && player->width == width)
            count++;
        if (count == 2)
            return true;
    }
    return false;
}

static void check_existing_eggs_pos(const arguments_t arg, zappy_t *zappy,
    player_t *player)
{
    do {
        player->height = rand() % arg.height;
        player->width = rand() % arg.width;
    } while (has_already_an_egg(zappy, player->height, player->width));
}

static void initialize_players_pos(const arguments_t arg, zappy_t *zappy)
{
    player_t *player;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (arg.nb_teams * arg.nb_clients <= arg.height * arg.width) {
            check_existing_eggs_pos(arg, zappy, player);
        } else {
            player->height = rand() % arg.height;
            player->width = rand() % arg.width;
        }
    }
}

void initialize_players(const arguments_t arg, zappy_t *zappy, team_t *team)
{
    player_t *player;

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    initialize_resources(&player->inventory);
    player->id = 0;
    player->level = 0;
    player->height = 0;
    player->width = 0;
    player->is_egg = true;
    player->team_name = strdup(team->team_name);
    initialize_players_pos(arg, zappy);
}

void initialize_teams(const arguments_t arg, zappy_t *zappy)
{
    team_t *team = TAILQ_FIRST(&arg.team_head);
    team_t *team_next;

    for (int i = 0; i != arg.nb_teams; i++) {
        for (int j = 0; j != arg.nb_clients; j++) {
            initialize_players(arg, zappy, team);
        }
        if (TAILQ_NEXT(team, team_entries) != NULL) {
            team_next = TAILQ_NEXT(team, team_entries);
            free(team);
            team = team_next;
        }
    }
}
