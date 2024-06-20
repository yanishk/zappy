/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Broadcast
*/

#include "AI/Searcher.hpp"

Zappy::Searcher::Message Zappy::Searcher::createMessage(const std::string &content)
{
    std::string value;
    std::string orientation;
    std::string message;
    std::stringstream stream;

    stream << content;
    stream >> value >> orientation >> message;

    return Message(message, getOrientation(std::atoi(orientation.c_str())));
}

bool Zappy::Searcher::checkAskAssistants(Network::Network &network)
{
    const std::string prefix = PREFIX_ASK_ASSISTANT;

    if (_messages.empty()) {
        return true;
    }

    for (std::size_t i = 0; i < MAX_LAST_MESSAGE && i < _messages.size(); i++) {

        std::size_t position = _messages[i].first.find(prefix);
        std::size_t level = START_LEVEL;

        if (position == std::string::npos) {
            continue;
        }

        position += prefix.length();
        level = std::stoul(_messages[i].first.substr(position));

        if (level != _level - ONE_LEVEL) {
            continue;
        }

        if (broadcastText(network, RESPONSE_ASK(_id)) != Response::Ok) {
            return false;
        }

        waitAskResponse(network);

    }

    return true;
}

bool Zappy::Searcher::waitAskResponse(Network::Network &network)
{
    std::string response = network.getInfoFromServer();

    Message message = createMessage(response);

    const std::string herePrefix = PREFIX_ASK_RESPONSE_HERE;
    const std::string noPrefix = PREFIX_ASK_RESPONSE_HERE;

    std::size_t herePosition = message.first.find(herePrefix);
    std::size_t noPosition = message.first.find(noPrefix);
    int id = START_ID;

    if (herePosition == std::string::npos && noPosition == std::string::npos) {
        return waitAskResponse(network);
    }

    if (herePosition != std::string::npos) {

        herePosition += herePrefix.length();
        id = std::stoul(message.first.substr(herePosition));

        if (id != _id) {
            return waitAskResponse(network);
        }

        _goBackToQueen = true;
        _messages.clear();

        return true;

    }

    noPosition += noPrefix.length();
    id = std::stoul(response.substr(noPosition));

    if (id != _id) {
        return waitAskResponse(network);
    }

    return true;
}