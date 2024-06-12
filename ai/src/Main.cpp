/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Main
*/

#include <string.h>
#include <iostream>

#include "Team.hpp"
#include "Zappy.hpp"
#include "AI/Queen.hpp"

static int help()
{
    std::cerr << "USAGE: ./zappy_ai -p port -n name -h machine\n";
    std::cerr << "\t\tport\t\tis the port number\n";
    std::cerr << "\t\tname\t\tis the name of the team\n";
    std::cerr << "\t\tmachine\t\tis the name of the machine; localhost by default\n";

    return EXIT_ERROR;
}

int main(int ac, char **av)
{
    if (ac < MIN_ARGS) {
        return help();
    }

    std::string port;
    std::string name;

    for (std::size_t i = 0; av[i] != NULL; i++) {

        if (!strcmp(av[i], PORT_FLAG) && av[i + 1] != NULL) {
            port = std::string(av[i + 1]);
        }

        if (!strcmp(av[i], NAME_FLAG) && av[i + 1] != NULL) {
            name = std::string(av[i + 1]);
        }

    }

    Zappy::Team team(name, port, std::make_unique<Zappy::Queen>(port, name));

    return team.run();
}
