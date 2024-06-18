/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** has_backslash
*/

#include <stdbool.h>

bool has_backslash(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\n')
            return true;
    return false;
}
