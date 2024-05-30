/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <stdlib.h>
    #include <sys/queue.h>

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
    size_t level;
    resource_t inventory;
    TAILQ_ENTRY(player_s) player_entries;
} player_t;

typedef struct zappy_s {
    resource_t **resource;
    TAILQ_HEAD(, player_s) player_head;
} zappy_t;

#endif /* !MAP_H_ */
