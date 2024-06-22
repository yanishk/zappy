/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_get_next_id
*/

#include <criterion/criterion.h>

int get_next_id(int *id);

Test(lib_tests, test_get_next_id)
{
    int id = 8;
    get_next_id(&id);

    cr_assert_eq(9, id);
}