/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_bct
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(bct_func, bct_for_map_tile)
{
    arguments_t arg;
    client_t client;
    server_t server;
    zappy_t zappy;
    int res = 0;

    arg.width = 10;
    arg.height = 20;
    client.client_fd = 0;
    server.cmd_arg_array = word_array("bct 9 15\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    zappy.resource = malloc(sizeof(resource_t *) * arg.height);
    for (int x = 0; x < arg.height; x++)
        zappy.resource[x] = malloc(sizeof(resource_t) * arg.width);
    for (int x = 0; x < arg.height; x++) {
        for (int y = 0; y < arg.width; y++) {
            zappy.resource[x][y].deraumere = 0;
            zappy.resource[x][y].food = 0;
            zappy.resource[x][y].linemate = 0;
            zappy.resource[x][y].mendiane = 0;
            zappy.resource[x][y].phiras = 0;
            zappy.resource[x][y].sibur = 0;
            zappy.resource[x][y].thystame = 0;
        }
    }

    res = bct_func(&server, &zappy, &arg, &client);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(bct_func, bct_for_out_of_map_tile)
{
    arguments_t arg;
    client_t client;
    server_t server;
    zappy_t zappy;
    int res = 0;

    arg.width = 10;
    arg.height = 20;
    client.client_fd = 0;
    server.cmd_arg_array = word_array("bct 10 20\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    zappy.resource = malloc(sizeof(resource_t *) * arg.height);
    for (int x = 0; x < arg.height; x++)
        zappy.resource[x] = malloc(sizeof(resource_t) * arg.width);
    for (int x = 0; x < arg.height; x++) {
        for (int y = 0; y < arg.width; y++) {
            zappy.resource[x][y].deraumere = 0;
            zappy.resource[x][y].food = 0;
            zappy.resource[x][y].linemate = 0;
            zappy.resource[x][y].mendiane = 0;
            zappy.resource[x][y].phiras = 0;
            zappy.resource[x][y].sibur = 0;
            zappy.resource[x][y].thystame = 0;
        }
    }

    res = bct_func(&server, &zappy, &arg, &client);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
