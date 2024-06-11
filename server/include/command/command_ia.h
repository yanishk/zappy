/*
** EPITECH PROJECT, 2024
** zappy_push_wo_vision
** File description:
** command_ai
*/

#ifndef COMMAND_AI_H_
    #define COMMAND_AI_H_

    #include "common_command.h"

    #define NB_IA_CMD 12

    #define INVENTORY_COMMAND "Inventory"
    #define TAKE_COMMAND "Take"
    #define SET_COMMAND "Set"
    #define FORWARD_COMMAND "Forward"
    #define LEFT_COMMAND "Left"
    #define RIGHT_COMMAND "Right"
    #define CONNECT_NBR_COMMAND "Connect_nbr"
    #define FORK_COMMAND "Fork"
    #define EJECT_COMMAND "Eject"
    #define LOOK_COMMAND "Look"
    #define BROADCAST_COMMAND "Broadcast"

    #define OBJECT_TO_TAKE server->cmd_arg_array[1]
    #define TILE_RESOURCE zappy->resource[player->height][player->width]

typedef struct command_infos_s {
    char *name;
    double time_unit;
    size_t arg_nb;
} command_infos_t;

typedef struct command_ia_s {
    char **array;
    double time_unit;
    size_t index;
    clock_t clock_begin;
    TAILQ_ENTRY(command_ia_s) command_ia_entries;
} command_ia_t;

typedef struct coordinate_s {
    int height;
    int width;
} coordinate_t;

typedef struct road_broadcast_s {
    int width_direct;
    int height_direct;
    int width_undirect;
    int height_undirect;
} road_broadcast_t;

extern int (*cmd_func_ia[NB_IA_CMD])(server_t *, zappy_t *, const arguments_t,
    client_t *);
extern command_infos_t cmd_list_ia[NB_IA_CMD];

bool is_player_connected(const zappy_t *, const unsigned int);
int connect_player(server_t *, zappy_t *, const arguments_t,
    const unsigned int);
void move_player(size_t direction, player_t *, const arguments_t);
char *get_on_land(zappy_t *, coordinate_t, unsigned int);
void free_ia_command(client_t *, command_ia_t *);

int inventory_command(server_t *, zappy_t *, const arguments_t, client_t *);
int move_forward(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_left(server_t *, zappy_t *, const arguments_t, client_t *);
int turn_right(server_t *, zappy_t *, const arguments_t, client_t *);
int connect_nbr(server_t *, zappy_t *, const arguments_t, client_t *);
int set_object(server_t *, zappy_t *, const arguments_t, client_t *);
int take_object(server_t *, zappy_t *, const arguments_t, client_t *);
int fork_player(server_t *, zappy_t *, const arguments_t, client_t *);
int eject_from_tile(server_t *, zappy_t *, const arguments_t, client_t *);
int broadcast(server_t *, zappy_t *, const arguments_t, client_t *);
int look_around(server_t *, zappy_t *, const arguments_t, client_t *);

#endif /* !COMMAND_AI_H_ */
