/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_tile_index
*/

#include "server.h"

int get_tile_index(const char *string_nb, const int nb_max)
{
    int nb = 0;

    if (!is_positive_number(string_nb))
        return ERROR_RETURN;
    nb = atoi(string_nb);
    if (nb >= nb_max)
        return ERROR_RETURN;
    return nb;
}
