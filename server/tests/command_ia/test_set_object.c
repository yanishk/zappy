/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_set_object
*/

#include <criterion/criterion.h>
#include "command_ia.h"

static zappy_t *init_zappy(zappy_t *zappy, arguments_t *arg)
{
    zappy->resource = malloc(sizeof(resource_t *) * arg->height);
    for (int i = 0; i < arg->height; i++) {
        zappy->resource[i] = malloc(sizeof(resource_t) * arg->width);
        for (int j = 0; j < arg->width; j++) {
            zappy->resource[i][j].deraumere = 1;
            zappy->resource[i][j].food = 1;
            zappy->resource[i][j].linemate = 1;
            zappy->resource[i][j].mendiane = 1;
            zappy->resource[i][j].phiras = 1;
            zappy->resource[i][j].sibur = 0;
            zappy->resource[i][j].thystame = 1;
        }
    }
    return zappy;
}

Test(set_object, no_player)
{
    server_t server;
    zappy_t zappy;
    client_t client;

    link_t *link = NULL;

    int player_id = 0;
    int client_fd = 5;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    TAILQ_INIT(&zappy.player_head);
    TAILQ_INIT(&zappy.link_head);

    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    client.client_fd = client_fd;

    int res = set_object(&server, &zappy, NULL, &client);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(set_object, all_good)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    server_t server;

    player_t *player = NULL;
    link_t *link = NULL;

    int client_fd = 5;
    int player_id = 5;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    TAILQ_INIT(&zappy->player_head);

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    player->direction = WEST;
    player->height = 5;
    player->width = 5;
    player->level = 7;

    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    client.client_fd = client_fd;
    server.cmd_arg_array = word_array("Set food\n", " \n");
    arg.width = 10;
    arg.height = 10;

    zappy = init_zappy(zappy, &arg);
    player->inventory.food = 1;
    player->inventory.deraumere = 1;
    player->inventory.linemate = 1;
    player->inventory.mendiane = 1;
    player->inventory.phiras = 1;
    player->inventory.sibur = 1;
    player->inventory.thystame = 1;

    int res = set_object(&server, zappy, NULL, &client);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(set_object, no_resource_on_land)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    server_t server;

    player_t *player = NULL;
    link_t *link = NULL;

    int client_fd = 5;
    int player_id = 5;

    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;

    TAILQ_INIT(&zappy->player_head);

    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    player->direction = WEST;
    player->height = 5;
    player->width = 5;
    player->level = 7;

    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    client.client_fd = client_fd;
    server.cmd_arg_array = word_array("Set sibur\n", " \n");
    arg.width = 10;
    arg.height = 10;

    zappy = init_zappy(zappy, &arg);
    player->inventory.food = 1;
    player->inventory.deraumere = 1;
    player->inventory.linemate = 1;
    player->inventory.mendiane = 1;
    player->inventory.phiras = 1;
    player->inventory.sibur = 0;
    player->inventory.thystame = 1;

    int res = set_object(&server, zappy, NULL, &client);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
