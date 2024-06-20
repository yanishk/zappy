/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject_from_tile
*/

#include "command_ia.h"
#include "command_gui.h"

tile_numbering_t const tile_numbering_list[NB_DIRECTIONS] = {
    {NORTH, 1, 2, 3, 4, 5, 6, 7, 8},
    {WEST, 7, 8, 1, 2, 3, 4, 5, 6},
    {SOUTH, 5, 6, 7, 8, 1, 2, 3, 4},
    {EAST, 3, 4, 5, 6, 7, 8, 1, 2}
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

static void eject_player(const zappy_t *zappy, const player_t *current_player,
    player_t *player, const arguments_t arg)
{
    unsigned int ejected_client_fd = get_client_fd(zappy, player->id);
    size_t previous_tile = 0;

    move_player(current_player->direction, player, arg);
    for (int i = 0; i < NB_DIRECTIONS; i++) {
        if (DIRECTION_TILE.direction == player->direction) {
            previous_tile = get_previous_tile(DIRECTION_TILE,
                current_player->direction);
            dprintf(ejected_client_fd, "eject: %ld\n", previous_tile);
        }
    }
}

static int eject_players(server_t *server, zappy_t *zappy, arguments_t *arg,
    player_t *current_player)
{
    int status = EXIT_WITH_ERROR;
    player_t *player = NULL;

    if (current_player == NULL)
        return status;
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player_on_same_tile(current_player, player)) {
            eject_player(zappy, current_player, player, *arg);
            ppo(server, zappy, player->id);
            status = EXIT_WITH_SUCCESS;
        }
    }
    return status;
}

static void kill_eggs(server_t *server, zappy_t *zappy,
    player_t *current_player)
{
    egg_t *egg = NULL;
    egg_t *egg_next = NULL;

    if (TAILQ_EMPTY(&zappy->egg_head))
        return;
    egg = TAILQ_FIRST(&zappy->egg_head);
    while (egg != NULL) {
        egg_next = TAILQ_NEXT(egg, egg_entries);
        if (egg_on_same_tile(current_player, egg)) {
            edi_func(server, egg->id);
            free_egg(zappy, egg);
        }
        egg = egg_next;
    }
}

int eject_from_tile(server_t *server, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    player_t *current_player = get_player_by_fd(zappy, client->client_fd);
    int status = EXIT_WITH_ERROR;

    if (current_player == NULL)
        return EXIT_WITH_ERROR;
    pex_func(server, current_player);
    status = eject_players(server, zappy, arg, current_player);
    kill_eggs(server, zappy, current_player);
    return status;
}
