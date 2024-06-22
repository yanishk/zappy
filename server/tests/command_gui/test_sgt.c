/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_sgt
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(sgt_func, all_good_sgt)
{
    server_t server;
    arguments_t arg;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    arg.freq = 10;

    int res = sgt_func(&server, NULL, &arg, NULL);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(sgt_func, no_graphical)
{
    server_t server;
    arguments_t arg;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;
    arg.freq = 10;

    int res = sgt_func(&server, NULL, &arg, NULL);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
