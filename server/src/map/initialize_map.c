/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_map
*/

#include "map.h"

void initialize_map(const arguments_t arg, zappy_t *zappy)
{
    initialize_players(arg, zappy);
    print_players(*zappy);
}
