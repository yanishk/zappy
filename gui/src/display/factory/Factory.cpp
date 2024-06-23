/*
** EPITECH PROJECT, 2024
** Factory file
** File description:
** Zappy proj
*/

#include "Factory.hpp"

Zappy::Factory::AllObjVar Zappy::Factory::newObjects(objType type, CommandManager &cmd,
    bool anim)
{

    switch (type) {
        case objType::ItemType:
            return std::make_unique<AllItem>(cmd);
        case objType::IslandType:
            return std::make_unique<AllIsland>(cmd);
        case objType::EggType:
            return std::make_unique<AllEggs>(cmd);
        case objType::PlayerType:
            return std::make_unique<AllPlayers>(cmd, anim);
        default:
            throw std::invalid_argument(WRONG_TYPE);
    }
}

Zappy::Factory::ObjVar Zappy::Factory::newObject(objType type)
{

    switch (type) {
        case objType::SkyType:
            return std::make_unique<Sky>();
        case objType::SeaType:
            return std::make_unique<Sea>();
        default:
            throw std::invalid_argument(WRONG_TYPE);
    }
}
