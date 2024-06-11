/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** check_player_food
*/

#include "server.h"

static void check_player_food(server_t *server, zappy_t *zappy,
    const arguments_t arg, player_t *player)
{
    double food_time_unit = calculate_freq(arg.freq, FOOD_TIME_UNIT);
    client_t *client = NULL;

    if (player->status != IS_PLAYER)
        return;
    if (time_is_up(player->clock_begin, food_time_unit)) {
        if (player->inventory.food == 0) {
            dprintf(player->id, "dead\n");
            client = get_client_in_struct(server, player->id);
            client->has_been_closed = true;
            close_client_socket(server, zappy, client);
            initialize_player(arg, zappy, player->team_name,
                IS_EGG_FROM_START);
            return;
        }
        if (player->inventory.food > 0)
            player->inventory.food--;
        player->clock_begin = clock();
    }
}

void check_players_food(server_t *server, zappy_t *zappy,
    const arguments_t arg)
{
    player_t *player = NULL;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        check_player_food(server, zappy, arg, player);
    }
}
