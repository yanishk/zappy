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

void print_players(const zappy_t zappy)
{
    player_t *player;

    TAILQ_FOREACH(player, &zappy.player_head, player_entries) {
        printf("new egg:\n");
        printf("\tteam_name=%s\n", player->team_name);
        printf("\tpos : height=%ld, width=%ld\n",
            player->height, player->width);
        printf("\tis_egg=%d\n", player->is_egg);
        printf("\tlevel=%ld\n", player->level);
        print_resources(player->inventory);
        printf("\n");
    }
}
