/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_turn_right
*/

#include <criterion/criterion.h>
#include "command_ia.h"

Test(turn_right, succesful_right_facing_west)
{
    server_t server;
    zappy_t zappy;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int player_id = 0;
    int client_fd = 5;

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
    client.client_fd = client_fd;
    player->direction = WEST;

    int res = turn_right(&server, &zappy, NULL, &client);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(turn_right, succesful_right_facing_south)
{
    server_t server;
    zappy_t zappy;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int player_id = 0;
    int client_fd = 5;

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
    client.client_fd = client_fd;
    player->direction = SOUTH;

    int res = turn_right(&server, &zappy, NULL, &client);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(turn_right, no_player)
{
    server_t server;
    zappy_t zappy;
    client_t client;
    link_t *link = NULL;
    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;

    int res = turn_right(&server, &zappy, NULL, &client);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
