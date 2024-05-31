/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** take_command
*/

#include "server.h"

static bool take_food(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("food", server->cmd_arg.tab[1]) == 0
        && zappy->resource[player->width][player->height].food > 0) {
            zappy->resource[player->width][player->height].food -= 1;
            player->inventory.food += 1;
            was_taken = true;
    }
    return was_taken;
}

static bool take_linemate(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("linemate", server->cmd_arg.tab[1]) == 0
        && zappy->resource[player->width][player->height].linemate > 0) {
            zappy->resource[player->width][player->height].linemate -= 1;
            player->inventory.linemate += 1;
            was_taken = true;
    }
    return was_taken;
}

static bool take_deraumere(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("deraumere", server->cmd_arg.tab[1]) == 0
        && zappy->resource[player->width][player->height].deraumere > 0) {
            zappy->resource[player->width][player->height].deraumere -= 1;
            player->inventory.deraumere += 1;
            was_taken = true;
    }
    return was_taken;
}

static bool take_sibur(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("sibur", server->cmd_arg.tab[1]) == 0
    && zappy->resource[player->width][player->height].sibur > 0) {
        zappy->resource[player->width][player->height].sibur -= 1;
        player->inventory.sibur += 1;
        was_taken = true;
    }
    return was_taken;
}

static bool take_mendiane(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("mendiane", server->cmd_arg.tab[1]) == 0
    && zappy->resource[player->width][player->height].mendiane > 0) {
        zappy->resource[player->width][player->height].mendiane -= 1;
        player->inventory.mendiane += 1;
        was_taken = true;
    }
    return was_taken;
}

static bool take_phiras(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("phiras", server->cmd_arg.tab[1]) == 0
    && zappy->resource[player->width][player->height].phiras > 0) {
        zappy->resource[player->width][player->height].phiras -= 1;
        player->inventory.phiras += 1;
        was_taken = true;
    }
    return was_taken;
}

static bool take_thystame(server_t *server, zappy_t *zappy, player_t *player,
    bool was_taken)
{
    if (strcmp("thystame", server->cmd_arg.tab[1]) == 0
    && zappy->resource[player->width][player->height].thystame > 0) {
        zappy->resource[player->width][player->height].thystame -= 1;
        player->inventory.thystame += 1;
        was_taken = true;
    }
    return was_taken;
}

int take_command(server_t *server, zappy_t *zappy, const arguments_t,
    const unsigned int client_fd)
{
    player_t *player = get_player(zappy, client_fd);
    bool was_taken = false;

    if (player == NULL || server->cmd_arg.tab[1] == NULL)
        return EXIT_WITH_ERROR;
    was_taken = take_food(server, zappy, player, was_taken);
    was_taken = take_linemate(server, zappy, player, was_taken);
    was_taken = take_deraumere(server, zappy, player, was_taken);
    was_taken = take_sibur(server, zappy, player, was_taken);
    was_taken = take_mendiane(server, zappy, player, was_taken);
    was_taken = take_phiras(server, zappy, player, was_taken);
    was_taken = take_thystame(server, zappy, player, was_taken);
    if (was_taken == false)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
