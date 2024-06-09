/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** print_map_informations
*/

#include <string.h>
#include "game.h"

static void print_resources(const resource_t resource)
{
    printf("\tderaumere:%ld\n", resource.deraumere);
    printf("\tfood:%ld\n", resource.food);
    printf("\tlinemate:%ld\n", resource.linemate);
    printf("\tmendiane:%ld\n", resource.mendiane);
    printf("\tphiras:%ld\n", resource.phiras);
    printf("\tsibur:%ld\n", resource.sibur);
    printf("\tthystame:%ld\n", resource.thystame);
}

void print_eggs(const zappy_t zappy)
{
    egg_t *egg = NULL;

    TAILQ_FOREACH(egg, &zappy.egg_head, egg_entries) {
        printf("new_egg:\n");
        printf("\tid=%d\n", egg->id);
        printf("\tteam_name=%s\n", egg->team_name);
        printf("\tpos : height(x)=%d, width(y)=%d\n",
            egg->height, egg->width);
        printf("\torigin:%d\n", egg->origin);
    }
}

void print_players(const zappy_t zappy)
{
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy.player_head, player_entries) {
        printf("new_player:\n");
        printf("\tid=%d\n", player->id);
        printf("\tteam_name=%s\n", player->team_name);
        printf("\tpos : height(x)=%d, width(y)=%d\n",
            player->height, player->width);
        printf("\tlevel=%d\n", player->level);
        printf("\tdirection=%ld\n", player->direction);
        print_resources(player->inventory);
        printf("\n");
    }
    printf("\n\n\n");
}

void print_tile_resources(const unsigned int client_fd, int width,
    int height, const resource_t resource)
{
    dprintf(client_fd, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n",
    width, height, resource.food, resource.linemate, resource.deraumere,
    resource.sibur, resource.mendiane, resource.phiras, resource.thystame);
}
