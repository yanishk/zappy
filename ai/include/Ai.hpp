/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Ai
*/

#ifndef AI_HPP_
    #define AI_HPP_

    #define MIN_ARGS 7
    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0

    #include <iostream>

namespace Ai
{
    void displayHelp() {
        std::cerr << "USAGE: ./zappy_ai -p port -n name -h machine\n";
        std::cerr << "\t\tport\t\tis the port number\n";
        std::cerr << "\t\tname\t\tis the name of the team\n";
        std::cerr << "\t\tmachine\t\tis the name of the machine; localhost by default\n";
    }
}


#endif /* !AI_HPP_ */
