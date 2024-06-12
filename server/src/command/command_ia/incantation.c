/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include "command_ia.h"


static resource_t const elevations_resources[NB_ELEVATIONS] = {
    {1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0},
    {2, 0, 1, 0, 2, 0, 0},
    {1, 1, 2, 0, 1, 0, 0},
    {1, 2, 1, 3, 0, 0, 0},
    {1, 2, 3, 0, 1, 0, 0},
    {2, 2, 2, 2, 2, 1, 0}
};

static incantation_t const elevations[NB_ELEVATIONS] = {
    {2, 1, &elevations_resources[0]},
    {3, 2, &elevations_resources[1]},
    {4, 2, &elevations_resources[2]},
    {5, 4, &elevations_resources[3]},
    {6, 4, &elevations_resources[4]},
    {7, 6, &elevations_resources[5]},
    {8, 6, &elevations_resources[6]},
};

#define REQUIRED_RESOURCE elevations[player->level - 1].required_resources
#define REQUIRED_LEVEL elevations[index].elevation_level - 1
#define REQUIRED_PLAYER elevations[index].required_players

static int check_required_resources(zappy_t *zappy, player_t *player)
{
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    for (size_t i = 0; i < NB_RESOURCES; i++) {
        if (get_resources(&TILE_RESOURCE, resource_list[i])
            < get_resources(REQUIRED_RESOURCE, resource_list[i])) {
                return EXIT_WITH_ERROR;
            }
    }
    return EXIT_WITH_SUCCESS;
}

static unsigned int command_queue_size(zappy_t *zappy)
{
    player_t *player_on_tile = NULL;
    unsigned int count_commands = 0;

    TAILQ_FOREACH(player_on_tile, &zappy->player_head, player_entries) {
        count_commands++;
    }
    return count_commands;
}

static int fill_required_player(zappy_t *zappy, player_t *player_start)
{
    player_t *player_on_tile = NULL;
    id_elevation_t *id_elevation = malloc(sizeof(id_elevation_t));

    TAILQ_INSERT_TAIL(&zappy->id_elevation_head, id_elevation, id_elevation_entries);
    id_elevation->player_id = player_start->id;
    TAILQ_FOREACH(player_on_tile, &zappy->player_head, player_entries) {
        if (player_on_same_tile(player_start, player_on_tile) && player_on_tile->level == player_start->level) {
            TAILQ_INSERT_TAIL(&zappy->id_elevation_head, id_elevation, id_elevation_entries);
            id_elevation->player_id = player_on_tile->id;
        }
    }
    return EXIT_WITH_SUCCESS;
}

static int check_required_player(zappy_t *zappy, player_t *player)
{
    int size_queue = 0;

    fill_required_player(zappy, player);
    size_queue = command_queue_size(zappy);
    for (int index = 0; index < NB_ELEVATIONS; index++) {
        if (REQUIRED_LEVEL == player->level && REQUIRED_PLAYER <= size_queue) {
            return EXIT_WITH_SUCCESS;
        }
    }
    return EXIT_WITH_ERROR;
}

int incantation(server_t *, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (check_required_resources(zappy, player) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    if (check_required_player(zappy, player) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
