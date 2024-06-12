/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** time_is_up
*/

#include "command_ia.h"

bool time_is_up(clock_t begin, double time_unit)
{
    clock_t end = clock();
    double time_elapsed_in_ms = ((end - begin) * TO_MILLI) / CLOCKS_PER_SEC;

    if (time_elapsed_in_ms >= time_unit)
        return true;
    return false;
}
