/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Run
*/

#ifndef RUN_HPP_
    #define RUN_HPP_

    #include <string>
    #include <memory>

    #include "AI/IAi.hpp"

    #define FORMAT_NAME(x) x + "\n"
    #define LOOK "Look\n"
    #define KO "ko\n"
    #define OK "ok\n"

    #define MESSAGE "message"
    #define MESSAGE_LEN 7
    #define START 0

    #define NONE 0
    #define ONE_COUNT 1

    #define PLAYER "player"
    #define FOOD "food"

    #define HERE 0
    #define ONE_PLAYER 1

namespace Zappy {

    std::unique_ptr<IAi> getAI(Network::Network &network);
    bool run(const std::string &name, const std::string &port, const std::string &home);

};

#endif /* !RUN_HPP_ */