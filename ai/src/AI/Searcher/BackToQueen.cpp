/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** GoBackToQueen
*/

#include "AI/Searcher.hpp"

Zappy::Orientation Zappy::Searcher::getOrientationToQueen(Network::Network &network)
{
    if (broadcastText(network, ASK_PING(_id)) != Response::Ok) {
        return Orientation::UNDEFINED;
    }

    const std::string prefix = PREFIX_ASK_RESPONSE_HERE;

    std::string response = network.getInfoFromServer();

    Message message = createMessage(response);

    std::size_t position = message.first.find(prefix);

    if (position == std::string::npos) {
        return getOrientationToQueen(network);
    }

    return message.second;
}

bool Zappy::Searcher::launchIncantation(Network::Network &network)
{
    if (takeObject(network, FOOD) != Response::Ok) {
        return false;
    }

    if (takeObject(network, FOOD) != Response::Ok) {
        return false;
    }

    std::string response = handlingMessage(network);

    if (response != ELEVATION_UNDERWAY) {
        return false;
    }

    response = handlingMessage(network);

    const std::string prefix = PREFIX_LEVEL;
    std::size_t position = response.find(PREFIX_LEVEL);

    if (position == std::string::npos) {
        return false;
    }

    position += prefix.length();
    _level = std::stoul(response.substr(position));

    _goBackToQueen = false;
    _messages.clear();

    return true;
}

bool Zappy::Searcher::backToQueen(Network::Network &network, bool incantation)
{
    Orientation orientation = getOrientationToQueen(network);

    if (orientation == Orientation::UNDEFINED) {
        return false;
    }

    if (orientation == Orientation::IN_CASE && incantation) {
        return launchIncantation(network);
    }

    if (orientation == Orientation::IN_CASE) {
        return true;
    }

    switch (orientation) {

        case FRONT:

            if (forward(network) != Response::Ok) {
                return false;
            }
            break;

        case FRONT_LEFT:

            if (forward(network) != Response::Ok) {
                return false;
            }
            if (left(network) != Response::Ok) {
                return false;
            }
            break;

        case LEFT:

            if (left(network) != Response::Ok) {
                return false;
            }
            break;

        case BACK_LEFT:

            if (left(network) != Response::Ok) {
                return false;
            }
            if (left(network) != Response::Ok) {
                return false;
            }
            if (forward(network) != Response::Ok) {
                return false;
            }
            if (left(network) != Response::Ok) {
                return false;
            }
            break;

        case BACK:

            if (left(network) != Response::Ok) {
                return false;
            }
            if (left(network) != Response::Ok) {
                return false;
            }
            if (forward(network) != Response::Ok) {
                return false;
            }
            break;

        case BACK_RIGHT:

            if (left(network) != Response::Ok) {
                return false;
            }
            if (left(network) != Response::Ok) {
                return false;
            }
            if (forward(network) != Response::Ok) {
                return false;
            }
            if (right(network) != Response::Ok) {
                return false;
            }
            break;

        case RIGHT:

            if (right(network) != Response::Ok) {
                return false;
            }
            break;

        case FRONT_RIGHT:

            if (forward(network) != Response::Ok) {
                return false;
            }
            if (right(network) != Response::Ok) {
                return false;
            }
            break;

        default:

            return false;

    }

    return backToQueen(network, incantation);
}
