/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Broadcast
*/

#include "AI/Searcher.hpp"

void Zappy::Searcher::goToBroadcast(Network::Network &network)
{
    // if (!_messages[0].first.compare(0, _messages[0].first.find(":"), QUEEN)) {
    // }
    if (_messages[0].second == IN_CASE) {
        return;
    }

    switch (_messages[0].second) {
        case FRONT:
            std::cout << "Searcher: " << _id << " go Front\n";
            forward(network);
            break;

        case FRONT_LEFT:
            std::cout << "Searcher: " << _id << " go Front Left\n";
            forward(network);
            left(network);
            break;

        case LEFT:
            std::cout << "Searcher: " << _id << " go Left\n";
            left(network);
            break;

        case BACK_LEFT:
            std::cout << "Searcher: " << _id << " go Back Left\n";
            left(network);
            left(network);
            forward(network);
            left(network);
            break;

        case BACK:
            std::cout << "Searcher: " << _id << " go Back\n";
            left(network);
            left(network);
            forward(network);
            break;

        case BACK_RIGHT:
            std::cout << "Searcher: " << _id << " go Back Right\n";
            left(network);
            left(network);
            forward(network);
            right(network);
            break;

        case RIGHT:
            std::cout << _id << " go Right\n";
            right(network);
            break;

        case FRONT_RIGHT:
            std::cout << _id << " go Front Right\n";
            forward(network);
            right(network);
            break;

        default:
            return;
    }

    handlingMessage(network);

    goToBroadcast(network);
}
