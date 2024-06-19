/*
** EPITECH PROJECT, 2024
** ai
** File description:
** CreateAI
*/

#include "Run.hpp"
#include "CreateAI.hpp"

Zappy::Threads &Zappy::createAI(const std::string &name, const std::string &port)
{
    static Threads threads;

    threads.push_back(std::thread(Zappy::run, name, port));

    return std::ref(threads);
}

void Zappy::join(Zappy::Threads &threads)
{
    for (auto &thread: threads) {
        thread.join();
    }
}
