/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_height_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(height_flag, valid_positive_height)
{
    arguments_t arg;
    char **array = word_array("-y 10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = height_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.height, 10);
}

Test(height_flag, invalid_zero_height)
{
    arguments_t arg;
    char **array = word_array("-y 0", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = height_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(height_flag, invalid_negative_height)
{
    arguments_t arg;
    char **array = word_array("-y -10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = height_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
