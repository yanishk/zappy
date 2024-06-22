/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_player_direction
*/

#include <criterion/criterion.h>
#include "server.h"

Test(get_player_direction, no_player)
{
    player_t *player = NULL;

    int res = get_player_direction(player);

    cr_assert_eq(res, ERROR_RETURN);
}

Test(get_player_direction, direction_found)
{
    player_t player;
    player.direction = 90;

    int res = get_player_direction(&player);

    cr_assert_eq(res, 2);
}

Test(get_player_direction, direction_not_found)
{
    player_t player;
    player.direction = 50;

    int res = get_player_direction(&player);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}
