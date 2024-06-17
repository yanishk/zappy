/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set_object
*/

#include "command_ia.h"
#include "command_gui.h"

int set_object(server_t *server, zappy_t *zappy, arguments_t *,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    int resource_in_pocket = 0;

    if (player == NULL || OBJECT_TO_TAKE == NULL)
        return EXIT_WITH_ERROR;
    resource_in_pocket = get_resources(&player->inventory, OBJECT_TO_TAKE);
    if (resource_in_pocket <= 0)
        return EXIT_WITH_ERROR;
    if (resource_in_pocket > 0) {
        set_resources(&TILE_RESOURCE, OBJECT_TO_TAKE, 1);
        set_resources(&player->inventory, OBJECT_TO_TAKE, -1);
        pdr_func(server, zappy, client, OBJECT_TO_TAKE);
        bct(server, zappy, player->width, player->height);
        pin(server, zappy, player->id);
    }
    return EXIT_WITH_SUCCESS;
}
