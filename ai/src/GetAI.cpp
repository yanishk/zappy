/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** GetAI
*/

#include <vector>

#include "Run.hpp"
#include "Network.hpp"

#include "AI/Queen.hpp"
#include "AI/Quentin.hpp"
#include "AI/Searcher.hpp"

static std::vector<std::string> look(Network::Network &network)
{
    network.sendInformationToServer(LOOK);

    std::vector<std::string> vector;
    std::string informations = network.getInfoFromServer();

    while (!informations.compare(START, MESSAGE_LEN, MESSAGE)) {
        informations = network.getInfoFromServer();
    }

    if (informations == KO || informations == DEAD) {
        return {};
    }

    if (!informations.empty() && informations.front() == '[') {
        informations.erase(informations.begin());
    }
    if (!informations.empty() && informations.back() == ']') {
        informations.pop_back();
    }

    std::istringstream stream(informations);
    std::string line;

    while (std::getline(stream, line, ',')) {
        if (!line.empty() && line[0] == ' ') {
            line.erase(line.begin());
        }
        vector.push_back(line);
    }

    if (informations.back() == ',') {
        vector.push_back("");
    }

    return vector;
}

static std::size_t countRessources(const std::string &ressources, const std::string &index)
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

std::unique_ptr<Zappy::IAi> Zappy::getAI(Network::Network &network)
{
    network.getInfoFromServer();
    network.sendInformationToServer(FORMAT_NAME(network.getName()));

    if (network.getInfoFromServer() == KO) {
        return nullptr;
    }

    std::vector<std::string> ressources = look(network);

    if (ressources.empty()) {
        return nullptr;
    }

    if (countRessources(ressources[HERE], PLAYER) == ONE_PLAYER) {
        return std::make_unique<Zappy::Queen>();
    }

    if (countRessources(ressources[HERE], FOOD) < CRITICAL_STOCK) {
        return std::make_unique<Zappy::Quentin>();
    }

    // return nullptr;
    return std::make_unique<Zappy::Searcher>();
}
