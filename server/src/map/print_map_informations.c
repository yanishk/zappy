/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** print_map_informations
*/

#include <string.h>
#include "map.h"

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

void print_players_pos_and_direction(const zappy_t zappy)
{
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy.player_head, player_entries) {
        printf("\tid=%d\n", player->id);
        printf("\tteam_name=%s\n", player->team_name);
        printf("\tpos : height(x)=%d, width(y)=%d\n",
            player->height, player->width);
        printf("\tdirection=%ld\n", player->direction);
        printf("\n");
    }
    printf("\n\n\n");
}

void print_players(const zappy_t zappy)
{
    player_t *player = NULL;

    TAILQ_FOREACH(player, &zappy.player_head, player_entries) {
        printf("new egg:\n");
        printf("\tid=%d\n", player->id);
        printf("\tteam_name=%s\n", player->team_name);
        printf("\tpos : height(x)=%d, width(y)=%d\n",
            player->height, player->width);
        printf("\tstatus=%d\n", player->status);
        printf("\tlevel=%d\n", player->level);
        printf("\tdirection=%ld\n", player->direction);
        print_resources(player->inventory);
        printf("\n");
    }
    printf("\n\n\n");
}

void print_tile_resources(const unsigned int client_fd, int width, int height,
    const resource_t resource)
{
    dprintf(client_fd, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n",
    width, height, resource.food, resource.linemate, resource.deraumere,
    resource.sibur, resource.mendiane, resource.phiras, resource.thystame);
}
