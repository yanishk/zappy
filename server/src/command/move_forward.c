/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** move_forward
*/

#include "server.h"
#include "map.h"

static void go_north(player_t *player, const arguments_t arg)
{
    if (player->height == 0)
        player->height = arg.height;
    else
        player->height--;
}

static void go_east(player_t *player, const arguments_t arg)
{
    if (player->width == arg.width)
        player->width = 0;
    else
        player->width++;
}

static void go_south(player_t *player, const arguments_t arg)
{
    if (player->height == arg.height)
        player->height = 0;
    else
        player->height++;
}

static void go_west(player_t *player, const arguments_t arg)
{
    if (player->width == 0)
        player->width = arg.width;
    else
        player->width--;
}

int move_forward(server_t *, zappy_t *zappy,
    const arguments_t arg, client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    switch (player->direction) {
        case NORTH:
            go_north(player, arg);
            break;
        case EAST:
            go_east(player, arg);
            break;
        case SOUTH:
            go_south(player, arg);
            break;
        case WEST:
            go_west(player, arg);
            break;
    }
    return EXIT_WITH_SUCCESS;
}
