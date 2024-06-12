/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pdr
*/

#include "command_gui.h"

int pdr_func(server_t *server, zappy_t *zappy, client_t *client, char *name)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    client_t *graphical = get_graphical_client(server);
    const char *resource_list[NB_RESOURCES] = {FOOD, LINEMATE, DERAUMERE,
        SIBUR, MENDIANE, PHIRAS, THYSTAME};

    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    for (int index = 0; index < NB_RESOURCES; index++) {
        if (strcmp(resource_list[index], name) == 0) {
            dprintf(graphical->client_fd, "pdr %d %s\n", player->id, name);
        }
    }
    return EXIT_WITH_SUCCESS;
}
