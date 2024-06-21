/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_immortal_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(immortal_flag, immortal_true)
{
    arguments_t arg;
    char **array = word_array("--immortal true", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = immortal_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.immortal, true);
}

Test(immortal_flag, immortal_false)
{
    arguments_t arg;
    char **array = word_array("--immortal false", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = immortal_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.immortal, false);
}

Test(immortal_flag, invalid_immortal)
{
    arguments_t arg;
    char **array = word_array("--immortal other", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = immortal_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
