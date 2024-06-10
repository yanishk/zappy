/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_on_ground
*/

#include "server.h"
#include "command_ia.h"

static char *get_resources_tile(int resource_decount, char *string_on_land,
    const char *name)
{
    char *new_string = NULL;

    while (resource_decount < 0) {
        new_string = realloc(string_on_land, strlen(string_on_land) +
            sizeof(" ") + sizeof(name));
        string_on_land = new_string;
        strcat(string_on_land, " ");
        strcat(string_on_land, name);
        resource_decount--;
    }
    return string_on_land;
}

static char *find_player_tile(zappy_t *zappy, coordinate_t pos,
    const unsigned int client_fd, char *string_on_land)
{
    player_t *current_player = get_player_by_fd(zappy, client_fd);
    player_t *player = NULL;
    char *new_string = NULL;

    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (player->height == pos.height && player->width == pos.width
            && player->id != current_player->id) {
            new_string = realloc(string_on_land,
                strlen(string_on_land) + sizeof(" player"));
            string_on_land = new_string;
            strcat(string_on_land, " player");
        }
    }
    return string_on_land;
}

char *get_on_land(zappy_t *zappy, coordinate_t pos,
    unsigned int client_fd)
{
    int resource_decount = 0;
    char *string_on_land = malloc(sizeof(char));
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
