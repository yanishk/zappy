/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_teams
*/

#include <string.h>
#include "server.h"
#include "map.h"

static bool has_already_an_egg(zappy_t *zappy, int height, int width)
{
    player_t *player = NULL;
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

void initialize_player_pos(const arguments_t arg, zappy_t *zappy,
    player_t *player)
{
    if (arg.nb_teams * arg.nb_clients <= arg.height * arg.width) {
        check_existing_eggs_pos(arg, zappy, player);
    } else {
        player->height = rand() % arg.height;
        player->width = rand() % arg.width;
    }
}

static size_t initialize_player_direction(void)
{
    return RIGHT_ANGLE * (rand() % 4);
}

void initialize_player(const arguments_t arg, zappy_t *zappy, char *team_name,
    enum PLAYER_STATUS status)
{
    player_t *player = NULL;

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    initialize_resources(&player->inventory);
    player->inventory.food = 10;
    player->id = 0;
    player->level = 1;
    player->height = 0;
    player->width = 0;
    player->status = status;
    player->team_name = strdup(team_name);
    player->direction = initialize_player_direction();
    initialize_player_pos(arg, zappy, player);
}

void initialize_teams(const arguments_t arg, zappy_t *zappy)
{
    team_t *team = TAILQ_FIRST(&arg.team_head);

    for (int i = 0; i != arg.nb_teams; i++) {
        for (int j = 0; j != arg.nb_clients; j++)
            initialize_player(arg, zappy, team->team_name, IS_EGG_FROM_START);
        team = TAILQ_NEXT(team, team_entries);
    }
}
