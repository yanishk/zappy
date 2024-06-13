/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** calculate_time_unit
*/

#include "game.h"

double calculate_freq(int frequency, double time_unit)
{
    time_unit /= frequency;
    time_unit *= TO_MILLI;
    return time_unit;
}
