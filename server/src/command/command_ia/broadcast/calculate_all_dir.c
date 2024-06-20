/*
** EPITECH PROJECT, 2024
** zppy_mmry_leak
** File description:
** calculate_all_dir
*/

#include "command_ia.h"

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

void fill_road_broadcast(player_t *sender, player_t *receiver,
    const arguments_t arg, road_broadcast_t *road)
{
    road->width_direct = width_direct_func(receiver->width, sender->width);
    road->height_direct = height_direct_func(receiver->height, sender->height);
    road->width_undirect = width_undirect_func(receiver->width, sender->width,
        arg.width);
    road->height_undirect = height_undirect_func(receiver->height,
        sender->height, arg.height);
}
