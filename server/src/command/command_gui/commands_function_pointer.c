/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commands_function_pointer
*/

#include "command_gui.h"

int (*cmd_func_gui[NB_GUI_CMD])(server_t *, zappy_t *,
    const arguments_t, client_t *) = {
    &exit_func,
    &msz_func,
    &bct_func,
    &mct_func,
    &tna_func
};

command_infos_gui_t cmd_list_gui[NB_GUI_CMD] = {
    {EXIT_COMMAND, 1},
    {MSZ_COMMAND, 1},
    {BCT_COMMAND, 3},
    {MCT_COMMAND, 1},
    {TNA_COMMAND, 1}
};
