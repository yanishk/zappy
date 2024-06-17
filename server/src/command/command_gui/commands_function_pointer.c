/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commands_function_pointer
*/

#include "command_gui.h"

command_infos_gui_t cmd_list_gui[NB_GUI_CMD] = {
    {EXIT_COMMAND, 1, &exit_func},
    {MSZ_COMMAND, 1, &msz_func},
    {BCT_COMMAND, 3, &bct_func},
    {MCT_COMMAND, 1, &mct_func},
    {TNA_COMMAND, 1, &tna_func},
    {PLV_COMMAND, 2, &plv_func},
    {PPO_COMMAND, 2, &ppo_func},
    {PIN_COMMAND, 2, &pin_func},
    {SGT_COMMAND, 1, &sgt_func},
    {SST_COMMAND, 2, &sst_func}
};
