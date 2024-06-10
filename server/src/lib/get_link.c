/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_link
*/

#include "server.h"

link_t *get_link_by_client_fd(const zappy_t *zappy,
    const unsigned int client_fd)
{
    link_t *link = NULL;

    TAILQ_FOREACH(link, &zappy->link_head, link_entries) {
        if (link->client_fd == client_fd)
            return link;
    }
    return NULL;
}

link_t *get_link_by_player_id(const zappy_t *zappy,
    const unsigned int player_id)
{
    link_t *link = NULL;

    TAILQ_FOREACH(link, &zappy->link_head, link_entries) {
        if (link->player_id == player_id)
            return link;
    }
    return NULL;
}

int get_client_fd(const zappy_t *zappy, const unsigned int player_id)
{
    link_t *link = get_link_by_player_id(zappy, player_id);

    if (link == NULL)
        return ERROR_RETURN;
    return link->client_fd;
}

static int get_player_id(const zappy_t *zappy, const unsigned int client_fd)
{
    link_t *link = get_link_by_client_fd(zappy, client_fd);

    if (link == NULL)
        return ERROR_RETURN;
    return link->player_id;
}

player_t *get_player_by_fd(const zappy_t *zappy, const unsigned int client_fd)
{
    int player_id = get_player_id(zappy, client_fd);
    player_t *player = NULL;

    if (player_id == ERROR_RETURN)
        return NULL;
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->id == player_id)
            return player;
    }
    return NULL;
}

player_t *get_player_by_id(const zappy_t *zappy, const int player_id)
{
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->id == player_id)
            return player;
    }
    return NULL;
}
