/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include "server.h"
#include "command.h"

static char *get_resources_tile(int resource_decount, char *string_on_land,
    const char *name)
{
    char *new_string = NULL;

    if (resource_decount > 0) {
        while (resource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) +
                sizeof(" ") + sizeof(name));
            string_on_land = new_string;
            strcat(string_on_land, " ");
            strcat(string_on_land, name);
            resource_decount--;
        }
    }
    return string_on_land;
}

static char *find_player_tile(zappy_t *zappy, coordinate_t pos,
    const unsigned int client_fd, char *string_on_land)
{
    player_t *player = get_player(zappy, client_fd);
    char *new_string = NULL;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (player->height == pos.height && player->width == pos.width
            && player->id != client_fd) {
            new_string = realloc(string_on_land,
                strlen(string_on_land) + sizeof(" player"));
            string_on_land = new_string;
            strcat(string_on_land, " player");
        }
    }
    return string_on_land;
}

static char *get_on_land(zappy_t *zappy, coordinate_t pos,
    unsigned int client_fd)
{
    int resource_decount = 0;
    char *string_on_land = malloc(1);
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    string_on_land[0] = '\0';
    string_on_land = find_player_tile(zappy, pos, client_fd, string_on_land);
    for (size_t i = 0; i < NB_RESOURCES; i++) {
        resource_decount =
            get_resources(&zappy->resource[pos.height][pos.width],
            resource_list[i]);
        string_on_land = get_resources_tile(resource_decount,
            string_on_land, resource_list[i]);
    }
    return string_on_land;
}

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

static void north_south_look(zappy_t *zappy, const arguments_t arg,
    player_t *player, client_t *client)
{
    coordinate_t pos = {player->height, player->width};
    size_t direction = player->direction;
    int vision_x_final = 0;
    int vision_y_final = 0;

    for (int vision_x = 1; vision_x != (player->level + 1); vision_x++) {
        vision_x_final = check_heigth_ns(arg, player, direction, vision_x);
        for (int vision_y = -vision_x; vision_y != vision_x + 1; vision_y++) {
            vision_y_final = check_width_ns(arg, player, vision_y);
            pos.height = vision_x_final;
            pos.width = vision_y_final;
            dprintf(client->client_fd, "%s",
                get_on_land(zappy, pos, client->client_fd));
            if (vision_y != vision_x && vision_x == player->level)
                dprintf(client->client_fd, ",");
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

    for (int vision_y = 1; vision_y != (player->level + 1); vision_y++) {
        vision_y_final = check_width_we(arg, player, direction, vision_y);
        for (int vision_x = -vision_y; vision_x != vision_y + 1; vision_x++) {
            vision_x_final = check_height_we(arg, player, vision_x);
            pos.height = vision_x_final;
            pos.width = vision_y_final;
            dprintf(client->client_fd, "%s",
                get_on_land(zappy, pos, client->client_fd));
            if (vision_y != vision_x && vision_y == player->level)
                dprintf(client->client_fd, ",");
        }
    }
}

int look_around(server_t *, zappy_t *zappy, const arguments_t arg,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);
    coordinate_t pos = {player->height, player->width};
    size_t direction = player->direction;

    dprintf(client->client_fd, "[player%s,",
        get_on_land(zappy, pos, client->client_fd));
    if (direction == NORTH || direction == SOUTH)
        north_south_look(zappy, arg, player, client);
    if (direction == EAST || direction == WEST)
        west_east_look(zappy, arg, player, client);
    dprintf(client->client_fd, "]\n");
    return EXIT_WITH_SUCCESS;
}
