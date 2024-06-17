/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** player_connection
*/

#include "command_ia.h"
#include "command_gui.h"

void link_client_and_player(zappy_t *zappy, const unsigned int client_fd,
    const unsigned int player_id)
{
    link_t *link = malloc(sizeof(link_t));

    if (link == NULL)
        return;
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
}

int connect_player(server_t *server, zappy_t *zappy, const arguments_t arg,
    const unsigned int client_fd)
{
    egg_t *chosen_egg = NULL;

    if (is_player_connected(zappy, client_fd))
        return UNKNOWN_COMMAND;
    chosen_egg = get_random_team_egg(zappy, server->cmd_arg_array[0]);
    if (chosen_egg == NULL)
        return UNKNOWN_COMMAND;
    initialize_player(zappy, chosen_egg);
    link_client_and_player(zappy, client_fd, zappy->infos->last_player_id);
    ebo_func(server, chosen_egg->id);
    free_egg(zappy, chosen_egg);
    dprintf(client_fd, "%d\n%d %d\n",
        count_team_eggs(zappy, server->cmd_arg_array[0]), arg.height,
        arg.width);
    pnw_func(server, zappy, client_fd);
    return COMMAND_SUCCESS;
}

bool is_player_connected(const zappy_t *zappy, const unsigned int client_fd)
{
    link_t *link = NULL;

    TAILQ_FOREACH(link, &zappy->link_head, link_entries) {
        if (link->client_fd == client_fd)
            return true;
    }
    return false;
}
