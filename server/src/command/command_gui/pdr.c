/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pdr
*/

#include "command_gui.h"

static struct associate_resource_nb_s const set_resource[NB_RESOURCES] = {
    {FOOD, 0},
    {LINEMATE, 1},
    {DERAUMERE, 2},
    {SIBUR, 3},
    {MENDIANE, 4},
    {PHIRAS, 5},
    {THYSTAME, 6}
};

int pdr_func(server_t *server, zappy_t *zappy, client_t *client, char *name)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);
    client_t *graphical = get_graphical_client(server);

    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    for (int index = 0; index < NB_RESOURCES; index++) {
        if (strcmp(set_resource[index].name, name) == 0) {
            dprintf(graphical->client_fd, "pdr %d %d\n",
                player->id, set_resource[index].code_resource);
        }
    }
    return EXIT_WITH_SUCCESS;
}
