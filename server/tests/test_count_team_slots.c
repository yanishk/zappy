/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_count_team_slots
*/

#include <criterion/criterion.h>
#include "server.h"

Test(count_team_eggs, no_team_eggs)
{
    zappy_t zappy;
    const char *team_name = "team1";
    size_t nb_eggs = 0;
    unsigned int res = 0;

    TAILQ_INIT(&zappy.egg_head);
    res = count_team_eggs(&zappy, team_name);
    cr_assert_eq(nb_eggs, res);
}

Test(count_team_eggs, four_team_eggs)
{
    zappy_t zappy;
    egg_t *egg = NULL;
    const char *team_name = "team1";
    size_t nb_eggs = 4;
    unsigned int res = 0;

    TAILQ_INIT(&zappy.egg_head);
    for (size_t i = 0; i < nb_eggs; i++) {
        egg = malloc(sizeof(egg_t));
        TAILQ_INSERT_TAIL(&zappy.egg_head, egg, egg_entries);
        egg->team_name = strdup(team_name);
    }
    res = count_team_eggs(&zappy, team_name);
    cr_assert_eq(nb_eggs, res);
}

Test(count_team_players, no_team_players)
{
    zappy_t zappy;
    const char *team_name = "team1";
    size_t nb_players = 0;
    unsigned int res = 0;

    TAILQ_INIT(&zappy.player_head);
    res = count_team_players(&zappy, team_name);
    cr_assert_eq(nb_players, res);
}

Test(count_team_players, six_team_players)
{
    zappy_t zappy;
    player_t *player = NULL;
    const char *team_name = "team1";
    size_t nb_players = 6;
    unsigned int res = 0;

    TAILQ_INIT(&zappy.player_head);
    for (size_t i = 0; i < nb_players; i++) {
        player = malloc(sizeof(player_t));
        TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
        player->team_name = strdup(team_name);
    }
    res = count_team_players(&zappy, team_name);
    cr_assert_eq(nb_players, res);
}

Test(count_team_slots, no_team_slots)
{
    zappy_t zappy;
    const char *team_name = "team1";
    size_t nb_players = 0;
    unsigned int res = 0;

    TAILQ_INIT(&zappy.egg_head);
    TAILQ_INIT(&zappy.player_head);
    res = count_team_players(&zappy, team_name);
    cr_assert_eq(nb_players, res);
}

Test(count_team_slots, eight_team_slots)
{
    zappy_t zappy;
    egg_t *egg = NULL;
    player_t *player = NULL;
    const char *team_name = "team1";
    size_t nb_players = 5;
    size_t nb_eggs = 3;
    size_t nb_total = nb_players + nb_eggs;
    unsigned int res = 0;

    TAILQ_INIT(&zappy.egg_head);
    TAILQ_INIT(&zappy.player_head);
    for (size_t i = 0; i < nb_eggs; i++) {
        egg = malloc(sizeof(egg_t));
        TAILQ_INSERT_TAIL(&zappy.egg_head, egg, egg_entries);
        egg->team_name = strdup(team_name);
    }
    for (size_t i = 0; i < nb_players; i++) {
        player = malloc(sizeof(player_t));
        TAILQ_INSERT_TAIL(&zappy.player_head, player, player_entries);
        player->team_name = strdup(team_name);
    }
    res = count_team_slots(&zappy, team_name);
    cr_assert_eq(nb_total, res);
}
