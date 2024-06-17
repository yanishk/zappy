/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_teams
*/

#include "server.h"

static bool has_already_a_player(zappy_t *zappy, int height, int width)
{
    player_t *player = NULL;
    unsigned int count = 0;

    if (TAILQ_EMPTY(&zappy->player_head))
        return false;
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->height == height && player->width == width)
            count++;
        if (count == 1)
            return true;
    }
    return false;
}

static bool has_already_an_egg(zappy_t *zappy, int height, int width)
{
    egg_t *egg = NULL;
    unsigned int count = 0;

    if (TAILQ_EMPTY(&zappy->egg_head))
        return false;
    TAILQ_FOREACH(egg, &zappy->egg_head, egg_entries) {
        if (egg->height == height && egg->width == width)
            count++;
        if (count == 2)
            return true;
    }
    return false;
}

static void check_existing_eggs_pos(const arguments_t arg, zappy_t *zappy,
    egg_t *egg)
{
    do {
        egg->height = rand() % arg.height;
        egg->width = rand() % arg.width;
    } while (has_already_an_egg(zappy, egg->height, egg->width) ||
        has_already_a_player(zappy, egg->height, egg->width));
}

static void initialize_egg_pos(const arguments_t arg, zappy_t *zappy,
    egg_t *egg)
{
    if (arg.nb_teams * arg.nb_clients <= arg.height * arg.width) {
        check_existing_eggs_pos(arg, zappy, egg);
    } else {
        egg->height = rand() % arg.height;
        egg->width = rand() % arg.width;
    }
}

static size_t initialize_player_direction(void)
{
    return RIGHT_ANGLE * (rand() % 4);
}

void initialize_player(zappy_t *zappy, egg_t *egg)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return;
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    initialize_resources(&player->inventory);
    player->inventory.food = 10;
    player->level = 1;
    player->height = egg->height;
    player->width = egg->width;
    player->team_name = strdup(egg->team_name);
    player->clock_begin = clock();
    player->id = get_next_id(&zappy->infos->last_player_id);
    player->direction = initialize_player_direction();
}

void initialize_egg(const arguments_t arg, zappy_t *zappy, char *team_name)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (egg == NULL)
        return;
    TAILQ_INSERT_TAIL(&zappy->egg_head, egg, egg_entries);
    egg->height = 0;
    egg->width = 0;
    egg->team_name = strdup(team_name);
    egg->id = get_next_id(&zappy->infos->last_egg_id);
    initialize_egg_pos(arg, zappy, egg);
}

void initialize_teams(const arguments_t arg, zappy_t *zappy)
{
    team_t *team = TAILQ_FIRST(&arg.team_head);

    TAILQ_INIT(&zappy->egg_head);
    TAILQ_INIT(&zappy->player_head);
    TAILQ_INIT(&zappy->link_head);
    for (int i = 0; i != arg.nb_teams; i++) {
        for (int j = 0; j != arg.nb_clients; j++)
            initialize_egg(arg, zappy, team->team_name);
        team = TAILQ_NEXT(team, team_entries);
    }
}
