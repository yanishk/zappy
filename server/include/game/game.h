/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "arguments.h"
    #include "egg.h"
    #include "player.h"

    #define NB_ELEVATIONS 7
    #define NB_DIRECTIONS 4

    #define NORTH 0
    #define EAST 90
    #define SOUTH 180
    #define WEST 270

    #define RIGHT_ANGLE 90

    #define TO_MILLI 1000

    #define ELEVATION elevations[player->level - 1]
    #define REQUIRED_RESOURCES ELEVATION.required_resources
    #define REQUIRED_LEVEL ELEVATION.elevation_level
    #define REQUIRED_PLAYERS ELEVATION.required_players

typedef struct incantation_s {
    unsigned int elevation_level;
    unsigned int required_players;
    const resource_t *required_resources;
} incantation_t;

typedef struct game_infos_s {
    int last_player_id;
    int last_egg_id;
} game_infos_t;

typedef struct link_s {
    unsigned int client_fd;
    unsigned int player_id;
    TAILQ_ENTRY(link_s) link_entries;
} link_t;

typedef struct zappy_s {
    resource_t **resource;
    game_infos_t *infos;
    TAILQ_HEAD(, player_s) player_head;
    TAILQ_HEAD(, egg_s) egg_head;
    TAILQ_HEAD(, link_s) link_head;
} zappy_t;

void initialize_game(const arguments_t, zappy_t *);
void init_basis_map(zappy_t *, const arguments_t *);
void initialize_teams(const arguments_t, zappy_t *);
void initialize_egg(const arguments_t, zappy_t *, char *);
void initialize_player(zappy_t *, egg_t *);
void initialize_resources(resource_t *);
void print_players(const zappy_t);
void print_eggs(const zappy_t);
void print_tile_resources(const unsigned int, int, int, const resource_t);

#endif /* !GAME_H_ */
