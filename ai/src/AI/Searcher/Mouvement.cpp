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

Zappy::Response Zappy::Searcher::move()
{
    Mouvement nextMove = _nextMouvment.back();
    Zappy::Response rep;
    std::string object;
    std::vector<std::string> temp;

    switch (nextMove) {
        case Forward:
            std::cerr << "Forward\n";
            rep = forward();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _nextMouvment.pop_back();
            _position.first -= 1;
            break;

        case Left:
            std::cerr << "Left\n";
            rep = left();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }
            _nextMouvment.pop_back();
            _position.second -= 1;
            break;

        case Right:
            std::cerr << "Right\n";
            rep = right();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            _nextMouvment.pop_back();
            _position.second += 1;
            break;

        case Back:
            std::cerr << "Back\n";
            rep = left();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            rep = left();
            if (rep == Response::Ko) {
                return Response::Ko;
            } else if (rep == Response::Dead) {
                return Response::Dead;
            }

            rep = forward();
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

            object = _objectToTake.front();
            temp = look();
            std::cerr << "Look {\n";
            for (const auto &i: temp) {
                std::cerr << "\t" + i << "\n";
            }
            std::cerr << "}\n";
            if (takeObject(object) == Response::Ok) {
                std::cerr << "Take " << object << "\n";
                _order.removeRessources(object, 1);
            } else {
                return Response::Ko;
            }

            _objectToTake.erase(_objectToTake.begin());
            _nextMouvment.pop_back();
            updateOrder();
            break;

        default:
            break;
    }

    if (_order.empty()) {
        _nextMouvment.clear();
        std::cerr << "Go back to queen\n";
    }

    return Response::Ok;
}
