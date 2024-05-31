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

typedef struct resource_s {
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
    size_t food;
} resource_t;

typedef struct player_s {
    size_t width;
    size_t height;
    bool is_egg;
    char *team_name;
    unsigned int id;
    size_t level;
    resource_t inventory;
    TAILQ_ENTRY(player_s) player_entries;
} player_t;

typedef struct zappy_s {
    resource_t **resource;
    TAILQ_HEAD(, player_s) player_head;
} zappy_t;

void density_onland(arguments_t *args, zappy_t *zappy);

void initialize_map(const arguments_t arg, zappy_t *zappy);
void initialize_teams(const arguments_t arg, zappy_t *zappy);
void initialize_resources(resource_t *resource);
void print_players(const zappy_t zappy);

#endif /* !MAP_H_ */
