/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** free_game
*/

#include <unistd.h>
#include "server.h"

void free_player(zappy_t *zappy, player_t *player)
{
    if (player != NULL) {
        TAILQ_REMOVE(&zappy->player_head, player, player_entries);
        if (player->team_name != NULL)
            free(player->team_name);
        free(player);
    }
}

void free_egg(zappy_t *zappy, egg_t *egg)
{
    if (egg != NULL) {
        TAILQ_REMOVE(&zappy->egg_head, egg, egg_entries);
        if (egg->team_name != NULL)
            free(egg->team_name);
        free(egg);
    }
}

void free_link(zappy_t *zappy, link_t *link)
{
    if (link != NULL) {
        TAILQ_REMOVE(&zappy->link_head, link, link_entries);
        free(link);
    }
}

void free_link_by_client_fd(zappy_t *zappy, const unsigned int client_fd)
{
    link_t *link = get_link_by_client_fd(zappy, client_fd);

    if (link == NULL)
        return;
    free_link(zappy, link);
}

static void free_players(zappy_t *zappy)
{
    player_t *player = TAILQ_FIRST(&zappy->player_head);
    player_t *player_next = NULL;

    while (player != NULL) {
        if (player->team_name != NULL)
            free(player->team_name);
        player_next = TAILQ_NEXT(player, player_entries);
        free(player);
        player = player_next;
    }
}

static void free_eggs(zappy_t *zappy)
{
    egg_t *egg = TAILQ_FIRST(&zappy->egg_head);
    egg_t *egg_next = NULL;

    while (egg != NULL) {
        if (egg->team_name != NULL)
            free(egg->team_name);
        egg_next = TAILQ_NEXT(egg, egg_entries);
        free(egg);
        egg = egg_next;
    }
}

static void free_links(zappy_t *zappy)
{
    link_t *link = TAILQ_FIRST(&zappy->link_head);
    link_t *link_next = NULL;

    while (link != NULL) {
        link_next = TAILQ_NEXT(link, link_entries);
        free(link);
        link = link_next;
    }
}

static void free_map(zappy_t *zappy, const arguments_t *arg)
{
    for (int x = 0; x < arg->height; x++)
        free(zappy->resource[x]);
    free(zappy->resource);
}

void free_game(zappy_t *zappy, const arguments_t *arg)
{
    free(zappy->infos);
    free_map(zappy, arg);
    free_links(zappy);
    free_eggs(zappy);
    free_players(zappy);
}
