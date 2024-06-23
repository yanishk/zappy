/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** test_connect_nbr
*/

#include <criterion/criterion.h>
#include "command_ia.h"

Test(connect_nbr, succesful_connect_nbr)
{
    zappy_t zappy;
    client_t client;
    player_t *player = NULL;
    link_t *link = NULL;
    egg_t *egg = NULL;
    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player->team_name = "team1";

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    TAILQ_INIT(&zappy.egg_head);
    egg = malloc(sizeof(egg_t));
    TAILQ_INSERT_TAIL(&zappy.egg_head, egg, egg_entries);
    egg->team_name = "team1";

    client.client_fd = client_fd;

    int res = connect_nbr(NULL, &zappy, NULL, &client);

    cr_assert_eq(res, COMMAND_SUCCESS);
}

Test(connect_nbr, no_player)
{
    zappy_t zappy;
    client_t client;
    link_t *link = NULL;
    int player_id = 0;
    int client_fd = 5;

    TAILQ_INIT(&zappy.player_head);

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;

    client.client_fd = client_fd;

    int res = connect_nbr(NULL, &zappy, NULL, &client);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
