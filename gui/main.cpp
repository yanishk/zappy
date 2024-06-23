/*
** EPITECH PROJECT, 2024
** all_test_libray
** File description:
** main
*/

#include "Game.hpp"
#include "ParsesModelConfig.hpp"
#include "Commands.hpp"
#include "Gui.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
    if (ac < MIN_ARGS) {
        Gui::displayHelp();
        return EXIT_WITH_ERROR;
    }
    bool animation = false;
    std::string port = av[2];
    std::string host = av[4];
    if (ac > MIN_ARGS && !std::string(av[5]).compare("-a")) {
        animation = true;
    }

    Zappy::CommandManager cmd;

    try {
        Zappy::Client client(port, host, cmd, animation);
        client.run();
    } catch (std::exception& e) {
        std::cerr << "Failed on: " << e.what() << "\n";
    }
    return 0;
}
