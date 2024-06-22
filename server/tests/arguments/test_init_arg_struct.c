/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_fill_arg_struct
*/

#include <criterion/criterion.h>
#include "server.h"

Test(fill_arg_struct, all_valid_arguments)
{
    arguments_t arg;
    char **array = word_array("./zappy_server -p 4242 -x 12 -y 7 -n team1 team2 -c 3 -f 15 --immortal true", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}

Test(fill_arg_struct, no_optional_arguments)
{
    arguments_t arg;
    char **array = word_array("./zappy_server -p 4242 -x 12 -y 7 -n team1 team2 -c 3", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.freq, 100);
    cr_assert_eq(arg.immortal, false);
}

Test(fill_arg_struct, no_team_provided)
{
    arguments_t arg;
    char **array = word_array("./zappy_server -p 4242 -x 1 -y 1 -n -c 1 -f 10", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(fill_arg_struct, invalid_flag)
{
    arguments_t arg;
    char **array = word_array("./zappy_server -invalid_flag value", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(fill_arg_struct, invalid_argument)
{
    arguments_t arg;
    char **array = word_array("./zappy_server -p not_a_port", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(fill_arg_struct, no_argument)
{
    arguments_t arg;
    char **array = word_array("./zappy_server", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(fill_arg_struct, multiple_arguments)
{
    arguments_t arg;
    char **array = word_array("./zappy_server -p 4242 -p 4243 -x 12 -y 7 -n team1 team2 -c 3", " ");
    int nb_args = array_size(array);
    int res = 0;

    res = fill_arg_struct(nb_args, (const char **) array, &arg);
    cr_assert_eq(res, EXIT_WITH_ERROR);
}
