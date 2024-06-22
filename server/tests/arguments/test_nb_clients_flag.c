/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_nb_clients_flag
*/

#include <criterion/criterion.h>
#include "server.h"

Test(nb_clients_flag, valid_positive_nb_clients)
{
    arguments_t arg;
    char **array = word_array("-c 10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = nb_clients_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_SUCCESS);
    cr_assert_eq(arg.nb_clients, 10);
}

Test(nb_clients_flag, invalid_zero_nb_clients)
{
    arguments_t arg;
    char **array = word_array("-c 0", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = nb_clients_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}

Test(nb_clients_flag, invalid_negative_nb_clients)
{
    arguments_t arg;
    char **array = word_array("-c -10", " ");
    int arg_nb = array_size(array);
    int i = 0;
    int res = nb_clients_flag(arg_nb, (const char **) array, &i, &arg);

    cr_assert_eq(res, EXIT_WITH_ERROR);
}
