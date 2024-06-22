/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_graphical_client
*/

#include <criterion/criterion.h>
#include "server.h"

Test(lib_tests, first_graphical_client_found)
{
    server_t server;
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;

    client_t *res = get_graphical_client(&server);

    cr_assert(res != NULL);
}

Test(lib_tests, no_graphical_client)
{
    server_t server;
    server.max_clients = 5;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));

    for (size_t i = 0; i < server.max_clients; i++) {
        server.clients[i] = malloc(sizeof(client_t));
        server.clients[i]->is_graphic = false;
    }

    client_t *res = get_graphical_client(&server);

    cr_assert(res == NULL);
}

Test(lib_tests, graphical_among_clients)
{
    server_t server;
    server.max_clients = 5;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));

    for (size_t i = 0; i < server.max_clients; i++) {
        server.clients[i] = malloc(sizeof(client_t));
        if (i == 3)
            server.clients[i]->is_graphic = true;
        else
            server.clients[i]->is_graphic = false;
    }

    client_t *res = get_graphical_client(&server);

    cr_assert(res != NULL);
}