/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** take_food
*/

#include "command.h"

bool take_food(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp(FOOD, server->cmd_arg_array[1]) == 0
        && zappy->resource[player->height][player->width].food > 0) {
            zappy->resource[player->height][player->width].food -= 1;
            player->inventory.food += 1;
            was_taken = true;
    }
    return was_taken;
}
