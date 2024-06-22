/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_sst
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(sst_func, all_good_sst)
{
    server_t server;
    arguments_t arg;

    server.max_clients = 1;
    server.cmd_arg_array = word_array("sst 10", " \n");
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    arg.freq = 10;

    int res = sst_func(&server, NULL, &arg, NULL);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(sst_func, no_graphical)
{
    server_t server;
    arguments_t arg;

    server.max_clients = 1;
    server.cmd_arg_array = word_array("sst 10", " \n");
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;
    arg.freq = 10;

    int res = sst_func(&server, NULL, &arg, NULL);


    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(sst_func, freq_is_zero)
{
    server_t server;
    arguments_t arg;

    server.max_clients = 1;
    server.cmd_arg_array = word_array("sst 0", " \n");
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    arg.freq = 0;

    int res = sst_func(&server, NULL, &arg, NULL);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(sst_func, freq_is_neg)
{
    server_t server;
    arguments_t arg;

    server.max_clients = 1;
    server.cmd_arg_array = word_array("sst -8", " \n");
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    arg.freq = 0;

    int res = sst_func(&server, NULL, &arg, NULL);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

