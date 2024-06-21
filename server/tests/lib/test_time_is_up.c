/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_time_is_up
*/

#include <criterion/criterion.h>
#include "server.h"
#include <time.h>

Test(time_is_up, time_is_not_up)
{
    clock_t start = clock();

    bool res = time_is_up(start, 20.0);

    cr_assert_eq(res, false);
}