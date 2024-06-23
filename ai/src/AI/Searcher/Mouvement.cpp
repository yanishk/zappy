/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** Mouvement
*/

#include "AI/Searcher.hpp"


void Zappy::Searcher::dumpMovement()
{
    std::cerr << "Mouvement {\n";

    for (const auto &i: _nextMouvment) {
        if (i == Zappy::Mouvement::Forward) {
            std::cerr << "\tForward,\n";
        }
        if (i == Zappy::Mouvement::Left) {
            std::cerr << "\tLeft,\n";
        }
        if (i == Zappy::Mouvement::Right) {
            std::cerr << "\tRight,\n";
        }
        if (i == Zappy::Mouvement::Back) {
            std::cerr << "\tBack,\n";
        }
        if (i == Zappy::Mouvement::Take) {
            std::cerr << "\tTake,\n";
        }
    }

    std::cerr << "}\n";
}

std::string Zappy::Searcher::takeThis(std::string tiled)
{
    std::istringstream stream(tiled);
    std::string temp("");
    Ressources ress = _order.getRessources();

    std::vector<int> value = ress.getAllValueRessources();

    std::cerr << "\tFood value: " << ress[FOOD] << "\n";
    std::cerr << "\tLINEMATE value: " << ress[LINEMATE] << "\n";
    std::cerr << "\tDERAUMERE value: " << ress[DERAUMERE] << "\n";
    std::cerr << "\tSIBUR value: " << ress[SIBUR] << "\n";
    std::cerr << "\tMENDIANE value: " << ress[MENDIANE] << "\n";
    std::cerr << "\tPHIRAS value: " << ress[PHIRAS] << "\n";
    std::cerr << "\tTHYSTAME value: " << ress[THYSTAME] << "\n";

    while (std::getline(stream, temp, ' ')) {

        if (ress.getRessource(temp) > 0 && temp != FOOD) {
            _order.removeRessources(temp, 1);
            return temp;
        }
    }

    return "";
}

Zappy::Response Zappy::Searcher::move(Network::Network &network)
{
    Mouvement nextMove = _nextMouvment.back();
    Zappy::Response rep;
    std::string object;
    std::vector<std::string> temp;

    switch (nextMove) {
        case Forward:
            std::cerr << "Searcher : " << _id << " Forward\n";
            rep = forward(network);
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _moveToStarter.emplace(_moveToStarter.begin(), Forward);
            _nextMouvment.pop_back();
            _position.first -= 1;
            break;

        case Left:
            std::cerr << "Searcher : " << _id << " Left\n";
            rep = left(network);
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _moveToStarter.emplace(_moveToStarter.begin(), Right);
            _nextMouvment.pop_back();
            _position.second -= 1;
            break;

        case Right:
            std::cerr << "Searcher : " << _id << " Right\n";
            rep = right(network);
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _moveToStarter.emplace(_moveToStarter.begin(), Left);
            _nextMouvment.pop_back();
            _position.second += 1;
            break;

        case Back:
            std::cerr << "Searcher : " << _id << " Back\n";
            rep = left(network);
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            rep = left(network);
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            rep = forward(network);
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            _nextMouvment.pop_back();
            _nextMouvment.pop_back();
            _nextMouvment.pop_back();
            _position.first += 1;
            break;

        case Take:

            temp = look(network);
            object = takeThis(temp[0]);

            std::cerr  << "Searcher : " << _id << " last Look {\n";
            for (const auto &i: temp) {
                std::cerr << "\t" + i << "\n";
            }
            if (object == "") {
                std::cerr << "Object not found\n";
                _nextMouvment.clear();
                return Response::Ko;
            }
            std::cerr << "}\n";
            if (takeObject(network, object) == Response::Ok) {
                std::cerr << "Searcher : " << _id << " Take " << object << "\n";
            } else {
                return Response::Ko;
            }

            _nextMouvment.clear();
            updateOrder();
            break;

        default:
            break;
    }

    return Response::Ok;
}
