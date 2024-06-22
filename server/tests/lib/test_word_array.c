/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_word_array
*/

#include <criterion/criterion.h>
#include "server.h"

Test(word_array, array_of_size_three)
{
    char *str = "      enorme  \t\t    excellent  \t\n       super    ";
    char **array = word_array(str, " \t\n");
    size_t size = 3;

    cr_assert_eq(size, array_size(array));
    cr_assert(strcmp("enorme", array[0]) == 0);
    cr_assert(strcmp("excellent", array[1]) == 0);
    cr_assert(strcmp("super", array[2]) == 0);
}
