/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include "server.h"

char *get_on_land(zappy_t *zappy, int pos_height, int pos_width, const unsigned int client_fd)
{
    int ressource_decount = 0;
    char *string_on_land = malloc(1);
    char *new_string = NULL;
    player_t *player = get_player(zappy, client_fd);

    string_on_land[0] = '\0';
    TAILQ_FOREACH(player, &zappy->player_head, player_entries) {
        if (player->height == pos_height && player->width == pos_width && player->id != client_fd) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" food"));
            string_on_land = new_string;
            strcat(string_on_land, " player");
        }
    }

    if (zappy->resource[pos_height][pos_width].food > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].food;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" food"));
            string_on_land = new_string;
            strcat(string_on_land, " food");
            ressource_decount--;
        }
    }
    if (zappy->resource[pos_height][pos_width].linemate > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].linemate;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" linemate"));
            string_on_land = new_string;
            strcat(string_on_land, " linemate");
            ressource_decount--;
        }
    }
    if (zappy->resource[pos_height][pos_width].deraumere > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].deraumere;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" deraumere"));
            string_on_land = new_string;
            strcat(string_on_land, " deraumere");
            ressource_decount--;
        }
    }
    if (zappy->resource[pos_height][pos_width].sibur > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].sibur;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" sibur"));
            string_on_land = new_string;
            strcat(string_on_land, " sibur");
            ressource_decount--;
        }
    }
    if (zappy->resource[pos_height][pos_width].mendiane > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].mendiane;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" mendiane"));
            string_on_land = new_string;
            strcat(string_on_land, " mendiane");
            ressource_decount--;
        }
    }
    if (zappy->resource[pos_height][pos_width].phiras > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].phiras;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" phiras"));
            string_on_land = new_string;
            strcat(string_on_land, " phiras");
            ressource_decount--;
        }
    }
    if (zappy->resource[pos_height][pos_width].thystame > 0) {
        ressource_decount = zappy->resource[pos_height][pos_width].thystame;
        while (ressource_decount != 0) {
            new_string = realloc(string_on_land, strlen(string_on_land) + sizeof(" thystame"));
            string_on_land = new_string;
            strcat(string_on_land, " thystame");
            ressource_decount--;
        }
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
