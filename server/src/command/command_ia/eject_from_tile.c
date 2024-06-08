/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject_from_tile
*/

#include "command_ia.h"

static tile_numbering_t const tile_numbering_list[NB_DIRECTIONS] = {
    {NORTH, 1, 3, 5, 7},
    {WEST, 7, 1, 3, 5},
    {SOUTH, 5, 7, 1, 3},
    {EAST, 3, 5, 7, 1},
};

static size_t get_previous_tile(const tile_numbering_t tile_numbering,
    const size_t orientation)
{
    switch (orientation) {
        case NORTH:
            return tile_numbering.south_tile;
        case WEST:
            return tile_numbering.east_tile;
        case SOUTH:
            return tile_numbering.north_tile;
        case EAST:
            return tile_numbering.west_tile;
    }
    return ERROR_RETURN;
}

static void eject_player(const player_t *current_player, player_t *player,
    const arguments_t arg)
{
    unsigned int ejected_client_fd = player->id;
    size_t previous_tile = 0;

    move_player(current_player->direction, player, arg);
    for (int i = 0; i < NB_DIRECTIONS; i++) {
        if (tile_numbering_list[i].direction == player->direction) {
            previous_tile = get_previous_tile(tile_numbering_list[i],
                current_player->direction);
            dprintf(ejected_client_fd, "eject: %ld\n", previous_tile);
        }
    }
}

int eject_from_tile(server_t *, zappy_t *zappy, const arguments_t arg,
    client_t *client)
{
    int status = EXIT_WITH_ERROR;
    player_t *current_player = get_player(zappy, client->client_fd);
    player_t *player = NULL;

    if (current_player == NULL)
        return status;
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (is_on_same_tile(player, current_player)) {
            if (player->status == IS_EGG_FROM_FORK) {
                TAILQ_REMOVE(&zappy->player_head, player, player_entries);
            } else if (player->status == IS_EGG_FROM_START) {
                initialize_player_pos(arg, zappy, player);
            } else {
                eject_player(current_player, player, arg);
                status = EXIT_WITH_SUCCESS;
            }
        }
    }
    return status;
}
