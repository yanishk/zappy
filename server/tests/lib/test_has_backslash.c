/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_has_backslash
*/

#include <criterion/criterion.h>
#include "server.h"

Test(has_backslash, no_backslash)
{
    bool res = has_backslash("iln'ypasdebackslash");

    cr_assert_eq(res, false);
}

Test(has_backslash, backslash_present)
{
    bool res = has_backslash("ilyaunbackslash\n");

    cr_assert_eq(res, true);
}

