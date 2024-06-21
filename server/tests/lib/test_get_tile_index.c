/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_tile_index
*/

#include <criterion/criterion.h>
#include "server.h"

Test(get_tile_index, not_number_in_string)
{
    int res = get_tile_index("abcde", 10);

    cr_assert_eq(res, ERROR_RETURN);
}

Test(get_tile_index, above_nb_max)
{
    int res = get_tile_index("11", 10);

    cr_assert_eq(res, ERROR_RETURN);
}

Test(get_tile_index, all_works)
{
    int res = get_tile_index("11", 100);

    cr_assert_eq(res, 11);
}
