/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_pin
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(pin_func, print_player_inventory)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    int player_id = 4;
    unsigned int res = 0;

    server.cmd_arg_array = word_array("pin 4\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->width = 5;
    player->height = 3;
    player->inventory.food = 0;
    player->inventory.linemate = 0;
    player->inventory.deraumere = 0;
    player->inventory.sibur = 0;
    player->inventory.mendiane = 0;
    player->inventory.phiras = 0;
    player->inventory.thystame = 0;

    res = pin_func(&server, &zappy, NULL, NULL);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(pin_func, player_not_found)
{
    zappy_t zappy;
    server_t server;
    unsigned int res = 0;

    server.cmd_arg_array = word_array("pin 4\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);

    res = pin_func(&server, &zappy, NULL, NULL);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(pin_func, not_a_player_id)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    int player_id = 4;
    unsigned int res = 0;

    server.cmd_arg_array = word_array("pin other\n", " \n");
    server.max_clients = 1;
    server.clients = malloc(sizeof(client_t) * (server.max_clients));
    server.clients[0] = malloc(sizeof(client_t));
    server.clients[0]->is_graphic = true;
    server.clients[0]->client_fd = 0;
    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->width = 5;
    player->height = 3;
    player->inventory.food = 0;
    player->inventory.linemate = 0;
    player->inventory.deraumere = 0;
    player->inventory.sibur = 0;
    player->inventory.mendiane = 0;
    player->inventory.phiras = 0;
    player->inventory.thystame = 0;

    res = pin_func(&server, &zappy, NULL, NULL);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
