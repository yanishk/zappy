/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Broadcast
*/

#include "AI/Searcher.hpp"
#include "Broadcast.hpp"

void Zappy::Searcher::goToBroadcast()
{
    if (_orientation == IN_CASE) {
        return;
    }

    std::stringstream myId;
    myId << std::this_thread::get_id();

    Broadcast broadcastHandler(_name, myId.str());

    switch (_orientation) {
        case FRONT:
            forward();
            break;

        case FRONT_LEFT:
            forward();
            left();
            break;

        case LEFT:
            left();
            break;

        case BACK_LEFT:
            left();
            left();
            forward();
            left();
            break;

        case BACK:
            left();
            left();
            forward();
            break;

        case BACK_RIGHT:
            left();
            left();
            forward();
            right();
            break;

        case RIGHT:
            right();
            break;

        case FRONT_RIGHT:
            forward();
            right();
            break;

        default:
            return;
    }

    while (true) {

        std::string response = broadcastHandler.ping(_network, _idToReach);
        std::string orientation("");
        std::string value("");
        std::string message("");

        if (!response.compare(0, MESSAGE_LEN, MESSAGE)) {
            std::stringstream stream;
            stream << response;
            stream >> value >> orientation >> message;

            _orientation = getOrientation(std::atoi(orientation.c_str()));
            break;

        }

    }

    goToBroadcast();
}
