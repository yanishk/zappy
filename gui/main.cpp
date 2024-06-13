/*
** EPITECH PROJECT, 2024
** all_test_libray
** File description:
** main
*/

#include "DisplayGame.hpp"
#include "ParsesModelConfig.hpp"
#include "Commands.hpp"
#include "Gui.hpp"
#include "Client.hpp"

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
    return 0;
}
