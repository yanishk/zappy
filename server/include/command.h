/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "server.h"

    #define OBJECT_TO_TAKE server->cmd_arg_array[1]
    #define TILE_RESOURCE zappy->resource[player->height][player->width]

typedef struct command_infos {
    char *name;
    double time_unit;
} command_infos_t;

typedef struct command_s {
    char **array;
    double time_unit;
    size_t index;
    clock_t clock_begin;
    TAILQ_ENTRY(command_s) command_entries;
} command_t;

extern int (*cmd_func[NB_CMD])(server_t *, zappy_t *, const arguments_t,
    client_t *);
extern command_infos_t cmd_list[NB_CMD];

bool is_player_connected(const zappy_t *, const unsigned int);
int connect_player(server_t *, zappy_t *, const arguments_t,
    const unsigned int);

int exit_func(server_t *, zappy_t *, const arguments_t, client_t *);
int inventory_command(server_t *, zappy_t *, const arguments_t, client_t *);
int move_forward(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_left(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_right(server_t *, zappy_t *, const arguments_t, client_t *);
int connect_nbr(server_t *, zappy_t *, const arguments_t, client_t *);
int set_object(server_t *, zappy_t *, const arguments_t, client_t *);
int take_object(server_t *, zappy_t *, const arguments_t, client_t *);

#endif /* !COMMAND_H_ */
