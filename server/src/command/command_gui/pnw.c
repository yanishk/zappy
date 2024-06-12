/*
** EPITECH PROJECT, 2024
** zappy_command_gui_dos
** File description:
** pnw
*/

#include "command_gui.h"

int pnw_func(server_t *server, zappy_t *zappy,
    const unsigned int client_fd)
{
    player_t *player = get_player_by_fd(zappy, client_fd);
    client_t *graphical = get_graphical_client(server);
    int player_direction = 0;

    if (player == NULL || graphical == NULL)
        return EXIT_WITH_ERROR;
    player_direction = get_player_direction(player);
    dprintf(graphical->client_fd, "pnw %d %d %d %d %d %s\n", player->id,
    player->width, player->height, player_direction,
    player->level, player->team_name);
    return EXIT_WITH_SUCCESS;
}
