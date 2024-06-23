/*
** EPITECH PROJECT, 2024
** Factory file
** File description:
** Zappy proj
*/

#ifndef FACTORY_HPP
    #define FACTORY_HPP
    #include <memory>
    #include <variant>
    #include "AllItem.hpp"
    #include "AllIsland.hpp"
    #include "AllPlayer.hpp"
    #include "Sea.hpp"
    #include "Sky.hpp"
    #include "Render.hpp"
    #include "AllEggs.hpp"
    #include "Commands.hpp"
    #include "AllObj.hpp"

    #define WRONG_TYPE "Unknown Type"

enum class objType {

    ItemType = 0,
    IslandType = 1,
    PlayerType = 2,
    EggType = 3,
    SkyType = 4,
    SeaType = 5
};

namespace Zappy {

    class Factory {

        public:

            using AllObjVar = std::variant<std::unique_ptr<AllItem>,
                std::unique_ptr<AllPlayers>, std::unique_ptr<AllIsland>, std::unique_ptr<AllEggs>>;
            using ObjVar = std::variant<std::unique_ptr<Sky>, std::unique_ptr<Sea>>;


            static AllObjVar newObjects(objType type, CommandManager &cmd, bool anim);
            static ObjVar newObject(objType type);

    };
}

#endif // FACTORY_HPP
