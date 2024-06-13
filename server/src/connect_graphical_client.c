/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** connect_graphical_client
*/

#include "command_ia.h"
#include "command_gui.h"

static void pnw_for_existing_players(server_t *server, zappy_t *zappy)
{
    link_t *link = NULL;

    TAILQ_FOREACH(link, &zappy->link_head, link_entries) {
        pnw_func(server, zappy, link->client_fd);
    }
}

static void send_game_info_to_graphic(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    msz_func(server, zappy, arg, client);
    mct_func(server, zappy, arg, client);
    tna_func(server, zappy, arg, client);
    pnw_for_existing_players(server, zappy);
}

bool connect_graphical_client(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    if (!is_player_connected(zappy, client->client_fd)) {
        if (array_size(server->cmd_arg_array) == 1 &&
            strcmp(server->cmd_arg_array[0], "GRAPHIC") == 0) {
                client->is_graphic = true;
                send_game_info_to_graphic(server, zappy, arg, client);
                free_array(server->cmd_arg_array);
                return true;
        }
    }
    return false;
}
