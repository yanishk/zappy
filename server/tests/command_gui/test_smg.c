/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_smg
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(smg_func, all_good_smg)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    int res = smg_func(&server, "toto");

    cr_assert_eq(res, EXIT_SUCCESS);
}

Test(smg_func, no_graphical)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;

    int res = smg_func(&server, "toto");

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(smg_func, no_msg)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    int res = smg_func(&server, NULL);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}