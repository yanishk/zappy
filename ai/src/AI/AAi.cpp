/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include <sstream>

#include "AI/AAi.hpp"
#include "AI/Quentin.hpp"

Zappy::Response Zappy::AAi::forward()
{
    _network.sendInformationToServer(FORWARD_CMD);

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::right()
{
    _network.sendInformationToServer(RIGHT_CMD);

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::left()
{
    _network.sendInformationToServer(LEFT_CMD);

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

std::vector<std::string> Zappy::AAi::look()
{
    _network.sendInformationToServer(LOOK_CMD);
    std::vector<std::string> vector;
    std::string information = _network.getInfoFromServer();

    if (information == RESPONSE_KO || information == DEAD) {
        return { DEAD };
    }

    if (!information.empty() && information[0] == '[') {
        information.erase(information.begin());
    }
    if (!information.empty() && information.back() == ']') {
        information.pop_back();
    }

    std::istringstream stream(information);
    std::string line;
    while (std::getline(stream, line, ',')) {
        if (!line.empty() && line[0] == ' ') {
            line.erase(line.begin());
        }
        vector.push_back(line);
    }

    if (information.back() == ',') {
        vector.push_back("");
    }

    return vector;
}

bool Zappy::AAi::checkRessources(const std::vector<std::string> &newRessources)
{
    for (const auto &i: newRessources) {
        std::stringstream stream;
        stream << i;
        std::string ressources;
        std::string quantity;
        stream >> ressources >> quantity;
        if (_ressources.getRessource(ressources) != std::atoi(quantity.c_str())) {
            return false;
        }
    }

    return true;
}

bool Zappy::AAi::inventory()
{
    _network.sendInformationToServer(INVENTORY_CMD);
    std::vector<std::string> vector;
    std::string information = _network.getInfoFromServer();

    if (information == RESPONSE_KO || information == DEAD) {
        return false;
    }

    if (!information.empty() && information[0] == '[') {
        information.erase(information.begin());
    }
    if (!information.empty() && information.back() == ']') {
        information.pop_back();
    }

    std::istringstream stream(information);
    std::string line;
    while (std::getline(stream, line, ',')) {
        if (!line.empty() && line[0] == ' ') {
            line.erase(line.begin());
        }
        vector.push_back(line);
    }

    if (information.back() == ',') {
        vector.push_back("");
    }

    return checkRessources(vector);
}

Zappy::Response Zappy::AAi::broadcastText(const std::string &text)
{
    _network.sendInformationToServer(BROADCAST_CMD + text);

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

std::size_t Zappy::AAi::connectNumber()
{
    _network.sendInformationToServer(CONNECT_NBR_CMD);

    return std::atoi(_network.getInfoFromServer().c_str());
}

Zappy::Response Zappy::AAi::fork()
{
    _network.sendInformationToServer(FORK_CMD);

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::eject()
{
    _network.sendInformationToServer(EJECT_CMD);

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::takeObject(const std::string &object)
{
    _network.sendInformationToServer(TAKE_CMD + object + "\n");

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::setObject(const std::string &object)
{
    _network.sendInformationToServer(SET_CMD + object + "\n");

    std::string response = _network.getInfoFromServer();

    if (response == RESPONSE_OK) {
        _ressources.removeRessources(object, 1);
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::incantation()
{
    std::cout << "Incantation\n";
    _network.sendInformationToServer(INCANTATION_CMD);
    std::string value = _network.getInfoFromServer();

    if (value == RESPONSE_OK) {
        std::stringstream stream;
        std::string temp;
        std::string level;

        stream << value;
        stream >> temp >> temp >> level;

        _level = std::atoi(level.c_str());
        return Response::Ok;
    } else if (value == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}
