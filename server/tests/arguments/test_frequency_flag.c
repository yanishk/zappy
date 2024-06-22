/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_frequency_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(frequency_flag, valid_positive_frequency)
{
    arguments_t arg;
    char **array = word_array("-f 10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = frequency_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.freq, 10);
}

Test(frequency_flag, invalid_zero_frequency)
{
    arguments_t arg;
    char **array = word_array("-f 0", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = frequency_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(frequency_flag, invalid_negative_frequency)
{
    arguments_t arg;
    char **array = word_array("-f -10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = frequency_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
