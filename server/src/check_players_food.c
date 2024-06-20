/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** check_player_food
*/

#include "command_ia.h"
#include "command_gui.h"

static void kill_player(server_t *server, zappy_t *zappy,
    const arguments_t arg, player_t *player)
{
    client_t *client = NULL;
    link_t *link = NULL;

    link = get_link_by_player_id(zappy, player->id);
    if (link == NULL)
        return;
    dprintf(link->client_fd, "dead\n");
    initialize_egg(arg, zappy, player->team_name);
    pdi_func(server, zappy, link->client_fd);
    client = get_client_in_struct(server, link->client_fd);
    client->has_been_closed = true;
    close_client_socket(server, zappy, client);
}

static void check_player_food(server_t *server, zappy_t *zappy,
    const arguments_t arg, player_t *player)
{
    double food_time_unit = calculate_freq(arg.freq, FOOD_TIME_UNIT);

    if (time_is_up(player->clock_begin, food_time_unit)) {
        if (player->inventory.food == 0 && !arg.immortal) {
            kill_player(server, zappy, arg, player);
            return;
        }
        if (player->inventory.food > 0 && !arg.immortal) {
            player->inventory.food--;
            pin(server, zappy, player->id);
        }
        player->clock_begin = clock();
    }
}

void check_players_food(server_t *server, zappy_t *zappy,
    const arguments_t arg)
{
    player_t *player = NULL;
    player_t *player_next = NULL;

    if (TAILQ_EMPTY(&zappy->player_head))
        return;
    player = TAILQ_FIRST(&zappy->player_head);
    while (player != NULL) {
        player_next = TAILQ_NEXT(player, player_entries);
        check_player_food(server, zappy, arg, player);
        player = player_next;
    }
}
