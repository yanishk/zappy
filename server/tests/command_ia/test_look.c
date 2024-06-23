/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_look
*/

#include <criterion/criterion.h>
#include "command_ia.h"

static zappy_t *init_zappy(zappy_t *zappy, arguments_t *arg)
{
    zappy->resource = malloc(sizeof(resource_t *) * arg->height);
    for (int i = 0; i < arg->height; i++) {
        zappy->resource[i] = malloc(sizeof(resource_t) * arg->width);
        for (int j = 0; j < arg->width; j++) {
            zappy->resource[i][j].deraumere = 0;
            zappy->resource[i][j].food = 1;
            zappy->resource[i][j].linemate = 1;
            zappy->resource[i][j].mendiane = 0;
            zappy->resource[i][j].phiras = 0;
            zappy->resource[i][j].sibur = 1;
            zappy->resource[i][j].thystame = 0;
        }
    }
    return zappy;
}

Test(look, succesful_look_west)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    player->direction = WEST;
    player->height = 5;
    player->width = 5;
    player->level = 7;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    int res = look_around(NULL, zappy, &arg, &client);
    cr_assert_eq(res, COMMAND_SUCCESS);
}

Test(look, succesful_look_north)
{
        zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    player->direction = NORTH;
    player->height = 5;
    player->width = 5;
    player->level = 8;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    int res = look_around(NULL, zappy, &arg, &client);
    cr_assert_eq(res, COMMAND_SUCCESS);
}

Test(look, succesful_look_east)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    player->direction = EAST;
    player->height = 5;
    player->width = 5;
    player->level = 8;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    int res = look_around(NULL, zappy, &arg, &client);
    cr_assert_eq(res, COMMAND_SUCCESS);
}

Test(look, succesful_look_north_positive_height)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    player->direction = NORTH;
    player->height = 5;
    player->width = 0;
    player->level = 1;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    int res = look_around(NULL, zappy, &arg, &client);
    cr_assert_eq(res, COMMAND_SUCCESS);
}

Test(look, succesful_look_south_negative_height)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player, player_entries);
    player->id = player_id;
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    player->direction = SOUTH;
    player->height = 8;
    player->width = 0;
    player->level = 3;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    int res = look_around(NULL, zappy, &arg, &client);
    cr_assert_eq(res, COMMAND_SUCCESS);
}


Test(look, no_player)
{
    zappy_t zappy;
    arguments_t arg;
    client_t client;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    arg.width = 10;
    arg.height = 10;
    zappy.resource = malloc(sizeof(resource_t *) * arg.height);
    for (int i = 0; i < arg.width; i++) {
        zappy.resource[i] = malloc(sizeof(resource_t) * arg.width);
    }
    zappy.resource[5][5].deraumere = 1;
    zappy.resource[5][5].food = 0;
    zappy.resource[5][5].linemate = 1;
    zappy.resource[5][5].mendiane = 1;
    zappy.resource[5][5].phiras = 0;
    zappy.resource[5][5].sibur = 1;
    zappy.resource[5][5].thystame = 0;

    int res = look_around(NULL, &zappy, &arg, &client);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(look_around, multiple_player)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    client_t client;
    player_t *player1 = NULL;
    player_t *player2 = NULL;
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    player1 = malloc(sizeof(player_t));
    player2 = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy->player_head, player1, player_entries);
    TAILQ_INSERT_TAIL(&zappy->player_head, player2, player_entries);
    player1->id = player_id;
    player2->id = player_id + 1;
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    client.client_fd = client_fd;
    player1->direction = EAST;
    player1->height = 5;
    player1->width = 5;
    player1->level = 8;
    player2->direction = EAST;
    player2->height = 5;
    player2->width = 5;
    player2->level = 8;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    int res = look_around(NULL, zappy, &arg, &client);
    cr_assert_eq(res, COMMAND_SUCCESS);
}

Test(get_on_land, no_player)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    arguments_t arg;
    coordinate_t coord = {0, 0};
    link_t *link = NULL;
    int client_fd = 5;
    int player_id = 0;

    TAILQ_INIT(&zappy->player_head);
    TAILQ_INIT(&zappy->link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy->link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    arg.width = 10;
    arg.height = 10;
    zappy = init_zappy(zappy, &arg);

    char *res = get_on_land(zappy, coord, client_fd);
    cr_assert(strcmp(res, " food linemate sibur") == 0);
}
