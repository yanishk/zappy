/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** move_player
*/

#include "command_ia.h"

static void go_north(player_t *player, const arguments_t arg)
{
    if (player->height == 0)
        player->height = arg.height - 1;
    else
        player->height--;
}

static void go_east(player_t *player, const arguments_t arg)
{
    if (player->width == arg.width - 1)
        player->width = 0;
    else
        player->width++;
}

static void go_south(player_t *player, const arguments_t arg)
{
    if (player->height == arg.height - 1)
        player->height = 0;
    else
        player->height++;
}

static void go_west(player_t *player, const arguments_t arg)
{
    if (player->width == 0)
        player->width = arg.width - 1;
    else
        player->width--;
}

void move_player(size_t direction, player_t *player, const arguments_t arg)
{
    switch (direction) {
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
}
