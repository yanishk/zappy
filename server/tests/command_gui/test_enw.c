/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_enw
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(enw_func, all_good_enw)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 1;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    int res = enw_func(&server, player, 0);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(enw_func, no_player)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;

    TAILQ_INIT(&zappy.link_head);
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    int res = enw_func(&server, player, 0);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(enw_func, no_graphical)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 1;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = false;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    int res = enw_func(&server, player, 0);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
