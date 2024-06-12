/*
** EPITECH PROJECT, 2024
** zappy_command_gui_dos
** File description:
** command_gui
*/

#ifndef COMMAND_GUI_H_
    #define COMMAND_GUI_H_

    #include "common_command.h"

    #define NB_GUI_CMD 9

    #define MSZ_COMMAND "msz"
    #define MCT_COMMAND "mct"
    #define BCT_COMMAND "bct"
    #define TNA_COMMAND "tna"
    #define PLV_COMMAND "plv"
    #define PPO_COMMAND "ppo"
    #define PIN_COMMAND "pin"
    #define SGT_COMMAND "sgt"

typedef struct command_infos_gui_s {
    char *name;
    size_t arg_nb;
} command_infos_gui_t;

extern int (*cmd_func_gui[NB_GUI_CMD])(server_t *, zappy_t *,
    const arguments_t, client_t *);
extern command_infos_gui_t cmd_list_gui[NB_GUI_CMD];

int msz_func(server_t *, zappy_t *, const arguments_t, client_t *);
int bct_func(server_t *, zappy_t *, const arguments_t, client_t *);
int mct_func(server_t *, zappy_t *, const arguments_t, client_t *);
int tna_func(server_t *, zappy_t *, const arguments_t, client_t *);
int plv_func(server_t *, zappy_t *, const arguments_t, client_t *);
int ppo_func(server_t *, zappy_t *, const arguments_t, client_t *);
int pin_func(server_t *, zappy_t *, const arguments_t, client_t *);
int sgt_func(server_t *, zappy_t *, const arguments_t, client_t *);

int pnw_func(server_t *, zappy_t *, const unsigned int);
int pfk_func(server_t *, zappy_t *, const unsigned int);
int pdr_func(server_t *, zappy_t *, client_t *, char *);
int pgt_func(server_t *, zappy_t *, client_t *, char *);
int pdi_func(server_t *, zappy_t *, const unsigned int);
int enw_func(server_t *, player_t *, const int);
int ebo_func(server_t *, const int);
int edi_func(server_t *, const int);

int ppo(server_t *, zappy_t *, const int);

#endif /* !COMMAND_GUI_H_ */
