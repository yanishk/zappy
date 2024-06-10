/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** is_positive_number
*/

#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

bool is_positive_number(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i += 1)
        if (isdigit(str[i]) == 0)
            return false;
    return true;
}
