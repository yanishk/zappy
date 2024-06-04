/*
** EPITECH PROJECT, 2024
** ai
** File description:
** TeamAi
*/

#include "TeamAi.hpp"

int Zappy::TeamAi::run()
{
    while (true) {
        std::string line = _network.getInfoFromServer();

        if (line == "end") {
            break;
        }
        _network.sendInformationToServer("exit");
    }
    return EXIT_WITH_SUCCESS;
}