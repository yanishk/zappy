/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_random_team_egg
*/

#include <criterion/criterion.h>
#include "server.h"

Test(get_random_team_egg, no_egg_array)
{
    zappy_t zappy;
    char *team_name = "team1";

    TAILQ_INIT(&zappy.egg_head);
    egg_t *res = get_random_team_egg(&zappy, team_name);
    cr_assert_eq(res, NULL);
}
