/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "command_ia.h"

static tile_numbering_t const tile_numbering_list[NB_DIRECTIONS] = {
    {NORTH, 1, 2, 3, 4, 5, 6, 7, 8},
    {WEST, 7, 8, 1, 2, 3, 4, 5, 6},
    {SOUTH, 5, 6, 7, 8, 1, 2, 3, 4},
    {EAST, 3, 4, 5, 6, 7, 8, 1, 2}
};

static int width_direct_func(size_t receiver_width, size_t sender_width)
{
    return receiver_width - sender_width;
}

static int height_direct_func(size_t receiver_height, size_t sender_height)
{
    return receiver_height - sender_height;
}

static int width_undirect_func(size_t receiver_width, size_t sender_width,
    size_t map_width)
{
    if (receiver_width < sender_width) {
        return (map_width - sender_width) + receiver_width;
    }
    return (map_width - receiver_width) + sender_width;
}

static int height_undirect_func(size_t receiver_height, size_t sender_height,
    size_t map_height)
{
    if (receiver_height < sender_height)
        return (map_height - sender_height) + receiver_height;
    return (map_height - receiver_height) + sender_height;
}

static void fill_road_broadcast(player_t *sender, player_t *receiver,
    const arguments_t arg, road_broadcast_t *road)
{
    road->width_direct = width_direct_func(receiver->width, sender->width);
    road->height_direct = height_direct_func(receiver->height, sender->height);
    road->width_undirect = width_undirect_func(receiver->width, sender->width,
        arg.width);
    road->height_undirect = height_undirect_func(receiver->height,
        sender->height, arg.height);
}

static void get_straight_line(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (road->height_direct == 0 && road->width_direct != 0) {
        if (road->width_direct > road->width_undirect)
            *dir_diag = tile_numbering_list[i].east_tile;
        else
            *dir_diag = tile_numbering_list[i].west_tile;
    }
    if (road->width_direct == 0 && road->height_direct != 0) {
        if (road->height_direct > road->height_undirect)
            *dir_diag = tile_numbering_list[i].south_tile;
        else
            *dir_diag = tile_numbering_list[i].north_tile;
    }
}

static void get_diagonal_line(road_broadcast_t *road, int i, size_t *dir_diag)
{
    if (road->height_direct != 0 && road->height_direct != 0) {
        if (road->width_direct > road->width_undirect)
            *dir_diag = tile_numbering_list[i].east_tile;
        else
            *dir_diag = tile_numbering_list[i].west_tile;
        if (road->height_direct > road->height_undirect)
            *dir_diag -= 1;
        else
            *dir_diag += 1;
    }
}

static void find_shortest_path(server_t *server, zappy_t *zappy,
    player_t *receiver, road_broadcast_t *road)
{
    size_t dir_diag = 0;
    int fd_player = get_client_fd(zappy, receiver->id);

    if (fd_player == ERROR_RETURN)
        return;
    for (int i = 0; i < NB_DIRECTIONS; i++) {
        if (tile_numbering_list[i].direction == receiver->direction) {
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

    TAILQ_FOREACH(receiver, &zappy->player_head, player_entries) {
        if (receiver->id != sender->id) {
            fill_road_broadcast(sender, receiver, *arg, road);
            find_shortest_path(server, zappy, receiver, road);
        }
    }
    free(road);
    return EXIT_WITH_SUCCESS;
}
