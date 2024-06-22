/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_pbc
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(pbc_func, print_broadcast)
{
    server_t server;
    player_t player;
    int player_id = 4;
    unsigned int res = 0;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    player.id = player_id;

    res = pbc_func(&server, player.id, "text");
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(pbc_func, graphical_not_found)
{
    server_t server;
    player_t player;
    int player_id = 4;
    unsigned int res = 0;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;
    player.id = player_id;

    res = pbc_func(&server, player.id, "text");
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
