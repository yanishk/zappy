/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** player
*/


#ifndef PLAYER_H_
    #define PLAYER_H_

    #include <sys/queue.h>
    #include "resource.h"

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

struct direction_player {
    size_t angle;
    int direction;
};

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

#endif /* !PLAYER_H_ */
