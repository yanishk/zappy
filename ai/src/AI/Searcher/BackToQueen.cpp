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
    _inDelivery = false;
    _queenLevel += 1;
    _level += 1;
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

    if (_position.first < 0) {

        _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Left);
        _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Left);
        while (_position.first < 0) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
            _position.first += 1;
        }
    } else {
        while (_position.first > 0) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
            _position.first -= 1;
        }
    }

    if (_position.second < 0) {

        _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Left);
        while (_position.first > 0) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
            _position.first -= 1;
        }

    } else {

        _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Right);
        while (_position.first < 0) {
            _nextMouvment.emplace(_nextMouvment.begin(), Mouvement::Forward);
            _position.first += 1;
        }

    }

    std::cerr << "\t\tposX: " << _position.first << " posY: " << _position.second << "\n";
    std::cerr << "MOUVEMENT TO QUEEN:\n";
    dumpMovement();

    return true;
}
