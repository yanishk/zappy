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

int incantation(server_t *, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    if (check_required_resources(zappy, player) == EXIT_WITH_ERROR)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
