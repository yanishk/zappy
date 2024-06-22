/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_port_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(port_flag, valid_positive_port)
{
    arguments_t arg;
    char **array = word_array("-p 10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = port_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.port, 10);
}

Test(port_flag, invalid_zero_port)
{
    arguments_t arg;
    char **array = word_array("-p 0", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = port_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(port_flag, invalid_negative_port)
{
    arguments_t arg;
    char **array = word_array("-p -10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = port_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
