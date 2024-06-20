/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "command_ia.h"
#include "command_gui.h"

static void get_north_south_diag(int i, size_t *dir_diag)
{
    if (*dir_diag == WEST_TILE)
        *dir_diag += 1;
    else {
        *dir_diag -= 1;
        if (*dir_diag == 0)
            *dir_diag = 8;
    }
}

static void decrement_diag(int i, size_t *dir_diag)
{
    if (*dir_diag == WEST_TILE) {
        *dir_diag -= 1;
        if (*dir_diag == 0)
            *dir_diag = 8;
    } else
        *dir_diag += 1;
}

static void get_orientation_diag(road_broadcast_t *road, int i,
    size_t *dir_diag)
{
    if (abs(road->width_direct) > abs(road->width_undirect))
        indirect_west_east(road, i, dir_diag);
    else
        direct_west_east(road, i, dir_diag);
    if (abs(road->height_direct) > abs(road->height_undirect)) {
        if (road->height_undirect > 0)
            get_north_south_diag(i, dir_diag);
        if (road->height_undirect < 0)
            decrement_diag(i, dir_diag);
    } else {
        if (road->height_direct > 0)
            decrement_diag(i, dir_diag);
        if (road->height_direct < 0)
            get_north_south_diag(i, dir_diag);
    }
}

static void get_diagonal_line(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (abs(road->height_direct) != 0 && abs(road->width_direct) != 0)
        get_orientation_diag(road, i, dir_diag);
}

static void find_shortest_path(server_t *server, zappy_t *zappy,
    player_t *receiver, road_broadcast_t *road)
{
    size_t dir_diag = 0;
    int fd_player = get_client_fd(zappy, receiver->id);

    if (fd_player == ERROR_RETURN)
        return;
    for (int i = 0; i < NB_DIRECTIONS; i++) {
        if (DIRECTION_TILE.direction == receiver->direction) {
            get_straight_line(road, i, &dir_diag);
            get_diagonal_line(road, i, &dir_diag);
            dprintf(fd_player, "message %ld, %s\n", dir_diag,
                server->cmd_arg_array[1]);
        }
    }
}

int broadcast(server_t *server, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    player_t *sender = get_player_by_fd(zappy, client->client_fd);
    player_t *receiver = NULL;
    road_broadcast_t *road = malloc(sizeof(road_broadcast_t));

    pbc_func(server, sender->id, server->cmd_arg_array[1]);
    TAILQ_FOREACH(receiver, &zappy->player_head, player_entries) {
        if (receiver->id != sender->id) {
            fill_road_broadcast(sender, receiver, *arg, road);
            find_shortest_path(server, zappy, receiver, road);
        }
    }
    free(road);
    return EXIT_WITH_SUCCESS;
}
