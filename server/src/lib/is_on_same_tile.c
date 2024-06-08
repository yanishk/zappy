/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** is_on_same_tile
*/

#include "map.h"

bool is_on_same_tile(const player_t *player1, const player_t *player2)
{
    return (player1->width == player2->width &&
            player1->height == player2->height &&
            player1->id != player2->id);
}
