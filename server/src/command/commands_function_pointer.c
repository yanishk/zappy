/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commands_function_pointer
*/

#include "command.h"

int (*cmd_func[NB_CMD])(server_t *server, zappy_t *zappy,
    const arguments_t arg, client_t *client) = {
    &exit_func,
    &inventory_command,
    &take_object,
    &set_object,
    &move_forward,
    &turn_left,
    &turn_right,
    &connect_nbr,
    &fork_player
};

command_infos_t cmd_list[NB_CMD] = {
    {"Exit", 0, 1},
    {"Inventory", 1, 1},
    {"Take", 7, 2},
    {"Set", 7, 2},
    {"Forward", 7, 1},
    {"Left", 7, 1},
    {"Right", 7, 1},
    {"Connect_nbr", 0, 1},
    {"Fork", 42, 1}
};
