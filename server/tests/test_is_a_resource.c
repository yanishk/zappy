/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_is_a_resource
*/

#include <criterion/criterion.h>
#include "server.h"

Test(is_a_resource, correct_resource)
{
    bool res = is_a_resource("food");

    cr_assert_eq(res, true);
}

Test(is_a_resource, incorrect_resource)
{
    bool res = is_a_resource("cacahuete");

    cr_assert_eq(res, false);
}

