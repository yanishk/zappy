/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Main
*/

#include <iostream>

#include "Run.hpp"
#include "Zappy.hpp"
#include "CreateAI.hpp"

static int help()
{
    std::cerr << USAGE << PORT << NAME << MACHINE;

    return EXIT_ERROR;
}

int main(int ac, char **av)
{
    if (ac < MIN_ARGS) {
        return help();
    }

    std::string name;
    std::string port;
    std::string home;

    for (std::size_t i = 0; av[i] != NULL; i++) {

        if (std::string(av[i]) == NAME_FLAG && av[i + 1]) {
            name = std::string(av[i + 1]);
        }

        if (std::string(av[i]) == PORT_FLAG && av[i + 1]) {
            port = std::string(av[i + 1]);
        }
        if (std::string(av[i]) == MACHINE_FLAG && av[i + 1]) {
            home = std::string(av[i + 1]);
        }
    }

    Zappy::Threads &threads = Zappy::createAI(name, port, home);
    Zappy::join(threads);

    return EXIT_SUCCESS;
}
