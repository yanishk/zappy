/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_msz
*/

#include <criterion/criterion.h>
#include "command_gui.h"

Test(msz_func, print_map_size)
{
    arguments_t arg;
    client_t client;
    int res = 0;

    arg.width = 10;
    arg.height = 20;
    client.client_fd = 0;

    res = msz_func(NULL, NULL, &arg, &client);
    cr_assert_eq(res, EXIT_WITH_SUCCESS);
}
