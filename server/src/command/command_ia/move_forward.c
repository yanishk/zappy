/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** move_forward
*/

#include "command_ia.h"
#include "command_gui.h"

int move_forward(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    player_t *player = get_player_by_fd(zappy, client->client_fd);

    if (player == NULL)
        return EXIT_WITH_ERROR;
    move_player(player->direction, player, *arg);
    ppo(server, zappy, player->id);
    return EXIT_WITH_SUCCESS;
}
