/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_edi
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(edi_func, all_good_edi)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    int res = edi_func(&server, 0);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(edi_func, no_graphical)
{
    server_t server;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;

    int res = edi_func(&server, 0);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
