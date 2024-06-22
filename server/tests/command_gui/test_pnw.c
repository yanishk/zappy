/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_pnw
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(pnw_func, print_new_player_infos)
{
    zappy_t zappy;
    server_t server;
    player_t *player = NULL;
    link_t *link = NULL;
    const char *team_name = "team1";
    int client_fd = 7;
    int player_id = 12;
    unsigned int res = 0;

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
    player->height = 10;
    player->level = 2;
    player->direction = SOUTH;
    player->team_name = strdup(team_name);
    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    res = pnw_func(&server, &zappy, client_fd);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(pnw_func, player_not_found)
{
    zappy_t zappy;
    server_t server;
    link_t *link = NULL;
    int client_fd = 7;
    int player_id = 12;
    unsigned int res = 0;

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

    res = pnw_func(&server, &zappy, client_fd);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
