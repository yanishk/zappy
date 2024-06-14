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

bool Zappy::AAi::forward()
{
    _network.sendInformationToServer(FORWARD_CMD);

    return _network.getInfoFromServer() == RESPONSE_OK;
}

bool Zappy::AAi::right()
{
    _network.sendInformationToServer(RIGHT_CMD);

    return _network.getInfoFromServer() == RESPONSE_OK;
}

bool Zappy::AAi::left()
{
    _network.sendInformationToServer(LEFT_CMD);

    return _network.getInfoFromServer() == RESPONSE_OK;
}

std::size_t Zappy::AAi::countMember(const std::string &line) const
{
    std::size_t count = 0;

    for (std::size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') {
            count++;
        }
    }

    return count;
}

std::vector<std::string> Zappy::AAi::look()
{
    _network.sendInformationToServer(LOOK_CMD);
    std::vector<std::string> vector;
    std::string information = _network.getInfoFromServer();
    std::size_t nbMember = countMember(information);

    while (vector.size() < nbMember) {
        std::istringstream stream(information);
        std::string line;

        std::getline(stream, line, ',');

        if (line[0] == '[') {
            line.erase(line.begin());
        }

        vector.push_back(line);
        information.erase(information.begin(), information.begin() + line.size() + 2);
    }

    information.pop_back();
    vector.push_back(information);
    for (auto &i:vector) {

        if (i[0] == ' ') {
            i.erase(i.begin());
        }
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
    std::size_t nbMember = countMember(information);

    while (vector.size() < nbMember) {
        std::istringstream stream(information);
        std::string line;

        std::getline(stream, line, ',');

        if (line[0] == '[') {
            line.erase(line.begin());
        }

        vector.push_back(line);
        information.erase(information.begin(), information.begin() + line.size() + 2);
    }

    information.pop_back();
    vector.push_back(information);
    for (auto &i:vector) {

        if (i[0] == ' ') {
            i.erase(i.begin());
        }
    }

    return checkRessources(vector);
}

bool Zappy::AAi::broadcastText(const std::string &text)
{
    _network.sendInformationToServer(BROADCAST_CMD + text);

    return _network.getInfoFromServer() == RESPONSE_OK;
}

std::size_t Zappy::AAi::connectNumber()
{
    _network.sendInformationToServer(CONNECT_NBR_CMD);

    return std::atoi(_network.getInfoFromServer().c_str());
}

bool Zappy::AAi::fork()
{
    _network.sendInformationToServer(FORK_CMD);

    if (_network.getInfoFromServer() == RESPONSE_KO) {
        return false;
    }

    return true;
}

bool Zappy::AAi::eject()
{
    _network.sendInformationToServer(EJECT_CMD);

    std::string response = _network.getInfoFromServer();

    return response == RESPONSE_OK;
}

bool Zappy::AAi::takeObject(const std::string &object)
{
    _network.sendInformationToServer(TAKE_CMD + object + "\n");

    std::string response = _network.getInfoFromServer();

    if (response != RESPONSE_OK) {
        return false;
    }

    _ressources.addRessources(object, 1);

    return true;
}

bool Zappy::AAi::setObject(const std::string &object)
{
    _network.sendInformationToServer(SET_CMD + object + "\n");

    std::string response = _network.getInfoFromServer();

    if (response != RESPONSE_OK) {
        return false;
    }

    _ressources.removeRessources(object, 1);

    return true;
}

bool Zappy::AAi::incantation()
{
    _network.sendInformationToServer(INCANTATION_CMD);
    std::string value = _network.getInfoFromServer();

    if (value == RESPONSE_KO) {
        return false;
    }
    std::stringstream stream;
    std::string temp;
    std::string level;

    stream << value;
    stream >> temp >> temp >> level;

    _level = std::atoi(level.c_str());
    return true;
}
