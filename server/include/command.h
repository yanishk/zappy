/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "server.h"

typedef struct command_infos {
    char *name;
    double time_unit;
} command_infos_t;

typedef struct command_s {
    char **tab;
    double time_unit;
    size_t index;
    clock_t clock_begin;
    TAILQ_ENTRY(command_s) command_entries;
} command_t;

typedef struct function_array {
    char *ressource;
    bool (*func)(server_t *server, zappy_t *zappy, player_t *player,
        bool);
} function_array_t;

extern int (*cmd_func[NB_CMD])(server_t *, zappy_t *, const arguments_t,
    client_t *);
extern command_infos_t cmd_list[NB_CMD];

int exit_func(server_t *, zappy_t *, const arguments_t, client_t *);
int inventory_command(server_t *, zappy_t *, const arguments_t, client_t *);
int move_forward(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_left(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_right(server_t *, zappy_t *, const arguments_t, client_t *);
int connect_nbr(server_t *, zappy_t *, const arguments_t, client_t *);
bool is_player_connected(const zappy_t *, const unsigned int);
int connect_player(server_t *, zappy_t *, const arguments_t,
    const unsigned int);

int set_object(server_t *, zappy_t *, const arguments_t, client_t *);
bool set_thystame(server_t *, zappy_t *, player_t *, bool);
bool set_sibur(server_t *, zappy_t *, player_t *, bool);
bool set_phiras(server_t *, zappy_t *, player_t *, bool);
bool set_mendiane(server_t *, zappy_t *, player_t *, bool);
bool set_linemate(server_t *, zappy_t *, player_t *, bool);
bool set_food(server_t *, zappy_t *, player_t *, bool);
bool set_deraumere(server_t *, zappy_t *, player_t *, bool);

int take_command(server_t *, zappy_t *, const arguments_t, client_t *);
bool take_thystame(server_t *, zappy_t *, player_t *, bool);
bool take_sibur(server_t *, zappy_t *, player_t *, bool);
bool take_phiras(server_t *, zappy_t *, player_t *, bool);
bool take_mendiane(server_t *, zappy_t *, player_t *, bool);
bool take_linemate(server_t *, zappy_t *, player_t *, bool);
bool take_food(server_t *, zappy_t *, player_t *, bool);
bool take_deraumere(server_t *, zappy_t *, player_t *, bool);

#endif /* !COMMAND_H_ */
