/*
** EPITECH PROJECT, 2024
** zappy_command_gui_dos
** File description:
** pnw
*/

#include "server.h"
#include "command_gui.h"

struct direction_player direction[] = {
    {NORTH, 1},
    {EAST, 2},
    {SOUTH, 3},
    {WEST, 4}
};

int pnw_func(server_t *, zappy_t *zappy, const arguments_t, client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);

    for (size_t index = 0; index < NB_DIR; index++) {
        if (direction[index].angle == player->direction) {
            dprintf(client->client_fd, "pnw %d %d %d %d %d %s\n", player->id,
            player->width, player->height, direction[index].direction,
            player->level, player->team_name);
        }
    }
    return EXIT_WITH_SUCCESS;
}
