/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set_object
*/

#include "server.h"

static bool set_food(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("food", server->cmd_arg_array[1]) == 0
        && player->inventory.food > 0) {
            player->inventory.food -= 1;
            zappy->resource[player->width][player->height].food += 1;
            was_set = true;
    }
    return was_set;
}

static bool set_linemate(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("linemate", server->cmd_arg_array[1]) == 0
        && player->inventory.linemate > 0) {
            player->inventory.linemate -= 1;
            zappy->resource[player->width][player->height].linemate += 1;
            was_set = true;
    }
    return was_set;
}

static bool set_deraumere(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("deraumere", server->cmd_arg_array[1]) == 0
        && player->inventory.deraumere > 0) {
            player->inventory.deraumere -= 1;
            zappy->resource[player->width][player->height].deraumere += 1;
            was_set = true;
    }
    return was_set;
}

static bool set_sibur(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("sibur", server->cmd_arg_array[1]) == 0
    && player->inventory.sibur > 0) {
        player->inventory.sibur -= 1;
        zappy->resource[player->width][player->height].sibur += 1;
        was_set = true;
    }
    return was_set;
}

static bool set_mendiane(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("mendiane", server->cmd_arg_array[1]) == 0
    && player->inventory.mendiane > 0) {
        player->inventory.mendiane -= 1;
        zappy->resource[player->width][player->height].mendiane += 1;
        was_set = true;
    }
    return was_set;
}

static bool set_phiras(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("phiras", server->cmd_arg_array[1]) == 0
    && player->inventory.phiras > 0) {
        player->inventory.phiras -= 1;
        zappy->resource[player->width][player->height].phiras += 1;
        was_set = true;
    }
    return was_set;
}

static bool set_thystame(server_t *server, zappy_t *zappy, player_t *player,
    bool was_set)
{
    if (strcmp("thystame", server->cmd_arg_array[1]) == 0
    && player->inventory.thystame > 0) {
        player->inventory.thystame -= 1;
        zappy->resource[player->width][player->height].thystame += 1;
        was_set = true;
    }
    return was_set;
}

int set_object(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);
    bool was_set = false;

    if (player == NULL || server->cmd_arg_array[1] == NULL)
        return EXIT_WITH_ERROR;
    was_set = set_food(server, zappy, player, was_set);
    was_set = set_linemate(server, zappy, player, was_set);
    was_set = set_deraumere(server, zappy, player, was_set);
    was_set = set_sibur(server, zappy, player, was_set);
    was_set = set_mendiane(server, zappy, player, was_set);
    was_set = set_phiras(server, zappy, player, was_set);
    was_set = set_thystame(server, zappy, player, was_set);
    if (was_set == false)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
