/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** take_command
*/

#include "server.h"
#include "command.h"

function_array_t array_take[] = {
    { FOOD, &take_food },
    { LINEMATE, &take_linemate },
    { DERAUMERE, &take_deraumere },
    { DERAUMERE, &take_sibur },
    { MENDIANE, &take_mendiane },
    { PHIRAS, &take_phiras },
    { THYSTAME, &take_thystame }
};

int take_command(server_t *server, zappy_t *zappy, const arguments_t,
    client_t *client)
{
    player_t *player = get_player(zappy, client->client_fd);
    bool was_taken = false;

    if (player == NULL || server->cmd_arg_array[1] == NULL)
        return EXIT_WITH_ERROR;
    for (size_t i = 0; i != NB_RESSOURCES; i++) {
        if (strcmp(array_take[i].ressource, server->cmd_arg_array[1]) == 0) {
            was_taken = array_take[i].func(server, zappy, player, was_taken);
        }
    }
    if (was_taken == false)
        return EXIT_WITH_ERROR;
    return EXIT_WITH_SUCCESS;
}
