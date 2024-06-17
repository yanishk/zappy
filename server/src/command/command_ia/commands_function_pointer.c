/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commands_function_pointer
*/

#include "command_ia.h"

command_infos_ia_t cmd_list_ia[NB_IA_CMD] = {
    {EXIT_COMMAND, 0, 1, &exit_func},
    {INVENTORY_COMMAND, 1, 1, &inventory_command},
    {TAKE_COMMAND, 7, 2, &take_object},
    {SET_COMMAND, 7, 2, &set_object},
    {FORWARD_COMMAND, 7, 1, &move_forward},
    {LEFT_COMMAND, 7, 1, &turn_left},
    {RIGHT_COMMAND, 7, 1, &turn_right},
    {CONNECT_NBR_COMMAND, 0, 1, &connect_nbr},
    {FORK_COMMAND, 42, 1, &fork_player},
    {EJECT_COMMAND, 7, 1, &eject_from_tile},
    {LOOK_COMMAND, 7, 1, &look_around},
    {BROADCAST_COMMAND, 7, 2, &broadcast},
    {START_INCANTATION_COMMAND, 0, 1, &start_incantation},
    {END_INCANTATION_COMMAND, 300, 1, &end_incantation}
};
