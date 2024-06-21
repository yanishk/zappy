/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** test_is_command_queue_full
*/

#include <criterion/criterion.h>
#include "command_ia.h"

Test(is_command_queue_full, empty_queue)
{
    client_t client;
    bool res = false;

    TAILQ_INIT(&client.command_head);
    res = is_command_queue_full(&client);
    cr_assert_eq(false, res);
}

Test(is_command_queue_full, queue_full)
{
    client_t client;
    command_ia_t *command = NULL;
    size_t nb_commands = 10;
    bool res = false;

    TAILQ_INIT(&client.command_head);
    for (size_t i = 0; i < nb_commands; i++) {
        command = malloc(sizeof(command_ia_t));
        TAILQ_INSERT_TAIL(&client.command_head, command, command_ia_entries);
    }
    res = is_command_queue_full(&client);
    cr_assert_eq(true, res);
}
