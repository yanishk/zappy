/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** initialize_game
*/

#include "game.h"

static void initialize_game_infos(zappy_t *zappy)
{
    zappy->infos = malloc(sizeof(game_infos_t));
    zappy->infos->last_egg_id = -1;
    zappy->infos->last_player_id = -1;
}

void initialize_game(const arguments_t arg, zappy_t *zappy)
{
    initialize_game_infos(zappy);
    init_basis_map(zappy, &arg);
    initialize_teams(arg, zappy);
}
