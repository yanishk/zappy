/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include <sstream>
#include "AI/AAi.hpp"
#include "AI/Quentin.hpp"
#include "Team.hpp"

std::string Zappy::AAi::handlingMessage()
{
    std::cout << "go handling some msg\n";
    std::string response = _network.getInfoFromServer();
    std::cout << "rep: (" << response << ")\n";
    std::string value;
    std::string orientation;
    std::string message;
    std::stringstream stream;

    if (response == RESPONSE_OK || response == RESPONSE_KO || response == DEAD) {
        return response;
    }

    while (response != RESPONSE_OK || response != RESPONSE_KO || response != DEAD) {
        if (!response.compare(0, MESSAGE_LEN, MESSAGE)) {
            stream << response;
            stream >> value >> orientation >> message;

            _orientation = getOrientation(std::atoi(orientation.c_str()));
            _message.emplace(_message.begin(), message);
        }

        response = _network.getInfoFromServer();

        if (response == RESPONSE_OK || response == RESPONSE_KO || response == DEAD) {
            return response;
        }
    }

    return response;
}

Zappy::Response Zappy::AAi::forward()
{
    _network.sendInformationToServer(FORWARD_CMD);

    std::string response = handlingMessage();

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

    std::string response = handlingMessage();

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

    std::string response = handlingMessage();

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
        return {};
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

std::vector<std::string> Zappy::AAi::inventory()
{
    _network.sendInformationToServer(INVENTORY_CMD);
    std::vector<std::string> vector;
    std::string information = _network.getInfoFromServer();

    if (information == RESPONSE_KO || information == DEAD) {
        return {};
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

void Zappy::AAi::updateInventory()
{
    std::vector<std::string> newInventory = inventory();

    for (const auto &i: newInventory) {
        std::stringstream stream;
        stream << i;
        std::string ressource;
        std::string quantity;
        stream >> ressource >> quantity;
        _ressources.updateRessources(ressource, std::atoi(quantity.c_str()));
    }

}

Zappy::Response Zappy::AAi::broadcastText(const std::string &text)
{
    _network.sendInformationToServer(BROADCAST_CMD + text);

    std::string response = handlingMessage();

    if (response == RESPONSE_OK) {
        return Response::Ok;
    } else if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Orientation Zappy::AAi::getOrientation(int value)
{
    switch (value) {
        case FRONT:
            return FRONT;
            break;
        case FRONT_LEFT:
            return FRONT_LEFT;
            break;
        case LEFT:
            return LEFT;
            break;
        case BACK_LEFT:
            return BACK_LEFT;
            break;
        case BACK:
            return BACK;
            break;
        case BACK_RIGHT:
            return BACK_RIGHT;
            break;
        case RIGHT:
            return RIGHT;
            break;
        default:
            return FRONT_RIGHT;
            break;
    }

    return UNDEFINED;
}

std::size_t Zappy::AAi::connectNumber()
{
    _network.sendInformationToServer(CONNECT_NBR_CMD);

    return std::atoi(_network.getInfoFromServer().c_str());
}

Zappy::Response Zappy::AAi::fork()
{
    _network.sendInformationToServer(FORK_CMD);

    std::string response = handlingMessage();

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

    std::string response = handlingMessage();

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

    std::string response = handlingMessage();

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

    std::string response = handlingMessage();

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
