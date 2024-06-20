/*
** EPITECH PROJECT, 2024
** ai
** File description:
** CreateAI
*/

#ifndef CREATE_AI_HPP_
    #define CREATE_AI_HPP_

    #include <vector>
    #include <thread>
    #include <string>

namespace Zappy {

    using Threads = std::vector<std::thread>;

    Threads &createAI(const std::string &name, const std::string &port, const std::string &home);
    void join(Threads &threads);

};

#endif /* !CREATE_AI_HPP_ */