/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set_object
*/

#include "server.h"
#include "command_ia.h"

int set_object(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    int resource_on_land = 0;
    int resource_in_pocket = 0;

    if (player == NULL || OBJECT_TO_TAKE == NULL)
        return EXIT_WITH_ERROR;
    resource_on_land = get_resources(&TILE_RESOURCE, OBJECT_TO_TAKE);
    resource_in_pocket = get_resources(&player->inventory, OBJECT_TO_TAKE);
    if (resource_on_land < 0 || resource_in_pocket <= 0)
        return EXIT_WITH_ERROR;
    if (resource_in_pocket > 0) {
        set_resources(&TILE_RESOURCE, OBJECT_TO_TAKE, 1);
        set_resources(&player->inventory, OBJECT_TO_TAKE, -1);
    }
    return EXIT_WITH_SUCCESS;
}
