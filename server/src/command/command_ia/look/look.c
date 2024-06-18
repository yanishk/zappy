/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include "command_ia.h"

static int check_heigth_ns(const arguments_t arg, player_t *player,
    size_t direction, int vision_x)
{
    int vision_x_final = 0;

    if (direction == NORTH) {
        if (player->height - vision_x < 0)
            vision_x_final = arg.height + (player->height - vision_x);
        else
            vision_x_final = player->height - vision_x;
    }
    if (direction == SOUTH) {
        if (player->height + vision_x > arg.height - 1)
            vision_x_final = (player->height + vision_x) - arg.height;
        else
            vision_x_final = player->height + vision_x;
    }
    return vision_x_final;
}

static int check_height_we(const arguments_t arg, player_t *player,
    int vision_x)
{
    int vision_x_final = 0;

    if (player->height + vision_x < 0)
        vision_x_final = arg.height + (player->height + vision_x);
    else if (player->height + vision_x > arg.height - 1)
        vision_x_final = (player->height + vision_x) - arg.height;
    else
        vision_x_final = player->height + vision_x;
    return vision_x_final;
}

static int check_width_ns(const arguments_t arg, player_t *player,
    int vision_y)
{
    int vision_y_final = 0;

    if (player->width + vision_y < 0)
        vision_y_final = arg.width + (player->width + vision_y);
    else if (player->width + vision_y > arg.width - 1)
        vision_y_final = (player->width + vision_y) - arg.width;
    else
        vision_y_final = player->width + vision_y;
    return vision_y_final;
}

static int check_width_we(const arguments_t arg, player_t *player,
    size_t direction, int vision_y)
{
    int vision_y_final = 0;

    if (direction == EAST) {
        if (player->width + vision_y > arg.width - 1)
            vision_y_final = (player->width + vision_y) - arg.width;
        else
            vision_y_final = player->width + vision_y;
    }
    if (direction == WEST) {
        if (player->width - vision_y < 0)
            vision_y_final = arg.width + (player->width - vision_y);
        else
            vision_y_final = player->width - vision_y;
    }
    return vision_y_final;
}

static void print_comma(int vision_y, player_t *player,
    client_t *client)
{
    if (vision_y != player->level)
        dprintf(client->client_fd, ",");
}

static void north_south_look(zappy_t *zappy, const arguments_t arg,
    player_t *player, client_t *client)
{
    coordinate_t pos = {player->height, player->width};
    size_t direction = player->direction;
    int vision_x_final = 0;
    int vision_y_final = 0;
    char *string_on_land = NULL;

    for (int vision_x = 1; vision_x <= player->level; vision_x++) {
        vision_x_final = check_heigth_ns(arg, player, direction, vision_x);
        for (int vision_y = -vision_x; vision_y <= vision_x; vision_y++) {
            vision_y_final = check_width_ns(arg, player, vision_y);
            pos.height = vision_x_final;
            pos.width = vision_y_final;
            string_on_land = get_on_land(zappy, pos, client->client_fd);
            dprintf(client->client_fd, "%s", string_on_land);
            print_comma(vision_y, player, client);
            free(string_on_land);
        }
    }
}

static void west_east_look(zappy_t *zappy, const arguments_t arg,
    player_t *player, client_t *client)
{
    coordinate_t pos = {player->height, player->width};
    size_t direction = player->direction;
    int vision_x_final = 0;
    int vision_y_final = 0;
    char *string_on_land = NULL;

    for (int vision_y = 1; vision_y <= player->level; vision_y++) {
        vision_y_final = check_width_we(arg, player, direction, vision_y);
        for (int vision_x = -vision_y; vision_x <= vision_y; vision_x++) {
            vision_x_final = check_height_we(arg, player, vision_x);
            pos.height = vision_x_final;
            pos.width = vision_y_final;
            string_on_land = get_on_land(zappy, pos, client->client_fd);
            dprintf(client->client_fd, "%s", string_on_land);
            print_comma(vision_x, player, client);
            free(string_on_land);
        }
    }
}

int look_around(server_t *, zappy_t *zappy, arguments_t *arg,
    client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    coordinate_t pos;
    size_t direction = 0;
    char *string_on_land = NULL;

    if (player == NULL)
        return EXIT_WITH_ERROR;
    pos.height = player->height;
    pos.width = player->width;
    direction = player->direction;
    string_on_land = get_on_land(zappy, pos, client->client_fd);
    dprintf(client->client_fd, "[player%s,", string_on_land);
    if (direction == NORTH || direction == SOUTH)
        north_south_look(zappy, *arg, player, client);
    if (direction == EAST || direction == WEST)
        west_east_look(zappy, *arg, player, client);
    dprintf(client->client_fd, "]\n");
    if (string_on_land != NULL)
        free(string_on_land);
    return COMMAND_SUCCESS;
}
