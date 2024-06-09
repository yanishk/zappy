/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

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
    size_t north_west_tile;
    size_t west_tile;
    size_t south_west_tile;
    size_t south_tile;
    size_t south_east_tile;
    size_t east_tile;
    size_t north_east_tile;
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

typedef struct game_infos_s {
    int last_player_id;
    int last_egg_id;
} game_infos_t;

enum EGG_ORIGIN {
    EGG_FROM_START,
    EGG_FROM_FORK
};

typedef struct link_s {
    unsigned int client_fd;
    unsigned int player_id;
    TAILQ_ENTRY(link_s) link_entries;
} link_t;

typedef struct egg_s {
    int id;
    int width;
    int height;
    char *team_name;
    enum EGG_ORIGIN origin;
    TAILQ_ENTRY(egg_s) egg_entries;
} egg_t;

typedef struct player_s {
    int id;
    int width;
    int height;
    size_t direction;
    char *team_name;
    int level;
    clock_t clock_begin;
    resource_t inventory;
    TAILQ_ENTRY(player_s) player_entries;
} player_t;

typedef struct zappy_s {
    resource_t **resource;
    game_infos_t *infos;
    TAILQ_HEAD(, player_s) player_head;
    TAILQ_HEAD(, egg_s) egg_head;
    TAILQ_HEAD(, link_s) link_head;
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
void init_basis_map(zappy_t *zappy, const arguments_t *arg);
void initialize_game(const arguments_t arg, zappy_t *zappy);
void initialize_teams(const arguments_t arg, zappy_t *zappy);
void initialize_egg(const arguments_t arg, zappy_t *zappy, char *team_name,
    enum EGG_ORIGIN origin);
void initialize_player(zappy_t *zappy, egg_t *egg);
void initialize_resources(resource_t *resource);
void print_players(const zappy_t zappy);
void print_eggs(const zappy_t zappy);
void print_tile_resources(const unsigned int client_fd, int width, int height,
    const resource_t resource);

#endif /* !GAME_H_ */
