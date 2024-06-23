/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_broadcast
*/

#include <criterion/criterion.h>
#include "command_ia.h"

Test(broadcast, succesful_broacast)
{
    server_t server;
    zappy_t zappy;
    arguments_t arg;
    client_t client;

    player_t *player = NULL;
    player_t *player2 = NULL;
    link_t *link = NULL;
    link_t *link2 = NULL;

    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->height = 5;
    player->width = 5;
    player->direction = WEST;

    player2 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player2, player_entries);
    player2->id = player_id + 1;
    player2->height = 0;
    player2->width = 0;
    player2->direction = WEST;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    link2 = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link2, link_entries);
    link2->client_fd = client_fd + 1;
    link2->player_id = player_id + 1;

    client.client_fd = client_fd;
    server.cmd_arg_array = word_array("broadcast hello", " \n");
    arg.height = 10;
    arg.width = 10;

    int res = broadcast(&server, &zappy, &arg, &client);

    cr_assert_eq(res, EXIT_SUCCESS);
}

Test(broadcast, succesful_broacast_north)
{
    server_t server;
    zappy_t zappy;
    arguments_t arg;
    client_t client;

    player_t *player = NULL;
    player_t *player2 = NULL;
    link_t *link = NULL;
    link_t *link2 = NULL;

    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->height = 5;
    player->width = 5;
    player->direction = NORTH;

    player2 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player2, player_entries);
    player2->id = player_id + 1;
    player2->height = 9;
    player2->width = 9;
    player2->direction = NORTH;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    link2 = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link2, link_entries);
    link2->client_fd = client_fd + 1;
    link2->player_id = player_id + 1;

    client.client_fd = client_fd;
    server.cmd_arg_array = word_array("broadcast hello", " \n");
    arg.height = 10;
    arg.width = 10;

    int res = broadcast(&server, &zappy, &arg, &client);

    cr_assert_eq(res, EXIT_SUCCESS);
}

Test(broadcast, straight_line_north)
{
    server_t server;
    zappy_t zappy;
    arguments_t arg;
    client_t client;

    player_t *player = NULL;
    player_t *player2 = NULL;
    link_t *link = NULL;
    link_t *link2 = NULL;

    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->height = 5;
    player->width = 0;
    player->direction = WEST;

    player2 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player2, player_entries);
    player2->id = player_id + 1;
    player2->height = 5;
    player2->width = 1;
    player2->direction = WEST;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    link2 = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link2, link_entries);
    link2->client_fd = client_fd + 1;
    link2->player_id = player_id + 1;


    client.client_fd = client_fd;
    server.cmd_arg_array = word_array("broadcast hello", " \n");
    arg.height = 10;
    arg.width = 10;

    int res = broadcast(&server, &zappy, &arg, &client);

    cr_assert_eq(res, EXIT_SUCCESS);
}

Test(broadcast, straight_line_west)
{
    server_t server;
    zappy_t zappy;
    arguments_t arg;
    client_t client;

    player_t *player = NULL;
    player_t *player2 = NULL;
    link_t *link = NULL;
    link_t *link2 = NULL;

    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->height = 6;
    player->width = 1;
    player->direction = WEST;

    player2 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player2, player_entries);
    player2->id = player_id + 1;
    player2->height = 5;
    player2->width = 1;
    player2->direction = WEST;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    link2 = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link2, link_entries);
    link2->client_fd = client_fd + 1;
    link2->player_id = player_id + 1;


    client.client_fd = client_fd;
    server.cmd_arg_array = word_array("broadcast hello", " \n");
    arg.height = 10;
    arg.width = 10;

    int res = broadcast(&server, &zappy, &arg, &client);

    cr_assert_eq(res, EXIT_SUCCESS);
}
