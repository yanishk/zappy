/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AIFactory
*/

#include "AIFactory.hpp"

std::unique_ptr<Zappy::IAi> Zappy::AIFactory::createComponent(const std::string &value, const std::string &port)
{
    if (_table.find(value) != _table.end()) {
        return _table.find(value)->second(port);
    }

    return nullptr;
}
