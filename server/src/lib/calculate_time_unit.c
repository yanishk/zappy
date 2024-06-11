/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** calculate_time_unit
*/

#include "game.h"

double calculate_freq(int frequency, double food_time_unit)
{
    food_time_unit /= frequency;
    food_time_unit *= TO_MILLI;
    return food_time_unit;
}
