/*
** EPITECH PROJECT, 2024
** zappy_command_gui_dos
** File description:
** command_gui
*/

#ifndef COMMAND_GUI_H_
    #define COMMAND_GUI_H_

    #include "common_command.h"

    #define NB_GUI_CMD 4

    #define MSZ_COMMAND "msg"
    #define MCT_COMMAND "mct"
    #define BCT_COMMAND "bct"

    #define NB_DIR 4

    #define NB_DIR 4

typedef struct command_infos_gui_s {
    char *name;
    size_t arg_nb;
} command_infos_gui_t;

extern int (*cmd_func_gui[NB_GUI_CMD])(server_t *, zappy_t *,
    const arguments_t, client_t *);
extern command_infos_gui_t cmd_list_gui[NB_GUI_CMD];

int msz_command(server_t *, zappy_t *, const arguments_t, client_t *);
int bct_command(server_t *, zappy_t *, const arguments_t, client_t *);
int mct_command(server_t *, zappy_t *, const arguments_t, client_t *);

#endif /* !COMMAND_GUI_H_ */
