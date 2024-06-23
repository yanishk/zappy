/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include "Run.hpp"
#include "CreateAI.hpp"
#include "AI/Queen.hpp"

bool Zappy::Queen::run(Network::Network &network)
{
    std::cerr << QUEEN_WELCOME;

    if (!initialize(network)) {
        return false;
    }

    std::cerr << QUEEN_START;

    while (true) {

        if (!updateInventory(network)) {
            break;
        }

        std::cerr << QUEEN_UPDATE_INVENTORY;

        _look = look(network);

        if (_look.empty()) {
            break;
        }

        std::cerr << QUEEN_LOOK;

        for (const auto &items: _look) {
            std::cerr << QUEEN_LOOK_ITEM(items);
        }

        checkFood();
        checkIncantation();

        if (!checkHere(network)) {
            break;
        }

        if (!execute(network)) {
            break;
        };

    }

    std::cerr << QUEEN_DEAD;

    return false;
}

bool Zappy::Queen::initialize(Network::Network &network)
{
    const std::size_t value = connectNumber(network);

    std::cerr << QUEEN_INITIALIZE(value);

    for (std::size_t i = 0; i < value; ++i) {

        Network::Network child(network.getPort(), network.getName(), network.getHome());

        child.getInfoFromServer();
        child.sendInformationToServer(FORMAT_NAME(child.getName()));

        if (child.getInfoFromServer() == KO) {
            return false;
        }

    }

    return true;
}

bool Zappy::Queen::checkFood()
{
    _stock = countRessources(_look[HERE], FOOD);

    std::cerr << QUEEN_FOOD(_ressources[FOOD]);
    std::cerr << QUEEN_FOOD_STOCK(_stock);

    while (_ressources[FOOD] < CRITICAL_FOOD && _stock) {
        _actions.push_back(Take);
        _ressources[FOOD] += ONE_COUNT;
        _stock -= ONE_COUNT;
    }

    if (_stock < CRITICAL_STOCK) {
        _actions.push_back(ForkQueen);
    }

    return true;
}

bool Zappy::Queen::checkIncantation()
{
    if (checkRessources() && _level == FIRST_LEVEL) {
        _actions.push_back(Incantation);
        return true;
    }

    if (checkRessources() && checkPlayers()) {
        _actions.push_back(Incantation);
        return true;
    }

    if (!checkRessources()) {
        _actions.push_back(ForkQueen);
        return true;
    }

    _actions.push_back(AskAssistants);

    return true;
}

bool Zappy::Queen::checkHere(Network::Network &network)
{
    const std::string suffix = BROADCAST_PING_SUFFIX;

    if (_messages.empty()) {
        return true;
    }

    for (std::size_t i = 0; i < MAX_LAST_MESSAGE && i < _messages.size(); i++) {

        const std::string content = _messages[i].first;
        const std::size_t size = content.size();

        if (size > suffix.size() && content.substr(size - suffix.size()) == suffix) {

            if (broadcastText(network, BROADCAST_HERE_ALL) != Response::Ok) {
                return false;
            }

            std::cerr << QUEEN_SAY_HERE_ALL;

            _messages.clear();

        }

    }

    return true;
}

bool Zappy::Queen::checkRessources()
{
    const Ressources ressources = { LINEMATE, DERAUMERE, SIBUR, MENDIANE, PHIRAS, THYSTAME };

    for (const auto &ressource: ressources) {

        std::size_t ressourcesCount = countRessources(_look[HERE], ressource);
        std::size_t ressourcesNeed = _incatation[_level - LEVEL_INDEX].second[ressource];

        if (ressourcesCount < ressourcesNeed) {
            return false;
        }

    }

    return true;
}

bool Zappy::Queen::checkPlayers()
{
    if (_assistants.size() == _incatation[_level - ONE_LEVEL].first - ONE_PLAYER) {
        return true;
    }

    return false;
}

bool Zappy::Queen::askAssistants(Network::Network &network)
{
    _nbAssistants = _assistants.size() + _assistantsIncomming.size();

    std::cerr << QUEEN_ASSISTANTS(_assistants.size());
    std::cerr << QUEEN_ASSISTANTS_INCOMMING(_assistantsIncomming.size());

    if (_nbAssistants < _incatation[_level - ONE_LEVEL].first - ONE_LEVEL) {

        if (broadcastText(network, BROADCAST_QUEEN_ASK_ASSISTANTS(_level)) != Response::Ok) {
            return false;
        }

        std::cerr << QUEEN_SAY_ASK_ASSISTANT(_level);

        if (!addAssistantsIncomming(network)) {
            return false;
        }
    }

    if (!addAssistants(network)) {
        return false;
    }

    return true;
}

