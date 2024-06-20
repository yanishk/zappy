/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "command_ia.h"
#include "command_gui.h"

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
    return (map_width - receiver_width) + sender_width;
}

static int height_undirect_func(size_t receiver_height, size_t sender_height,
    size_t map_height)
{
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
        if (abs(road->width_direct) > abs(road->width_undirect)) {
            printf("STRAIGHT EAST [diag: %ld]", *dir_diag);
            *dir_diag = tile_numbering_list[i].east_tile;
        } else {
            printf("STRAIGHT WEST [diag: %ld]", *dir_diag);
            *dir_diag = tile_numbering_list[i].west_tile;
        }
    }
    if (road->width_direct == 0 && road->height_direct != 0) {
        if (abs(road->height_direct) > abs(road->height_undirect)) {
            printf("STRAIGHT SOUTH [diag: %ld]", *dir_diag);
            *dir_diag = tile_numbering_list[i].south_tile;
        } else {
            printf("STRAIGHT NORTH [diag: %ld]", *dir_diag);
            *dir_diag = tile_numbering_list[i].north_tile;
        }
    }
}

static void get_diagonal_line(road_broadcast_t *road, int i, size_t *dir_diag)
{
    unsigned int width_direct = abs(road->width_direct);
    unsigned int width_undirect = abs(road->width_undirect);
    unsigned int height_direct = abs(road->height_direct);
    unsigned int height_undirect = abs(road->height_undirect);

    if (height_direct != 0 && width_direct != 0) {
        printf("DIAG:\n");
        if (width_direct > width_undirect) {
            if (road->width_undirect > 0) {
                printf("\tINDIRECT EAST [diag: %ld]", *dir_diag);
                *dir_diag = tile_numbering_list[i].east_tile;
            }
            if (road->width_undirect < 0) {
                printf("\tINDIRECT WEST [diag: %ld]", *dir_diag);
                *dir_diag = tile_numbering_list[i].west_tile;
            }
        } else {
            if (road->width_direct > 0) {
                printf("\tDIRECT WEST [diag: %ld]", *dir_diag);
                *dir_diag = tile_numbering_list[i].west_tile;
            }
            if (road->width_direct < 0) {
                printf("\tDIRECT EAST [diag: %ld]", *dir_diag);
                *dir_diag = tile_numbering_list[i].east_tile;
            }
        }
        if (height_direct > height_undirect) {
            if (road->height_undirect > 0) {
                if (*dir_diag == tile_numbering_list[i].west_tile) {
                    printf("INDIRECT SUD 1 [diag: %ld]\n", *dir_diag);
                    *dir_diag += 1;
                } else {
                    printf("INDIRECT SUD 2 [diag: %ld]\n", *dir_diag);
                    *dir_diag -= 1;
                }
            }
            if (road->height_undirect < 0) {
                if (*dir_diag == tile_numbering_list[i].west_tile) {
                    printf("INDIRECT NORTH 1 [diag: %ld]\n", *dir_diag);
                    *dir_diag -= 1;
                } else {
                    printf("INDIRECT NORTH 2 [diag: %ld]\n", *dir_diag);
                    *dir_diag += 1;
                }
            }
        } else {
            if (road->height_direct > 0) {
                if (*dir_diag == tile_numbering_list[i].west_tile) {
                    printf("INDIRECT NORTH 3 [diag: %ld]\n", *dir_diag);
                    *dir_diag -= 1;
                } else {
                    printf("INDIRECT NORTH 4 [diag: %ld]\n", *dir_diag);
                    *dir_diag += 1;
                }
            }
            if (road->height_direct < 0) {
                if (*dir_diag == tile_numbering_list[i].west_tile) {
                    printf("INDIRECT SUD 3 [diag: %ld]\n", *dir_diag);
                    *dir_diag += 1;
                } else {
                    printf("INDIRECT SUD 4 [diag: %ld]\n", *dir_diag);
                    *dir_diag -= 1;
                }
            }
        }
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
