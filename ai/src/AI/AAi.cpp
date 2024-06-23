/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AAi
*/

#include <sstream>

#include "AI/AAi.hpp"
#include "AI/Quentin.hpp"

std::string Zappy::AAi::handlingMessage(Network::Network &network)
{
    std::string response = network.getInfoFromServer();

    if (response == RESPONSE_OK || response == RESPONSE_KO || response == DEAD) {
        return response;
    }

    while (!response.compare(START, MESSAGE_LEN, MESSAGE)) {

        std::string value;
        std::string orientation;
        std::string message;
        std::stringstream stream;

        stream << response;
        stream >> value >> orientation >> message;

        _messages.emplace(_messages.begin(), std::make_pair(message, getOrientation(std::atoi(orientation.c_str()))));

        response = network.getInfoFromServer();

    }

    return response;
}

Zappy::Response Zappy::AAi::forward(Network::Network &network)
{
    network.sendInformationToServer(FORWARD_CMD);

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        std::cerr << "Forward\n";
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::right(Network::Network &network)
{
    network.sendInformationToServer(RIGHT_CMD);

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::left(Network::Network &network)
{
    network.sendInformationToServer(LEFT_CMD);

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

std::vector<std::string> Zappy::AAi::look(Network::Network &network)
{
    network.sendInformationToServer(LOOK_CMD);

    std::string informations = handlingMessage(network);

    if (informations == RESPONSE_KO || informations == DEAD) {
        return {};
    }

    if (!informations.empty() && informations.front() == '[') {
        informations.erase(informations.begin());
    }

    if (!informations.empty() && informations.back() == ']') {
        informations.pop_back();
    }

    std::vector<std::string> vector;

    std::istringstream stream(informations);
    std::string line;

    while (std::getline(stream, line, ',')) {

        if (!line.empty() && line.front() == ' ') {
            line.erase(line.begin());
        }

        vector.push_back(line);

    }

    if (informations.back() == ',') {
        vector.push_back("");
    }

    return vector;
}

std::vector<std::string> Zappy::AAi::inventory(Network::Network &network)
{
    network.sendInformationToServer(INVENTORY_CMD);

    std::string informations = handlingMessage(network);

    if (informations == RESPONSE_KO || informations == DEAD) {
        return {};
    }

    if (!informations.empty() && informations.front() == '[') {
        informations.erase(informations.begin());
    }

    if (!informations.empty() && informations.back() == ']') {
        informations.pop_back();
    }

    std::vector<std::string> vector;

    std::istringstream stream(informations);
    std::string line;

    while (std::getline(stream, line, ',')) {

        if (!line.empty() && line.front() == ' ') {
            line.erase(line.begin());
        }

        vector.push_back(line);

    }

    if (informations.back() == ',') {
        vector.push_back("");
    }

    return vector;
}

bool Zappy::AAi::updateInventory(Network::Network &network)
{
    std::vector<std::string> newInventory = inventory(network);

    if (newInventory.empty()) {
        return false;
    }

    for (const auto &i: newInventory) {

        std::stringstream stream;
        stream << i;
        std::string ressource;
        std::string quantity;
        stream >> ressource >> quantity;
        if (ressource == FOOD) {
            _ressources.updateRessources(ressource, std::atoi(quantity.c_str()));
        }

    }

    return true;
}

Zappy::Response Zappy::AAi::broadcastText(Network::Network &network, const std::string &text)
{
    network.sendInformationToServer(BROADCAST_CMD + text);

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
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
        case FRONT_RIGHT:
            return FRONT_RIGHT;
        default:
            return IN_CASE;
            break;
    }

    return UNDEFINED;
}

std::size_t Zappy::AAi::connectNumber(Network::Network &network)
{
    network.sendInformationToServer(CONNECT_NBR_CMD);

    return std::atoi(network.getInfoFromServer().c_str());
}

Zappy::Response Zappy::AAi::fork(Network::Network &network)
{
    network.sendInformationToServer(FORK_CMD);

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        return Response::Ok;
    }

    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::eject(Network::Network &network)
{
    network.sendInformationToServer(EJECT_CMD);

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::takeObject(Network::Network &network, const std::string &object)
{
    network.sendInformationToServer(TAKE_CMD + object + "\n");

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::setObject(Network::Network &network, const std::string &object)
{
    network.sendInformationToServer(SET_CMD + object + "\n");

    std::string response = handlingMessage(network);

    if (response == RESPONSE_OK) {
        _ressources.removeRessources(object, 1);
        return Response::Ok;
    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}

Zappy::Response Zappy::AAi::incantation(Network::Network &network)
{
    network.sendInformationToServer(INCANTATION_CMD);

    std::string response = handlingMessage(network);

    if (response == ELEVATION_UNDERWAY) {

        response = handlingMessage(network);

        const std::string prefix = PREFIX_LEVEL;
        std::size_t position = response.find(PREFIX_LEVEL);

        if (position == std::string::npos) {
            return Response::Ko;
        }

        position += prefix.length();
        _level = std::stoul(response.substr(position));
    
        return Response::Ok;

    }
    
    if (response == RESPONSE_KO) {
        return Response::Ko;
    }

    return Response::Dead;
}
