/*
** EPITECH PROJECT, 2024
** zappy_command_gui_dos
** File description:
** command_gui
*/

#ifndef COMMAND_GUI_H_
    #define COMMAND_GUI_H_

    #include "server.h"

typedef struct command_infos_gui_s {
    char *name;
    size_t arg_nb;
} command_infos_gui_t;

typedef struct command_gui_s {
    size_t index;
    TAILQ_ENTRY(command_ia_s) command_entries;
} command_gui_t;

extern int (*cmd_func_gui[NB_GUI_CMD])(client_t *);
extern command_infos_gui_t cmd_list_ia[NB_GUI_CMD];

int exit_func(client_t *);

#endif /* !COMMAND_GUI_H_ */
