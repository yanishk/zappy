/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** time_is_up
*/

#include <time.h>
#include <stdbool.h>

bool time_is_up(time_t begin, double time_unit)
{
    time_t end = time(NULL);

    if (difftime(end, begin) >= time_unit)
        return true;
    return false;
}
