/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Quentin
*/

#include "CreateAI.hpp"
#include "AI/Quentin.hpp"

bool Zappy::Quentin::run(Network::Network &network)
{
    std::cerr << QUENTIN_WELCOME(_id);

    if (!updateInventory(network)) {
        std::cerr << QUENTIN_DEAD(_id);
        return false;
    }

    while (_ressources[FOOD] > LAST_FOOD) {

        if (setObject(network, FOOD) != Response::Ok) {
            std::cerr << QUENTIN_DEAD(_id);
            return false;
        }

        std::cerr << QUENTIN_DROP(_id);

    }

    return forkQuentin(network);
}

bool Zappy::Quentin::forkQuentin(Network::Network &network)
{
    if (fork(network) != Response::Ok) {
        std::cerr << QUENTIN_DEAD(_id);
        return false;
    }

    std::cerr << QUENTIN_FORK(_id);

    Zappy::createAI(network.getName(), network.getPort(), network.getHome());

    std::cerr << QUENTIN_DEAD(_id);

    return true;
}
