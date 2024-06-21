/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_link
*/

#include <criterion/criterion.h>
#include "server.h"

Test(get_link_by_client_fd, empty)
{
    zappy_t zappy;
    link_t *res_link = NULL;
    unsigned int client_fd = 7;

    TAILQ_INIT(&zappy.link_head);
    res_link = get_link_by_client_fd(&zappy, client_fd);
    cr_assert_eq(NULL, res_link);
}

Test(get_link_by_client_fd, one_link)
{
    zappy_t zappy;
    link_t *link = NULL;
    link_t *res_link = NULL;
    unsigned int client_fd = 7;
    unsigned int player_id = 4;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    res_link = get_link_by_client_fd(&zappy, client_fd);
    cr_assert_neq(NULL, res_link);
    cr_assert_eq(client_fd, res_link->client_fd);
    cr_assert_eq(player_id, res_link->player_id);
}

Test(get_link_by_client_fd, multiple_links)
{
    zappy_t zappy;
    link_t *link = NULL;
    link_t *res_link = NULL;
    unsigned int nb_links = 10;
    unsigned int client_fd = 7;
    unsigned int player_id = 6;
    unsigned int searched_client_fd = 14;
    unsigned int searched_player_id = 13;

    TAILQ_INIT(&zappy.link_head);
    for (unsigned int i = 0; i < nb_links; i++) {
        link = malloc(sizeof(link_t));
        TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
        link->client_fd = client_fd;
        link->player_id = player_id;
        client_fd++;
        player_id++;
    }
    res_link = get_link_by_client_fd(&zappy, searched_client_fd);
    cr_assert_neq(NULL, res_link);
    cr_assert_eq(searched_client_fd, res_link->client_fd);
    cr_assert_eq(searched_player_id, res_link->player_id);
}

Test(get_link_by_player_id, empty)
{
    zappy_t zappy;
    link_t *res_link = NULL;
    unsigned int player_id = 7;

    TAILQ_INIT(&zappy.link_head);
    res_link = get_link_by_player_id(&zappy, player_id);
    cr_assert_eq(NULL, res_link);
}

Test(get_link_by_player_id, one_link)
{
    zappy_t zappy;
    link_t *link = NULL;
    link_t *res_link = NULL;
    unsigned int client_fd = 7;
    unsigned int player_id = 4;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    res_link = get_link_by_player_id(&zappy, player_id);
    cr_assert_neq(NULL, res_link);
    cr_assert_eq(client_fd, res_link->client_fd);
    cr_assert_eq(player_id, res_link->player_id);
}

Test(get_link_by_player_id, multiple_links)
{
    zappy_t zappy;
    link_t *link = NULL;
    link_t *res_link = NULL;
    unsigned int nb_links = 10;
    unsigned int client_fd = 7;
    unsigned int player_id = 6;
    unsigned int searched_client_fd = 14;
    unsigned int searched_player_id = 13;

    TAILQ_INIT(&zappy.link_head);
    for (unsigned int i = 0; i < nb_links; i++) {
        link = malloc(sizeof(link_t));
        TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
        link->client_fd = client_fd;
        link->player_id = player_id;
        client_fd++;
        player_id++;
    }
    res_link = get_link_by_player_id(&zappy, searched_player_id);
    cr_assert_neq(NULL, res_link);
    cr_assert_eq(searched_client_fd, res_link->client_fd);
    cr_assert_eq(searched_player_id, res_link->player_id);
}

Test(get_client_fd, empty)
{
    zappy_t zappy;
    int retrived_client_fd = 0;
    unsigned int player_id = 7;

    TAILQ_INIT(&zappy.link_head);
    retrived_client_fd = get_client_fd(&zappy, player_id);
    cr_assert_eq(ERROR_RETURN, retrived_client_fd);
}

Test(get_client_fd, one_link)
{
    zappy_t zappy;
    link_t *link = NULL;
    unsigned int client_fd = 7;
    unsigned int player_id = 4;
    int retrived_client_fd = 0;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    retrived_client_fd = get_client_fd(&zappy, player_id);
    cr_assert_eq(retrived_client_fd, client_fd);
}

Test(get_client_fd, multiple_links)
{
    zappy_t zappy;
    link_t *link = NULL;
    unsigned int nb_links = 10;
    unsigned int client_fd = 7;
    unsigned int player_id = 8;
    unsigned int searched_client_fd = 10;
    unsigned int searched_player_id = 11;
    int retrived_client_fd = 0;

    TAILQ_INIT(&zappy.link_head);
    for (unsigned int i = 0; i < nb_links; i++) {
        link = malloc(sizeof(link_t));
        TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
        link->client_fd = client_fd;
        link->player_id = player_id;
        client_fd++;
        player_id++;
    }
    retrived_client_fd = get_client_fd(&zappy, searched_player_id);
    cr_assert_eq(retrived_client_fd, searched_client_fd);
}

Test(get_player_by_fd, player_not_found1)
{
    zappy_t zappy;
    int client_fd = 7;
    player_t *player = NULL;

    TAILQ_INIT(&zappy.player_head);
    TAILQ_INIT(&zappy.link_head);
    player = get_player_by_fd(&zappy, client_fd);
    cr_assert_eq(NULL, player);
}

Test(get_player_by_fd, player_not_found2)
{
    zappy_t zappy;
    int client_fd = 7;
    int player_id = 12;
    player_t *player = NULL;
    link_t *link = NULL;

    TAILQ_INIT(&zappy.link_head);
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    player = get_player_by_fd(&zappy, client_fd);
    cr_assert_eq(NULL, player);
}

Test(get_player_by_fd, player_found)
{
    zappy_t zappy;
    int client_fd = 7;
    int player_id = 12;
    player_t *player = NULL;
    link_t *link = NULL;

    TAILQ_INIT(&zappy.player_head);
    TAILQ_INIT(&zappy.link_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    link = malloc(sizeof(link_t));
    TAILQ_INSERT_TAIL(&zappy.link_head, link, link_entries);
    link->client_fd = client_fd;
    link->player_id = player_id;
    player = get_player_by_fd(&zappy, client_fd);
    cr_assert_neq(NULL, player);
    cr_assert_eq(player_id, player->id);
}

Test(get_player_by_id, player_not_found)
{
    zappy_t zappy;
    int player_id = 7;
    player_t *player = NULL;

    TAILQ_INIT(&zappy.player_head);
    player = get_player_by_id(&zappy, player_id);
    cr_assert_eq(NULL, player);
}

Test(get_player_by_id, player_found)
{
    zappy_t zappy;
    int player_id = 7;
    player_t *player = NULL;

    TAILQ_INIT(&zappy.player_head);
    player = malloc(sizeof(player_t));
    TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
    player->id = player_id;
    player = get_player_by_id(&zappy, player_id);
    cr_assert_eq(player_id, player->id);
}

