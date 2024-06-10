/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Main
*/

#include "Gui.hpp"
#include "Client.hpp"
#include "DisplayGame.hpp"

int main(int ac, char **av)
{
    if (ac != MIN_ARGS) {
        Gui::displayHelp();
        return EXIT_WITH_ERROR;
    }

    std::string port = av[2];
    std::string host = av[4];

    CommandManager cmd;

    try {
        Client client(port, host, cmd);
        client.run();

    } catch (std::exception& e) {
        std::cerr << "Failed on: " << e.what() << "\n";
    }

    return EXIT_WITH_SUCCESS;
}
