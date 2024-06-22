/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_array_functions
*/

#include <criterion/criterion.h>
#include "server.h"

Test(array_size, array_of_size_three)
{
    size_t size = 3;
    char **array = word_array("eva grosse nulle\n", " \n");
    size_t res = array_size(array);

    cr_assert_eq(size, res);
}
