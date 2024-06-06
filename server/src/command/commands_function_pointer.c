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
    &fork_player,
    &look_around
};

command_infos_t cmd_list[NB_CMD] = {
    {EXIT_COMMAND, 0, 1},
    {INVENTORY_COMMAND, 1, 1},
    {TAKE_COMMAND, 7, 2},
    {SET_COMMAND, 7, 2},
    {FORWARD_COMMAND, 7, 1},
    {LEFT_COMMAND, 7, 1},
    {RIGHT_COMMAND, 7, 1},
    {CONNECT_NBR_COMMAND, 0, 1},
    {FORK_COMMAND, 42, 1}
  //look
};
