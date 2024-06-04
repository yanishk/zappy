/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set_object
*/

#include "server.h"
#include "command.h"

function_array_t array_set[] = {
    { FOOD, &set_food },
    { LINEMATE, &set_linemate },
    { DERAUMERE, &set_deraumere },
    { SIBUR, &set_sibur },
    { MENDIANE, &set_mendiane },
    { PHIRAS, &set_phiras },
    { THYSTAME, &set_thystame }
};

int set_object(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);
    bool was_set = false;

    if (player == NULL || server->cmd_arg_array[1] == NULL)
        return EXIT_WITH_ERROR;
    for (size_t index = 0; index != NB_RESSOURCES; index++) {
        if (strcmp(array_set[index].ressource,
            server->cmd_arg_array[1]) == 0) {
            was_set = array_set[index].func(server, zappy, player, was_set);
        }
    }
    if (was_set == false)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
