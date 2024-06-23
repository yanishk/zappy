/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_fork
*/

#include <criterion/criterion.h>
#include "command_ia.h"

Test(fork, successful_fork)
{
    server_t server;
    zappy_t *zappy = malloc(sizeof(zappy_t));
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int player_id = 0;
    int client_fd = 5;
    zappy->infos = malloc(sizeof(game_infos_t));

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    TAILQ_INIT(&zappy->player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    player->team_name = "team1";
    player->height = 5;
    player->width = 5;

    TAILQ_INIT(&zappy->egg_head);

    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    client.client_fd = client_fd;
    zappy->infos->last_egg_id = 1;

    int res = fork_player(&server, zappy, NULL, &client);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}
