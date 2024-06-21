/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_is_on_same_tile
*/

#include <criterion/criterion.h>
#include "server.h"

Test(player_on_same_tile, on_same_tile)
{
    player_t player1;
    player_t player2;

    player1.height = 0;
    player1.width = 10;
    player1.id = 0;

    player2.height = 0;
    player2.width = 10;
    player2.id = 1;

    bool res = player_on_same_tile(&player1, &player2);

    cr_assert_eq(res, true);
}

Test(player_on_same_tile, same_id)
{
    player_t player1;
    player_t player2;

    player1.height = 0;
    player1.width = 10;
    player1.id = 0;

    player2.height = 0;
    player2.width = 10;
    player2.id = 0;

    bool res = player_on_same_tile(&player1, &player2);

    cr_assert_eq(res, false);
}

Test(player_on_same_tile, different_tile_width)
{
    player_t player1;
    player_t player2;

    player1.height = 0;
    player1.width = 1;
    player1.id = 0;

    player2.height = 0;
    player2.width = 10;
    player2.id = 1;

    bool res = player_on_same_tile(&player1, &player2);

    cr_assert_eq(res, false);
}

Test(player_on_same_tile, different_tile_height)
{
    player_t player1;
    player_t player2;

    player1.height = 1;
    player1.width = 10;
    player1.id = 0;

    player2.height = 0;
    player2.width = 10;
    player2.id = 1;

    bool res = player_on_same_tile(&player1, &player2);

    cr_assert_eq(res, false);
}

Test(egg_on_same_tile, on_same_tile)
{
    player_t player;
    egg_t egg;

    player.height = 0;
    player.width = 10;

    egg.height = 0;
    egg.width = 10;

    bool res = egg_on_same_tile(&player, &egg);

    cr_assert_eq(res, true);
}

Test(egg_on_same_tile, different_tile)
{
    player_t player;
    egg_t egg;

    player.height = 1;
    player.width = 9;

    egg.height = 0;
    egg.width = 10;

    bool res = egg_on_same_tile(&player, &egg);

    cr_assert_eq(res, false);
}
