/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <stdlib.h>
    #include "arguments.h"
    #include <stdbool.h>
    #include "arguments.h"

    #define RIGHT_ANGLE 90

    #define NB_DIRECTIONS 4

    #define NORTH 0
    #define EAST 90
    #define SOUTH 180
    #define WEST 270

    #define FOOD_TIME_UNIT 126

    #define NB_DIR 4
    #define NB_RESOURCES 7

    #define FOOD "food"
    #define LINEMATE "linemate"
    #define DERAUMERE "deraumere"
    #define SIBUR "sibur"
    #define MENDIANE "mendiane"
    #define PHIRAS "phiras"
    #define THYSTAME "thystame"

    #define FOOD_DEN 0.5
    #define LINEMATE_DEN 0.3
    #define DERAUMERE_DEN 0.15
    #define SIBUR_DEN 0.1
    #define MENDIANE_DEN 0.1
    #define PHIRAS_DEN 0.08
    #define THYSTAME_DEN 0.05

typedef struct tile_numbering_s {
    size_t direction;
    size_t north_tile;
    size_t west_tile;
    size_t south_tile;
    size_t east_tile;
} tile_numbering_t;

typedef struct resource_s {
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
    size_t food;
} resource_t;

enum PLAYER_STATUS {
    IS_EGG_FROM_START,
    IS_EGG_FROM_FORK,
    IS_PLAYER
};

typedef struct player_s {
    int width;
    int height;
    int level;
    unsigned int id;
    char *team_name;
    enum PLAYER_STATUS status;
    size_t direction;
    clock_t clock_begin;
    resource_t inventory;
    TAILQ_ENTRY(player_s) player_entries;
} player_t;

typedef struct zappy_s {
    resource_t **resource;
    TAILQ_HEAD(, player_s) player_head;
} zappy_t;

struct repartion_resource {
    char *name;
    double density;
};

struct direction_player {
    size_t angle;
    int direction;
};

void replace_disconnected_players(const arguments_t arg, zappy_t *zappy);
void density_onland(const arguments_t *args, zappy_t *zappy);
void initialize_map(const arguments_t arg, zappy_t *zappy);
void initialize_teams(const arguments_t arg, zappy_t *zappy);
void initialize_player(const arguments_t arg, zappy_t *zappy, char *team_name,
    enum PLAYER_STATUS);
void initialize_player_pos(const arguments_t arg, zappy_t *zappy,
    player_t *player);
void initialize_resources(resource_t *resource);
void print_players_pos_and_direction(const zappy_t zappy);
void print_players(const zappy_t zappy);
void print_tile_resources(const unsigned int client_fd, int width, int height,
    const resource_t resource);

#endif /* !MAP_H_ */