bool Zappy::Queen::addAssistantsIncomming(Network::Network &network)
{
    const std::string suffix = BROADCAST_ASK_SUFFIX;

    if (_messages.empty()) {
        return true;
    }

    for (std::size_t i = 0; i < MAX_LAST_MESSAGE && i < _messages.size(); i++) {

        const std::string content = _messages[i].first;
        const std::size_t size = content.size();

        if (size > suffix.size() && content.substr(size - suffix.size()) == suffix) {
            
            const std::string messageId = content.substr(START, size - suffix.size());
            bool isIncomming = false;

            for (const auto &id: _assistantsIncomming) {

                if (id == messageId) {
                    isIncomming = true;
                }

            }

            if (!isIncomming && _nbAssistants == _incatation[_level - ONE_LEVEL].first - ONE_LEVEL) {

                if (broadcastText(network, BROADCAST_QUEEN_NO(messageId)) != Response::Ok) {
                    return false;
                }

                std::cerr << QUEEN_SAY_NO(messageId);

            }

            if (!isIncomming) {

                _assistantsIncomming.push_back(messageId);

                if (broadcastText(network, BROADCAST_QUEEN_HERE(messageId)) != Response::Ok) {
                    return false;
                }

                std::cerr << QUEEN_SAY_HERE_COME(messageId);

                _nbAssistants += ONE_COUNT;

            }

        }

    }

    return true;
}

bool Zappy::Queen::addAssistants(Network::Network &network)
{
    const std::string suffix = BROADCAST_PING_SUFFIX;

    if (_messages.empty()) {
        return true;
    }

    for (std::size_t i = 0; i < MAX_LAST_MESSAGE && i < _messages.size(); i++) {

        const std::string content = _messages[i].first;
        const Orientation orientation = _messages[i].second;
        const std::size_t size = content.size();

        if (size > suffix.size() && content.substr(size - suffix.size()) == suffix) {

            if (!sendMessageToAssistant(network, content, orientation)) {
                return false;
            }

        }

    }

    return true;
}

bool Zappy::Queen::sendMessageToAssistant(Network::Network &network, const std::string &content, const Orientation &orientation)
{
    const std::string suffix = BROADCAST_PING_SUFFIX;
    const std::size_t size = content.size();

    const std::string messageId = content.substr(START, size - suffix.size());

    for (std::size_t i = 0; i < _assistantsIncomming.size(); i++) {

        if (_assistantsIncomming[i] == messageId && orientation == IN_CASE) {

            _assistants.push_back(_assistantsIncomming[i]);
            _assistantsIncomming.erase(_assistantsIncomming.begin() + i);

            std::cerr << QUEEN_ASSISTANT_IS_HERE(messageId);

        }

    }

    if (broadcastText(network, BROADCAST_QUEEN_HERE(messageId)) != Response::Ok) {
        return false;
    }

    std::cerr << QUEEN_SAY_HERE(messageId);

    return true;
}

bool Zappy::Queen::execute(Network::Network &network)
{
    for (const auto &action: _actions) {

        for (const auto &task : _execute) {

            if (action == task.first) {

                if (!task.second(network)) {
                    return false;
                }

                break;

            }

        }

    }

    _actions.clear();

    return true;
}

bool Zappy::Queen::take(Network::Network &network)
{
    if (takeObject(network, FOOD) != Response::Ok) {
        return false;
    }

    std::cerr << QUEEN_TAKE_FOOD;

    return true;
}

bool Zappy::Queen::forkQueen(Network::Network &network)
{
    if (fork(network) != Response::Ok) {
        return false;
    }

    std::cerr << QUEEN_FORK;

    Zappy::createAI(network.getName(), network.getPort(), network.getHome());

    if (broadcastText(network, BROADCAST_QUEEN_LEVEL(_level)) != Response::Ok) {
        return false;
    }

    std::cerr << QUEEN_SAY_LEVEL(_level);

    return true;
}

bool Zappy::Queen::makeIncantation(Network::Network &network)
{
    std::cerr << QUEEN_START_INCANTATION(_level + ONE_LEVEL);

    std::string message(BROADCAST_QUEEN_INCANTATION);

    for (const auto &assistant: _assistants) {
        message.append(BROADCAST_PREFIXE + assistant);
    }

    _assistants.clear();
    _messages.clear();

    if (broadcastText(network, message) != Response::Ok) {
        return false;
    }

    std::cerr << QUEEN_SAY_INCANTATION(message);

    if (incantation(network) != Response::Ok) {
        return false;
    }

    std::cerr << QUEEN_INCANTATION(_level);

    return true;
}

std::size_t Zappy::Queen::countRessources(const std::string &ressources, const std::string &index)
{
    if (!index.length()) {
        return NONE;
    }

    std::size_t count = INITIAL_COUNT;
    std::size_t offset = ressources.find(index);

    while (offset != std::string::npos) {
        count += ONE_COUNT;
        offset = ressources.find(index, offset + index.length());
    }

    return count;
}
