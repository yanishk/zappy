/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include "server.h"

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

static char *find_player_tile(zappy_t *zappy, const int pos_height,
    const int pos_width, const unsigned int client_fd, char *string_on_land)
{
    player_t *player = get_player(zappy, client_fd);
    char *new_string = NULL;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (player->height == pos_height && player->width == pos_width
            && player->id != client_fd) {
            new_string = realloc(string_on_land,
                strlen(string_on_land) + sizeof(" player"));
            string_on_land = new_string;
            strcat(string_on_land, " player");
        }
    }
    return string_on_land;
}

char *get_on_land(zappy_t *zappy, const int pos_height,
    const int pos_width, const unsigned int client_fd)
{
    int resource_decount = 0;
    char *string_on_land = malloc(1);
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    string_on_land[0] = '\0';
    string_on_land = find_player_tile(zappy, pos_height, pos_width,
        client_fd, string_on_land);
    for (size_t i = 0; i < NB_RESOURCES; i++) {
        resource_decount =
            get_resources(&zappy->resource[pos_height][pos_width],
            resource_list[i]);
        string_on_land = get_resources_tile(resource_decount,
            string_on_land, resource_list[i]);
    }
    return string_on_land;
}

int look_around(server_t *, zappy_t *zappy, const arguments_t arg,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);
    size_t direction = player->direction;
    int vision_x_final = 0;
    int vision_y_final = 0;

    dprintf(client->client_fd, "[player%s,", get_on_land(zappy, player->height, player->width, client->client_fd));
    if (direction == NORTH) {
        for (int vision_x = 1; vision_x != (player->level + 1); vision_x++) {
            if (player->height - vision_x < 0)
                vision_x_final = arg.height + (player->height - vision_x);
            else
                vision_x_final = player->height - vision_x;
            for (int vision_y = -vision_x; vision_y != vision_x + 1; vision_y++) {
                if (player->width + vision_y < 0)
                    vision_y_final = arg.width + (player->width + vision_y);
                else if (player->width + vision_y > arg.width - 1)
                    vision_y_final = (player->width + vision_y) - arg.width;
                else
                    vision_y_final = player->width + vision_y;
                dprintf(client->client_fd, "%s", get_on_land(zappy, vision_x_final, vision_y_final, client->client_fd));
                if (vision_y != vision_x && vision_x == player->level)
                    dprintf(client->client_fd, ",");
            }
        }

    }

    if (direction == EAST) {
        for (int vision_y = 1; vision_y != (player->level + 1); vision_y++) {
            if (player->width + vision_y > arg.width - 1)
                vision_y_final = (player->width + vision_y) - arg.width;
            else
                vision_y_final = player->width + vision_y;
            for (int vision_x = -vision_y; vision_x != vision_y + 1; vision_x++) {
                if (player->height + vision_x < 0)
                    vision_x_final = arg.height + (player->height + vision_x);
                else if (player->height + vision_x > arg.height - 1)
                    vision_x_final = (player->height + vision_y) - arg.height;
                else
                    vision_x_final = player->height + vision_x;
                dprintf(client->client_fd, "%s", get_on_land(zappy, vision_x_final, vision_y_final, client->client_fd));
                if (vision_y != vision_x && vision_y == player->level)
                    dprintf(client->client_fd, ",");
            }
        }
    }

    if (direction == SOUTH) {
        for (int vision_x = 1; vision_x != (player->level + 1); vision_x++) {
            if (player->height + vision_x > arg.height - 1)
                vision_x_final = (player->height + vision_x) - arg.height;
            else
                vision_x_final = player->height + vision_x;
            for (int vision_y = -vision_x; vision_y != vision_x + 1; vision_y++) {
                if (player->width + vision_y < 0)
                    vision_y_final = arg.width + (player->width + vision_y);
                else if (player->width + vision_y > arg.width - 1)
                    vision_y_final = (player->width + vision_y) - arg.width;
                else
                    vision_y_final = player->width + vision_y;
                dprintf(client->client_fd, "%s", get_on_land(zappy, vision_x_final, vision_y_final, client->client_fd));
                if (vision_y != vision_x && vision_x == player->level)
                    dprintf(client->client_fd, ",");
            }
        }

    }

    if (direction == WEST) {
        for (int vision_y = 1; vision_y != (player->level + 1); vision_y++) {
            if (player->width - vision_y < 0)
                vision_y_final = arg.width + (player->width - vision_y);
            else
                vision_y_final = player->width - vision_y;
            for (int vision_x = -vision_y; vision_x != vision_y + 1; vision_x++) {
                if (player->height + vision_x < 0)
                    vision_x_final = arg.height + (player->height + vision_x);
                else if (player->height + vision_x > arg.height - 1)
                    vision_x_final = (player->height + vision_y) - arg.height;
                else
                    vision_x_final = player->height + vision_x;
                dprintf(client->client_fd, "%s", get_on_land(zappy, vision_x_final, vision_y_final, client->client_fd));
                if (vision_y != vision_x && vision_y == player->level)
                    dprintf(client->client_fd, ",");
            }
        }
    }

    dprintf(client->client_fd, "]\n");
    return EXIT_WITH_SUCCESS;
}
