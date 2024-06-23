/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_eject
*/

#include <criterion/criterion.h>
#include "command_ia.h"

Test(eject_from_tile, no_player)
{
    server_t server;
    zappy_t zappy;
    client_t client;
    arguments_t arg;

    link_t *link = NULL;
    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    int res = eject_from_tile(&server, &zappy, &arg, &client);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(eject_from_tile, eject_player_kill_egg)
{
    server_t server;
    zappy_t *zappy = malloc(sizeof(zappy_t));
    client_t client;
    arguments_t arg;

    player_t *player1 = NULL;
    player_t *player2 = NULL;
    link_t *link = NULL;
    link_t *link2 = NULL;
    int player_id = 5;
    int client_fd = 5;

    TAILQ_INIT(&zappy->player_head);

    player1 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player1, player_entries);
    player1->id = player_id;
    player1->team_name = "team1";
    player1->height = 5;
    player1->width = 5;
    player1->direction = WEST;

    player2 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player2, player_entries);
    player2->id = player_id + 1;
    player2->team_name = "team1";
    player2->height = 5;
    player2->width = 5;
    player2->direction = WEST;

    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    link2 = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link2, link_entries);
    link2->client_fd = client_fd + 1;
    link2->player_id = player_id + 1;

    TAILQ_INIT(&zappy->egg_head);

    client.client_fd = client_fd;

    int res = eject_from_tile(&server, zappy, &arg, &client);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}
