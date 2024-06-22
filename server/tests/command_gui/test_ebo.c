/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_ebo
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(ebo_func, all_good_ebo)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    int res = ebo_func(&server, 0);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(ebo_func, no_graphical)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;

    int res = ebo_func(&server, 0);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
