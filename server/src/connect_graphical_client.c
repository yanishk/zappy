/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** connect_graphical_client
*/

#include "command_ia.h"
#include "command_gui.h"

static void smg_dropped_eggs(server_t *server, zappy_t *zappy)
{
    char egg_infos[MAX_BUFFER_SIZE] = {0};
    egg_t *egg = NULL;

    TAILQ_FOREACH(egg, &zappy->egg_head, egg_entries) {
        sprintf(egg_infos, "eni %d %d %d", egg->id, egg->width, egg->height);
        smg_func(server, egg_infos);
    }
}

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
    sgt_func(server, zappy, arg, client);
    mct_func(server, zappy, arg, client);
    tna_func(server, zappy, arg, client);
    pnw_for_existing_players(server, zappy);
    smg_dropped_eggs(server, zappy);
}

bool connect_graphical_client(server_t *server, zappy_t *zappy,
    arguments_t *arg, client_t *client)
{
    if (!is_player_connected(zappy, client->client_fd)) {
        if (array_size(server->cmd_arg_array) == 1 &&
            strcmp(server->cmd_arg_array[0], "GRAPHIC") == 0
            && get_graphical_client(server) == NULL) {
                client->is_graphic = true;
                send_game_info_to_graphic(server, zappy, arg, client);
                return true;
        }
    }
    return false;
}
