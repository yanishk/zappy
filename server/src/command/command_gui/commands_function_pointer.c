/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commands_function_pointer
*/

#include "command_gui.h"
#include "command_ia.h"

int (*cmd_func_gui[NB_GUI_CMD])(client_t *) = {
    &exit_func
};

command_infos_t cmd_list_gui[NB_GUI_CMD] = {
    {EXIT_COMMAND, 1}
};
