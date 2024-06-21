/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_calculate_time_unit
*/

#include <criterion/criterion.h>
#include "server.h"

Test(calculate_freq, correct_freq)
{
    double res = calculate_freq(10, 20.0);

    cr_assert_eq(2000, res);
}