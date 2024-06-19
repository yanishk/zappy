/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_on_ground
*/

#include "command_ia.h"

static char *get_resources_tile(int resource_decount,
    const char *name, char *string_on_land)
{
    int len = 0;

    while (resource_decount > 0) {
        if (string_on_land != NULL)
            len = strlen(string_on_land);
        string_on_land = realloc(string_on_land, sizeof(char) *
            (len + strlen(" ") + strlen(name) + 1));
        if (len == 0)
            memset(string_on_land, '\0', strlen(" ") + strlen(name));
        else
            string_on_land[strlen(string_on_land)] = '\0';
        strcat(string_on_land, " ");
        strcat(string_on_land, name);
        resource_decount--;
    }
    return string_on_land;
}

static char *find_player_tile(zappy_t *zappy, coordinate_t pos,
    const unsigned int client_fd)
{
    player_t *current_player = get_player_by_fd(zappy, client_fd);
    player_t *player = NULL;
    char *player_string = " player";
    char *string_on_land = NULL;

    if (current_player != NULL)
        return NULL;
    for ((player) = ((&zappy->player_head)->tqh_first); (player);
        (player) = ((player)->player_entries.tqe_next)) {
        if (player->height == pos.height && player->width == pos.width
            && player->id != current_player->id) {
            string_on_land = realloc(string_on_land, sizeof(char) *
                (strlen(string_on_land) + strlen(player_string)) + 1);
            strcat(string_on_land, player_string);
        }
    }
    return string_on_land;
}

char *get_on_land(zappy_t *zappy, coordinate_t pos,
    unsigned int client_fd)
{
    int resource_decount = 0;
    char *string_on_land = find_player_tile(zappy, pos, client_fd);
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    for (size_t i = 0; i < NB_RESOURCES; i++) {
        resource_decount =
            get_resources(&zappy->resource[pos.height][pos.width],
            resource_list[i]);
        string_on_land = get_resources_tile(resource_decount,
            resource_list[i], string_on_land);
    }
    if (string_on_land == NULL) {
        string_on_land = malloc(sizeof(char) * strlen("\0") + 1);
        *string_on_land = '\0';
    }
    return string_on_land;
}
