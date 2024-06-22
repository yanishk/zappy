/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** elevation
*/

#include "command_ia.h"

resource_t const elevations_resources[NB_ELEVATIONS] = {
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 0},
    {0, 2, 0, 1, 0, 2, 0},
    {0, 1, 1, 2, 0, 1, 0},
    {0, 1, 2, 1, 3, 0, 0},
    {0, 1, 2, 3, 0, 1, 0},
    {0, 2, 2, 2, 2, 2, 1}
};

incantation_t const elevations[NB_ELEVATIONS] = {
    {2, 1, &elevations_resources[0]},
    {3, 2, &elevations_resources[1]},
    {4, 2, &elevations_resources[2]},
    {5, 4, &elevations_resources[3]},
    {6, 4, &elevations_resources[4]},
    {7, 6, &elevations_resources[5]},
    {8, 6, &elevations_resources[6]}
};
