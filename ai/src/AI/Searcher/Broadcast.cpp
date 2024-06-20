/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Broadcast
*/

#include "AI/Searcher.hpp"

void Zappy::Searcher::goToBroadcast(Network::Network &network)
{
    if (_messages[0].second == IN_CASE) {
        return;
    }

    switch (_messages[0].second) {
        case FRONT:
            forward(network);
            break;

        case FRONT_LEFT:
            forward(network);
            left(network);
            break;

        case LEFT:
            left(network);
            break;

        case BACK_LEFT:
            left(network);
            left(network);
            forward(network);
            left(network);
            break;

        case BACK:
            left(network);
            left(network);
            forward(network);
            break;

        case BACK_RIGHT:
            left(network);
            left(network);
            forward(network);
            right(network);
            break;

        case RIGHT:
            right(network);
            break;

        case FRONT_RIGHT:
            forward(network);
            right(network);
            break;

        default:
            return;
    }

}
