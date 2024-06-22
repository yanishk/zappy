/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_width_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(width_flag, valid_positive_width)
{
    arguments_t arg;
    char **array = word_array("-x 10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = width_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.width, 10);
}

Test(width_flag, invalid_zero_width)
{
    arguments_t arg;
    char **array = word_array("-x 0", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = width_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(width_flag, invalid_negative_width)
{
    arguments_t arg;
    char **array = word_array("-x -10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = width_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
