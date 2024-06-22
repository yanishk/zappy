/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_pic
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(pic_func, print_start_incantation)
{
    server_t server;
    player_t player;
    unsigned int res = 0;
    int id_players[] = {4, 9, 12, 44};

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    player.width = 5;
    player.height = 3;
    player.level = 2;

    res = pic_func(&server, &player, id_players);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(pic_func, no_graphical_client)
{
    server_t server;
    player_t player;
    unsigned int res = 0;
    int id_players[] = {4, 9, 12, 44};

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;
    player.width = 5;
    player.height = 3;
    player.level = 2;

    res = pic_func(&server, &player, id_players);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
