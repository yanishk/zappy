/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Main
*/

#include "Ai.hpp"

int main(int ac, __attribute__((__unused__)) char **av)
{
    if (ac != MIN_ARGS) {
        Ai::displayHelp();
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}
