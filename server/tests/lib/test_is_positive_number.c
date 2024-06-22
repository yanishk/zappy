/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test
*/

#include <criterion/criterion.h>
#include "server.h"

Test(is_positive_number, positive_case)
{
    bool res = is_positive_number("10");

    cr_assert_eq(true, res);
}

Test(is_positive_number, negative_case)
{
    bool res = is_positive_number("-10");

    cr_assert_eq(false, res);
}
