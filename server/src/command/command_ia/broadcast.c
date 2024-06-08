/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast
*/

#include "server.h"

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

static int width_undirect_func(size_t receiver_width, size_t sender_width, size_t map_width)
{
    if (receiver_width < sender_width) {
        return (map_width - sender_width) + receiver_width;
    }
    return (map_width - receiver_width) + sender_width;
}

static int height_undirect_func(size_t receiver_height, size_t sender_height, size_t map_height)
{
    if (receiver_height < sender_height)
        return (map_height - sender_height) + receiver_height;
    return (map_height - receiver_height) + sender_height;
}

int broadcast(server_t *server, zappy_t *zappy, const arguments_t arg, client_t *client)
{
    player_t *sender = get_player(zappy, client->client_fd);
    player_t *receiver = NULL;
    int width_direct = 0;
    int height_direct = 0;
    int width_undirect = 0;
    int height_undirect = 0;
    size_t dir_diag = 0;

    printf("Sender[%d][%d]\n", sender->height, sender->width);
    TAILQ_FOREACH(receiver, &zappy->player_head, player_entries) {
        if (receiver->id != sender->id) {
            printf("Receiver[%d][%d], Dir = %ld\n", receiver->height, receiver->width, receiver->direction);
            width_direct = width_direct_func(receiver->width, sender->width);
            height_direct = height_direct_func(receiver->height, sender->height);
            width_undirect = width_undirect_func(receiver->width, sender->width, arg.width);
            height_undirect = height_undirect_func(receiver->height, sender->height, arg.height); //mettre dans une struct

            for (int i = 0; i < NB_DIRECTIONS; i++) {
                if (tile_numbering_list[i].direction == receiver->direction) {
                    if (height_direct == 0 && width_direct == 0)
                        dir_diag = 0;
                    if (height_direct == 0 && width_direct != 0) {
                        if (width_direct > width_undirect)
                            dir_diag = tile_numbering_list[i].east_tile;
                        else
                            dir_diag = tile_numbering_list[i].west_tile;
                    }
                    if (width_direct == 0 && height_direct != 0) {
                        if (height_direct > height_undirect)
                            dir_diag = tile_numbering_list[i].south_tile;
                        else
                            dir_diag = tile_numbering_list[i].north_tile;
                    }
                    if (height_direct != 0 && height_direct != 0) {
                        if (width_direct > width_undirect)
                            dir_diag = tile_numbering_list[i].east_tile;
                        else
                            dir_diag = tile_numbering_list[i].west_tile;
                        if (height_direct > height_undirect)
                            dir_diag -= 1;
                        else
                            dir_diag += 1;
                    }
                    dprintf(receiver->id, "message %ld, %s\n", dir_diag, server->cmd_arg_array[1]);
                }

            }
        }
    }
    return EXIT_WITH_SUCCESS;
}
