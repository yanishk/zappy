/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_plv
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(plv_func, print_player_level)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    int player_id = 4;
    unsigned int res = 0;

    server.cmd_arg_array = word_array("plv 4\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->level = 2;

    res = plv_func(&server, &zappy, NULL, NULL);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(plv_func, player_not_found)
{
    zappy_t zappy;
    server_t server;
    unsigned int res = 0;

    server.cmd_arg_array = word_array("plv 4\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);

    res = plv_func(&server, &zappy, NULL, NULL);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(plv_func, not_a_player_id)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    int player_id = 4;
    unsigned int res = 0;

    server.cmd_arg_array = word_array("plv other\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->level = 2;

    res = plv_func(&server, &zappy, NULL, NULL);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
