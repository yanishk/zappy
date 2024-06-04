/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** set_food
*/

#include "server.h"

bool set_food(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("food", server->cmd_arg_array[1]) == 0
        && player->inventory.food > 0) {
            player->inventory.food -= 1;
            zappy->resource[player->height][player->width].food += 1;
            was_set = true;
    }
    return was_set;
}
