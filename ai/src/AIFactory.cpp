/*
** EPITECH PROJECT, 2024
** B-YEP-400-PAR-4-1-zappy-edward.lalande
** File description:
** AIFactory
*/

#include "AIFactory.hpp"

Zappy::AIFactory::AIFactory()
{
    _table.emplace("default", IAi());
}

std::unique_ptr<Zappy::IAi> Zappy::AIFactory::createComponent(const std::string &value)
{

    for (const auto &i:_table) {

        if (i.first == value) {
            return std::make_unique<IAi>(i.second);
        }

    }

    return nullptr;
}
