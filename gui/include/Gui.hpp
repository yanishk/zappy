/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_

    #define MIN_ARGS 5
    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0

    #include <iostream>

namespace Gui
{
    void displayHelp() {
        std::cerr << "USAGE: ./zappy_gui -p port -h machine\n";
        std::cerr << "\t\tport\t\tis the port number\n";
        std::cerr << "\t\tmachine\t\tis the name of the machine; localhost by default\n";
    }
}

/**
 * faudra créer un namespace Thread et Network (a voir avec Asio)
*/

#endif /* !GUI_HPP_ */
