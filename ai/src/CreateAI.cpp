/*
** EPITECH PROJECT, 2024
** ai
** File description:
** CreateAI
*/

#include "Run.hpp"
#include "CreateAI.hpp"

Zappy::Threads &Zappy::createAI(const std::string &name, const std::string &port, const std::string &home)
{
    static Threads threads;

    threads.emplace_back(&Zappy::run, name, port, home);

    return threads;
}

void Zappy::join(Zappy::Threads &threads)
{
    for (auto &thread: threads) {
        if (thread.joinable()) {
           thread.join();
        }
    }
}
